
#include <stdlib.h>
#include <syslog.h>

#include "liblogger.h"

namespace liblogger
{

LogSyslog::LogSyslog()
{
	openlog(NULL, LOG_PID, 0);
}

LogSyslog::LogSyslog(const std::string &ident)
{
	openlog(ident.c_str(), LOG_PID, 0);
}

LogSyslog::LogSyslog(const std::string &ident, int options)
{
	openlog(ident.c_str(), options, 0);
}

LogSyslog::LogSyslog(const std::string &ident, int options, int facility)
{
	openlog(ident.c_str(), options, facility);
}


LogSyslog::LogSyslog(int facility)
{
	openlog(NULL, LOG_PID, facility);
}

LogSyslog::~LogSyslog()
{
	closelog();
}

std::string LogSyslog::GetName() const {
	return "Syslog";
}

std::string LogSyslog::GetDesc() const {
	return "Logs to a syslog";
}

void LogSyslog::Log(const LogType Type, const std::string &str) {
	switch(Type)
	{
		case LOGGER_DEBUG:
			syslog(LOG_DEBUG, "%s", str.c_str());
			break;
		case LOGGER_INFO:
			syslog(LOG_INFO, "%s", str.c_str());
			break;
		case LOGGER_NOTICE:
			syslog(LOG_NOTICE, "%s", str.c_str());
			break;
		case LOGGER_WARNING:
			syslog(LOG_WARNING, "%s", str.c_str());
			break;
		case LOGGER_ERR:
			syslog(LOG_ERR, "%s", str.c_str());
			break;
		case LOGGER_CRIT:
			syslog(LOG_CRIT, "%s", str.c_str());
			break;
		case LOGGER_ALERT:
			syslog(LOG_ALERT, "%s", str.c_str());
			break;
		case LOGGER_EMERG:
			syslog(LOG_EMERG, "%s", str.c_str());
			break;
		default:
			abort();
			break;
	}
}

};

