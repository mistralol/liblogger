
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sstream>
#include "liblogger.h"

namespace liblogger
{

void LogStderr::GetName(std::string *str)
{
	*str = "Stderr";
}

void LogStderr::GetDesc(std::string *str)
{
	*str = "Logs to Stderr";
}

void LogStderr::Log(const LogType Type, const std::string &str)
{
	time_t current = time(NULL);
	struct tm timeinfo;
	char buf[128];
	
	localtime_r(&current, &timeinfo);
	if (strftime(buf, sizeof(buf), "%F %T", &timeinfo) == 0)
		abort(); //Bug

	if (fprintf(stderr, "%s - %s [PID: %d] - %s\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str()) < 0)
	{
		std::stringstream ss;
		ss << "failed to write to stderr error:" << strerror(errno);
		throw(LogException(ss.str()));
	}
	if (fflush(stderr) < 0)
	{
		std::stringstream ss;
		ss << "failed to flush to stderr error:" << strerror(errno);
		throw(LogException(ss.str()));
	}
}

};
