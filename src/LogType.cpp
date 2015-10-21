
#include <stdlib.h>
#include <liblogger.h>

namespace liblogger {

const std::string LogTypeToStr(LogType Type)
{
	switch(Type)
	{
		case LOGGER_DEBUG:
			return "DEBG";
		case LOGGER_INFO:
			return "INFO";
		case LOGGER_NOTICE:
			return "NOTE";
		case LOGGER_WARNING:
			return "WARN";
		case LOGGER_ERR:
			return "ERRO";
		case LOGGER_CRIT:
			return "CRIT";
		case LOGGER_ALERT:
			return "ALER";
		case LOGGER_EMERG:
			return "EMER";
		default:
			abort();
			break;
	}
	return ""; //Unreachable
}


};

