
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

void LogPipe::Log(LogType Type, const std::string str)
{
	if (m_fp == NULL)
		return;

	fprintf(m_fp, "%s\n", str.c_str());
	fflush(m_fp);
}

};

