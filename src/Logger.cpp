
#include <stdlib.h>
#include <list>

#include "liblogger.h"

namespace liblogger {

void Logger(const LogType Type, const std::string &str) {
	LogManager::Send(Type, str);
}

void Logger(LogType Type, const char *fmt, ...) {
	char *tmp = 0;
	
    va_list ap;
    va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	Logger(Type, str);
	free(tmp);
    va_end(ap);
}

void Logger(const char *fmt, ...) {
	char *tmp = 0;
	
    va_list ap;
    va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	Logger(LOGGER_INFO, str);
	free(tmp);
    va_end(ap);
}

void Logger(const std::string &str) {
	Logger(LOGGER_INFO, str);
}

};
