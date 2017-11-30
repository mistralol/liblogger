
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sstream>
#include "liblogger.h"

namespace liblogger
{

std::string LogStdout::GetName() const {
	return "Stdout";
}

std::string LogStdout::GetDesc() const {
	return "Logs to a Stdout";
}

void LogStdout::Log(const LogType Type, const std::string &str) {
	time_t current = time(NULL);
	struct tm timeinfo;
	char buf[128];

	localtime_r(&current, &timeinfo);
	if (strftime(buf, sizeof(buf), "%F %T", &timeinfo) == 0)
		abort(); //Bug

	if (fprintf(stdout, "%s - %s [PID: %d] - %s\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str()) < 0)
	{
		std::stringstream ss;
		ss << "failed to write to stdout error:" << strerror(errno);
		throw(LogException(ss.str()));
	}
	if (fflush(stdout) < 0)
	{
		std::stringstream ss;
		ss << "failed to flush to stdout error:" << strerror(errno);
		throw(LogException(ss.str()));
	}
}

};

