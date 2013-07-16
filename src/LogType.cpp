
#include <stdlib.h>
#include <liblogger.h>

namespace liblogger {

const std::string LogTypeToStr(LogType Type)
{
	switch(Type)
	{
		case LOGGER_DEBUG:
			return "DEBUG";
		case LOGGER_INFO:
			return "INFO";
		case LOGGER_NOTICE:
			return "NOTICE";
		case LOGGER_WARNING:
			return "WARNING";
		case LOGGER_ERR:
			return "ERROR";
		case LOGGER_CRIT:
			return "CRITICAL";
		case LOGGER_ALERT:
			return "ALERT";
		case LOGGER_EMERG:
			return "EMERGENCY";
		default:
			abort();
			break;
	}
	return "";
}


};

