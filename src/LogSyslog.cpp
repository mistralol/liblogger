
#include <stdlib.h>
#include <syslog.h>

#include "liblogger.h"

namespace liblogger
{

void LogSyslog::GetName(std::string *str)
{
	*str = "Syslog";
}

void LogSyslog::GetDesc(std::string *str)
{
	*str = "Logs to Syslog";
}

void LogSyslog::Log(const LogType Type, const std::string &str)
{
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

