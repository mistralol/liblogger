
#include <stdlib.h>
#include <list>

#include "liblogger.h"

namespace liblogger
{

void Logger(const LogType Type, const std::string &str)
{
	LogManager::Send(Type, str);
}

void Logger(LogType Type, const char *fmt, ...)
{
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

void Logger(const char *fmt, ...)
{
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

void Logger(const std::string &str)
{
	Logger(LOGGER_INFO, str);
}

void LogDebug(const char *fmt, ...)
{
	char *tmp = 0;
	
    va_list ap;
    va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	Logger(LOGGER_DEBUG, str);
	free(tmp);
    va_end(ap);
}

void LogDebug(const std::string &str)
{
	LogDebug("%s", str.c_str());
}

void LogInfo(const char *fmt, ...)
{
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

void LogInfo(const std::string &str)
{
	LogInfo("%s", str.c_str());
}

void LogNotice(const char *fmt, ...)
{
	char *tmp = 0;
	
    va_list ap;
    va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	Logger(LOGGER_NOTICE, str);
	free(tmp);
    va_end(ap);
}

void LogNotice(const std::string &str)
{
	LogNotice("%s", str.c_str());
}

void LogWarning(const char *fmt, ...)
{
	char *tmp = 0;
	
    va_list ap;
    va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	Logger(LOGGER_WARNING, str);
	free(tmp);
    va_end(ap);
}

void LogWarning(const std::string &str)
{
	LogWarning("%s", str.c_str());
}

void LogError(const char *fmt, ...)
{
	char *tmp = 0;
	
    va_list ap;
    va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	Logger(LOGGER_ERR, str);
	free(tmp);
    va_end(ap);
}

void LogError(const std::string &str)
{
	LogError("%s", str.c_str());
}

void LogCritical(const char *fmt, ...)
{
	char *tmp = 0;
	
    va_list ap;
    va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	Logger(LOGGER_CRIT, str);
	free(tmp);
    va_end(ap);
}

void LogCritical(const std::string &str)
{
	LogCritical("%s", str.c_str());
}

void LogAlert(const char *fmt, ...)
{
	char *tmp = 0;
	
    va_list ap;
    va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	Logger(LOGGER_ALERT, str);
	free(tmp);
    va_end(ap);
}

void LogAlert(const std::string &str)
{
	LogAlert("%s", str.c_str());
}

void LogEmergency(const char *fmt, ...)
{
	char *tmp = 0;
	
    va_list ap;
    va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	Logger(LOGGER_EMERG, str);
	free(tmp);
    va_end(ap);
}

void LogEmergency(const std::string &str)
{
	LogEmergency("%s", str.c_str());
}

void LoggerRotate()
{
	LogManager::Rotate();
}

};
