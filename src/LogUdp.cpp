
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sstream>

#include <arpa/inet.h>
#include <sys/socket.h>

#include "liblogger.h"

namespace liblogger
{

LogUdp::LogUdp(const std::string addr, int port) :
	m_addr(addr),
	m_port(port),
	m_fd(-1),
	m_ignoreerrors(false)
{
	m_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_fd < 0)
	{
		std::stringstream ss;
		ss << "Cannot create socket: " << strerror(errno);
		throw(LogException(ss.str()));
	}
	
	int localport = 1025;
	
	bool bound = false;
	for(int i = 0 ;i<50;i++)
	{
		struct sockaddr_in local;
		socklen_t locallen = sizeof(local);
		memset(&local, 0, sizeof(local));
		local.sin_family = AF_INET;
		local.sin_addr.s_addr = INADDR_ANY;
		local.sin_port = htons(localport + i);

		if (bind(m_fd, (struct sockaddr *) &local, locallen) == 0)
		{
			localport += i;
			bound = true;
			break;
		}
	}
	
	if (bound == false)
	{
		if (close(m_fd) < 0)
			abort();
		m_fd = -1;
		throw(LogException("Unable to bind socket"));
	}
	
	struct sockaddr_in dest;
	socklen_t destlen = sizeof(dest);
	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(addr.c_str());
	dest.sin_port = htons(m_port);
	
	int ret = connect(m_fd, (struct sockaddr *) &dest, destlen);
	if (ret < 0)
	{
		std::stringstream ss;
		ss << "Cannot connect to " << addr << ":" << port << " error: " << strerror(errno);
		if (close(m_fd) < 0)
			abort();
		m_fd = -1;
		throw(LogException(ss.str()));
	}
}

LogUdp::~LogUdp()
{
	if (m_fd >= 0)
		close(m_fd);
}

void LogUdp::GetName(std::string *str)
{
	*str = "Udp4";
}

void LogUdp::GetDesc(std::string *str)
{
	*str = "Logs to a Udp port";
}

void LogUdp::Log(const LogType Type, const std::string &str)
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
		if (m_ignoreerrors)
			return;
		throw(LogException(ss.str()));
	}
	else
	{
		int len = strlen(msg);
		ssize_t ret = send(m_fd, msg, len, 0);
		if (ret < 0)
		{
			std::stringstream ss;
			ss << "write failed error:" << strerror(errno);
			free(msg);
			if (m_ignoreerrors)
				return;
			throw(LogException(ss.str()));
		}
		if (ret != len)
		{
			std::stringstream ss;
			ss << "Short write only wrote " << ret << " instead of " << len << " error:" << strerror(errno);
			free(msg);
			if (m_ignoreerrors)
				return;
			throw(LogException(ss.str()));
		}
	}
	free(msg);
}

void LogUdp::Rotate()
{

}

void LogUdp::SetIgnoreErrors(bool value)
{
	m_ignoreerrors = value;
}

};

