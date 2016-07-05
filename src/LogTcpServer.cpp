
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sstream>

#include <poll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/eventfd.h>

#include "liblogger.h"

namespace liblogger
{

LogTcpServer::LogTcpServer(int port) :
	m_port(port),
	m_acceptfd(-1),
	m_eventfd(-1),
	m_running(false)
{
	try
	{
		if (pthread_mutex_init(&m_mutex, NULL) != 0)
			abort();
	
		m_acceptfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_acceptfd < 0)
		{
			std::stringstream ss;
			ss << "Cannot create socket: " << strerror(errno);
			throw(LogException(ss.str()));
		}
	
		m_eventfd = eventfd(0, 0);
		if (m_eventfd < 0)
		{
			std::stringstream ss;
			ss << "Cannot create eventfd: " << strerror(errno);
			throw(LogException(ss.str()));
		}

		//Set SO_REUSEADDR so re can rebind on a port
		int value = 1;
		socklen_t vallen(sizeof(value));
		if (setsockopt(m_acceptfd, SOL_SOCKET, SO_REUSEADDR, &value, vallen) < 0)
		{
			std::stringstream ss;
			ss << "Cannot set SO_REUSEADDR on socket: " << strerror(errno);
			throw(LogException(ss.str()));
		}

		//Bind etc..
		struct sockaddr_in serv_addr;
		socklen_t sockaddr_len = sizeof(serv_addr);
		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(port);
		if (bind(m_acceptfd, (struct sockaddr *) &serv_addr, sockaddr_len) < 0)
		{
			std::stringstream ss;
			ss << "Cannot bind to port: " << port << " error: " << strerror(errno);
			throw(LogException(ss.str()));
		}
		
		if (listen(m_acceptfd, 15) < 0)
		{
			std::stringstream ss;
			ss << "Cannot listen on port: " << port << " error: " << strerror(errno);
			throw(LogException(ss.str()));
		}

		//Create thread
		if (pthread_create(&m_thread, NULL, LogTcpServer::Run, this) != 0)
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

		if (m_eventfd >= 0)
		{
			if (close(m_eventfd) < 0)
			{
				abort();
			}
		}

		throw(ex);
	}
}


LogTcpServer::~LogTcpServer()
{
	if (m_running)
	{
		uint64_t value = 1;
		
		if (write(m_eventfd, &value, sizeof(value)) != sizeof(value))
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
	
	if (m_eventfd >= 0)
	{
		if (close(m_eventfd) < 0)
		{
			abort();
		}
	}
	
	if (pthread_mutex_destroy(&m_mutex) != 0)
		abort();

}

void LogTcpServer::GetName(std::string *str)
{
	*str = "TcpServer";
}

void LogTcpServer::GetDesc(std::string *str)
{
	*str = "Logs to client when they connect to the tcp port";
}

void LogTcpServer::Log(const LogType Type, const std::string &str)
{
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
			//FIXME: deal with short write
			ssize_t ret = write(fd, msg, len);
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

void LogTcpServer::Rotate()
{

}

void LogTcpServer::Lock()
{
	if (pthread_mutex_lock(&m_mutex) != 0)
		abort();
}

void LogTcpServer::Unlock()
{
	if (pthread_mutex_unlock(&m_mutex) != 0)
		abort();
}

void *LogTcpServer::Run(void *arg)
{
	LogTcpServer *self = (LogTcpServer *) arg;

	bool busy = true;
	while(busy)
	{
		struct pollfd fds[2];
		
		fds[0].fd = self->m_acceptfd;
		fds[0].events = POLLIN;
		fds[0].revents = 0;
		
		fds[1].fd = self->m_eventfd;
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
			struct sockaddr_in addr;			
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


