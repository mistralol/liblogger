
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sstream>

#include "liblogger.h"

namespace liblogger
{

LogFile::LogFile(const std::string fname)
{
	m_fname = fname;
	m_fp = fopen(m_fname.c_str(), "a");
	if (m_fp == NULL)
	{
		std::stringstream ss;
		ss << "Cannot open file: '" << fname << "'";
		throw(LogException(ss.str()));
	}
}

LogFile::~LogFile()
{
	if (m_fp != NULL)
		fclose(m_fp);		
}

void LogFile::GetName(std::string *str)
{
	*str = "File";
}

void LogFile::GetDesc(std::string *str)
{
	*str = "Logs to a File";
}

void LogFile::Log(const LogType Type, const std::string &str)
{
	if (m_fp == NULL)
		return;
	
	time_t current = time(NULL);
	struct tm timeinfo;
	char buf[128];
	
	localtime_r(&current, &timeinfo);
	strftime(buf, sizeof(buf), "%F %T", &timeinfo);

	if (fprintf(m_fp, "%s - %s [PID: %d] - %s\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str()) < 0)
	{
		std::stringstream ss;
		ss << "failed to write to file '" << m_fname.c_str() << "' error:" << strerror(errno);
		throw(LogException(ss.str()));
	}
	fflush(m_fp);
}

void LogFile::Rotate()
{
	if (m_fp != NULL)
	{
		fclose(m_fp);
	}

	m_fp = fopen(m_fname.c_str(), "a");
	if (m_fp == NULL)
	{
		std::stringstream ss;
		ss << "Cannot open file: '" << m_fname << "'";
		throw(LogException(ss.str()));
	}
}

};

