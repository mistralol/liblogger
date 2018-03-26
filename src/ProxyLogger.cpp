
#include <liblogger.h>

namespace liblogger
{

ProxyLogger::ProxyLogger() :
    m_prefix("")
{

}

ProxyLogger::ProxyLogger(const std::string &prefix) :
    m_prefix(prefix)
{

}

void ProxyLogger::Logger(const LogType Type, const std::string &str) {
    liblogger::Logger(Type, str);
}

void ProxyLogger::Logger(const LogType Type, const char *fmt, ...) {
    char *tmp = 0;
	va_list ap;
	va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	liblogger::Logger(Type, "%s %s ", m_prefix.c_str(), str.c_str());
	free(tmp);
	va_end(ap);
}

void ProxyLogger::Logger(const char *fmt, ...) {
	char *tmp = 0;
	va_list ap;
	va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	liblogger::Logger(LOGGER_INFO, "%s %s ", m_prefix.c_str(), str.c_str());
	free(tmp);
	va_end(ap);
}

void ProxyLogger::Logger(const std::string &str) {
    Logger(LOGGER_INFO, str);
}

/* Cleaner Aliases for the above */
void ProxyLogger::LogDebug(const char *fmt, ...) {
	char *tmp = 0;
	va_list ap;
	va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	liblogger::Logger(LOGGER_DEBUG, "%s %s ", m_prefix.c_str(), str.c_str());
	free(tmp);
	va_end(ap);
}

void ProxyLogger::LogDebug(const std::string &str) {
    Logger(LOGGER_DEBUG, str);
}

void ProxyLogger::LogInfo(const char *fmt, ...) {
	char *tmp = 0;

	va_list ap;
	va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	liblogger::Logger(LOGGER_INFO, "%s %s ", m_prefix.c_str(), str.c_str());
	free(tmp);
	va_end(ap);
}

void ProxyLogger::LogInfo(const std::string &str) {
    Logger(LOGGER_INFO, str);
}

void ProxyLogger::LogNotice(const char *fmt, ...) {
	char *tmp = 0;

	va_list ap;
	va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	liblogger::Logger(LOGGER_NOTICE, "%s %s ", m_prefix.c_str(), str.c_str());
	free(tmp);
	va_end(ap);
}

void ProxyLogger::LogNotice(const std::string &str) {
    Logger(LOGGER_NOTICE, str);
}

void ProxyLogger::LogWarning(const char *fmt, ...) {
	char *tmp = 0;

	va_list ap;
	va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	liblogger::Logger(LOGGER_WARNING, "%s %s ", m_prefix.c_str(), str.c_str());
	free(tmp);
	va_end(ap);
}

void ProxyLogger::LogWarning(const std::string &str) {
    Logger(LOGGER_WARNING, str);
}

void ProxyLogger::LogError(const char *fmt, ...) {
	char *tmp = 0;

	va_list ap;
	va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	liblogger::Logger(LOGGER_ERR, "%s %s ", m_prefix.c_str(), str.c_str());
	free(tmp);
	va_end(ap);
}

void ProxyLogger::LogError(const std::string &str) {
    Logger(LOGGER_ERR, str);
}

void ProxyLogger::LogCritical(const char *fmt, ...) {
	char *tmp = 0;

	va_list ap;
	va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	liblogger::Logger(LOGGER_CRIT, "%s %s ", m_prefix.c_str(), str.c_str());
	free(tmp);
	va_end(ap);
}

void ProxyLogger::LogCritical(const std::string &str) {
    Logger(LOGGER_CRIT, str);
}

void ProxyLogger::LogAlert(const char *fmt, ...) {
	char *tmp = 0;

	va_list ap;
	va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	liblogger::Logger(LOGGER_ALERT, "%s %s ", m_prefix.c_str(), str.c_str());
	free(tmp);
	va_end(ap);
}

void ProxyLogger::LogAlert(const std::string &str) {
    Logger(LOGGER_ALERT, str);
}

void ProxyLogger::LogEmergency(const char *fmt, ...) {
	char *tmp = 0;
	va_list ap;
	va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
	std::string str = tmp;
	liblogger::Logger(LOGGER_EMERG, "%s %s ", m_prefix.c_str(), str.c_str());
	free(tmp);
	va_end(ap);
}

void ProxyLogger::LogEmergency(const std::string &str) {
    liblogger::Logger(LOGGER_EMERG, str);
}

};
