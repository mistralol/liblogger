
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sstream>
#include "liblogger.h"

namespace liblogger
{

void LogStdout::GetName(std::string *str)
{
	*str = "Stdout";
}

void LogStdout::GetDesc(std::string *str)
{
	*str = "Logs to Stdout";
}

void LogStdout::Log(const LogType Type, const std::string &str)
{
	time_t current = time(NULL);
	struct tm timeinfo;
	char buf[128];
	
	localtime_r(&current, &timeinfo);
	strftime(buf, sizeof(buf), "%F %T", &timeinfo);

	if (fprintf(stdout, "%s - %s [PID: %d] - %s\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str()) < 0)
	{
		std::stringstream ss;
		ss << "failed to write to stdout error:" << strerror(errno);
		throw(LogException(ss.str()));
	}
	fflush(stdout);
}

};

