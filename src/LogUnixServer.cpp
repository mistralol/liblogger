
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sstream>

#include <poll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "liblogger.h"

namespace liblogger
{

LogUnixServer::LogUnixServer(const std::string &path) :
	m_path(path),
	m_acceptfd(-1),
	m_running(false)
{
	m_ctlfd[0] = -1;
	m_ctlfd[1] = -1;

	try
	{
		if (pthread_mutex_init(&m_mutex, NULL) != 0)
			abort();

		unlink(m_path.c_str());
		m_acceptfd = socket(AF_UNIX, SOCK_STREAM, 0);
		if (m_acceptfd < 0)
		{
			std::stringstream ss;
			ss << "Cannot create socket: " << strerror(errno);
			throw(LogException(ss.str()));
		}

		if (socketpair(AF_LOCAL, SOCK_STREAM, 0, m_ctlfd) != 0)
		{
			std::stringstream ss;
			ss << "Cannot create ctlfd: " << strerror(errno);
			throw(LogException(ss.str()));
		}

		//Bind etc..
		struct sockaddr_un serv_addr;
		socklen_t sockaddr_len = sizeof(serv_addr);
		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sun_family = AF_UNIX;
		snprintf(serv_addr.sun_path, sizeof(serv_addr.sun_path), "%s", m_path.c_str());

		if (bind(m_acceptfd, (struct sockaddr *) &serv_addr, sockaddr_len) < 0)
		{
			std::stringstream ss;
			ss << "Cannot bind to path: " << m_path << " error: " << strerror(errno);
			throw(LogException(ss.str()));
		}

		if (listen(m_acceptfd, 15) < 0)
		{
			std::stringstream ss;
			ss << "Cannot listen on path: " << m_path << " error: " << strerror(errno);
			throw(LogException(ss.str()));
		}

		//Create thread
		if (pthread_create(&m_thread, NULL, LogUnixServer::Run, this) != 0)
		{
			std::stringstream ss;
			ss << "Cannot start thread: " << strerror(errno);
			throw(LogException(ss.str()));
		}
		m_running = true;

	} catch(std::exception &ex)
	{
		if (m_acceptfd >= 0)
		{
			if (close(m_acceptfd) < 0)
			{
				abort();
			}
		}

		if (m_ctlfd[0] >= 0)
		{
			if (close(m_ctlfd[0]) < 0)
			{
				abort();
			}
		}

		if (m_ctlfd[1] >= 0)
		{
			if (close(m_ctlfd[1]) < 0)
			{
				abort();
			}
		}

		throw(ex);
	}
}


LogUnixServer::~LogUnixServer()
{
	if (m_running)
	{
		char value = 'Q';

		if (write(m_ctlfd[1], &value, sizeof(value)) != sizeof(value))
		{
			abort();
		}

		void *ret = NULL;
		if (pthread_join(m_thread, &ret) != 0)
		{
			abort();
		}
		m_running = false;
	}

	//No background thread. So no locking required from this point on

	while(!m_list.empty())
	{
		int fd = m_list.front();
		if (close(fd) < 0)
			abort();
		m_list.pop_front();
	}

	if (m_acceptfd >= 0)
	{
		if (close(m_acceptfd) < 0)
		{
			abort();
		}
	}

	if (m_ctlfd[0] >= 0)
	{
		if (close(m_ctlfd[0]) < 0)
		{
			abort();
		}
	}

	if (m_ctlfd[1] >= 0)
	{
		if (close(m_ctlfd[1]) < 0)
		{
			abort();
		}
	}

	if (pthread_mutex_destroy(&m_mutex) != 0)
		abort();

}

std::string LogUnixServer::GetName() const {
	return "UnixServer";
}

std::string LogUnixServer::GetDesc() const {
	return "Logs to client when they connect to the unix socket";
}

void LogUnixServer::Log(const LogType Type, const std::string &str) {
	char *msg = NULL;

	time_t current = time(NULL);
	struct tm timeinfo;
	char buf[128];

	localtime_r(&current, &timeinfo);
	strftime(buf, sizeof(buf), "%F %T", &timeinfo);

	if (asprintf(&msg, "%s - %s [PID: %d] - %s\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str()) < 0)
	{
		std::stringstream ss;
		ss << "asprintf failed error:" << strerror(errno);
		throw(LogException(ss.str()));
	}
	else
	{
		std::list<int> broken;
		int len = strlen(msg);

		Lock();

		for(auto fd : m_list)
		{
			ssize_t offset = 0;
			ssize_t ret = 0;
			do
			{
				ret = write(fd, msg + offset, len - offset);
				if (ret < 0)
				{
					switch(errno)
					{
						case EINTR:
							ret = 0; //Fudge this as if we didn't write anything
							break;
						default:
							break;
					}
				}
				else
				{
					offset += len;
				}
			} while(offset < len);

			if (ret < len || ret == 0)
			{
				broken.push_back(fd);
			}
		}

		//Kick any broken clients
		for(auto fd : broken)
		{
			if (close(fd) < 0)
			{
				abort();
			}
			m_list.remove(fd);
		}

		Unlock();

	}
	free(msg);
}

void LogUnixServer::Rotate()
{

}

void LogUnixServer::Lock()
{
	if (pthread_mutex_lock(&m_mutex) != 0)
		abort();
}

void LogUnixServer::Unlock()
{
	if (pthread_mutex_unlock(&m_mutex) != 0)
		abort();
}

void *LogUnixServer::Run(void *arg)
{
	LogUnixServer *self = (LogUnixServer *) arg;

	bool busy = true;
	while(busy)
	{
		struct pollfd fds[2];

		fds[0].fd = self->m_acceptfd;
		fds[0].events = POLLIN;
		fds[0].revents = 0;

		fds[1].fd = self->m_ctlfd[0];
		fds[1].events = POLLIN;
		fds[1].revents = 0;

		int ret = poll(fds, 2, 0);
		if (ret < 0)
		{
			switch(errno)
			{
				default:
					abort();
			}
		}

		if ( (fds[0].revents & POLLIN) ) {
			//Accept
			struct sockaddr_un addr;
			socklen_t addr_len = sizeof(addr);
			int nclient = accept(self->m_acceptfd, (struct sockaddr *) &addr, &addr_len);
			if (nclient >= 0)
			{
				self->Lock();
				self->m_list.push_back(nclient);
				self->Unlock();
			}
		}

		//Check eventfd and exit if it has data
		if ( (fds[1].revents & POLLIN) ) {
			busy = false;
		}

	}

	return NULL;
}

};


