
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sstream>

#include "liblogger.h"

namespace liblogger
{

LogPipe::LogPipe(const std::string command) :
	m_command(command)
{
	m_fp = popen(m_command.c_str(), "w");
	if (!m_fp)
	{
		std::stringstream ss;
		ss << "failed to open pipe '" << m_command << "'";
		throw(LogException(ss.str()));
	}
}

LogPipe::~LogPipe()
{
	if (m_fp != NULL)
	{
		if (pclose(m_fp) < 0)
		{
			std::stringstream ss;
			ss << "failed to close pipe '" << m_command << "' error:" << strerror(errno);
			throw(LogException(ss.str()));
		}
	}
}

void LogPipe::GetName(std::string *str)
{
	*str = "File";
}

void LogPipe::GetDesc(std::string *str)
{
	*str = "Logs to a File";
}

void LogPipe::Log(const LogType Type, const std::string &str)
{
	if (m_fp == NULL)
		return;
		
	time_t current = time(NULL);
	struct tm timeinfo;
	char buf[128];
	
	localtime_r(&current, &timeinfo);
	if (strftime(buf, sizeof(buf), "%F %T", &timeinfo) == 0)
		abort(); //Bug

	if (fprintf(m_fp, "%s - %s [PID: %d] - %s\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str()) < 0)
	{
		std::stringstream ss;
		ss << "failed to write to pipe '" << m_command << "' error:" << strerror(errno);
		throw(LogException(ss.str()));
	}
	if (fflush(m_fp) < 0)
	{
		std::stringstream ss;
		ss << "failed to flush to pipe '" << m_command << "' error:" << strerror(errno);
		throw(LogException(ss.str()));
	}
}

};

