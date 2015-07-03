
#include <stdio.h>

#include "liblogger.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

namespace liblogger
{

void LogStdoutColor::GetName(std::string *str)
{
	*str = "StdoutColor";
}

void LogStdoutColor::GetDesc(std::string *str)
{
	*str = "Logs to Stdout Colored";
}

void LogStdoutColor::Log(const LogType Type, const std::string &str)
{
	time_t current = time(NULL);
	struct tm timeinfo;
	char buf[128];
	
	localtime_r(&current, &timeinfo);
	strftime(buf, sizeof(buf), "%F %T", &timeinfo);

	switch(Type)
	{
		case LOGGER_DEBUG:
			fprintf(stdout, COLOR_BLUE "%s - %s [PID: %d] - %s" COLOR_RESET "\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str());
			break;
		case LOGGER_INFO:
			fprintf(stdout, COLOR_GREEN "%s - %s [PID: %d] - %s" COLOR_RESET "\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str());
			break;
		case LOGGER_NOTICE:
			fprintf(stdout, COLOR_GREEN "%s - %s [PID: %d] - %s" COLOR_RESET "\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str());
			break;
		case LOGGER_WARNING:
			fprintf(stdout, COLOR_YELLOW "%s - %s [PID: %d] - %s" COLOR_RESET "\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str());
			break;
		case LOGGER_ERR:
			fprintf(stdout, COLOR_RED "%s - %s [PID: %d] - %s" COLOR_RESET "\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str());
			break;
		case LOGGER_CRIT:
			fprintf(stdout, COLOR_MAGENTA "%s - %s [PID: %d] - %s" COLOR_RESET "\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str());
			break;
		case LOGGER_ALERT:
			fprintf(stdout, COLOR_CYAN "%s - %s [PID: %d] - %s" COLOR_RESET "\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str());
			break;
		case LOGGER_EMERG:
			fprintf(stdout, COLOR_CYAN "%s - %s [PID: %d] - %s" COLOR_RESET "\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str());
			break;
	}

	fflush(stdout);
}

};

