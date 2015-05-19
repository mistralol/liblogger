
#include <stdio.h>

#include "liblogger.h"

namespace liblogger
{

LogPipe::LogPipe(const std::string command)
{
	m_command = command;
	m_fp = popen(m_command.c_str(), "w");
}

LogPipe::~LogPipe()
{
	if (m_fp != NULL)
		pclose(m_fp);		
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
	strftime(buf, sizeof(buf), "%F %T", &timeinfo);

	fprintf(m_fp, "%s - %s [PID: %d] - %s\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str());
	fflush(m_fp);
}

};

