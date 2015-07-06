
namespace liblogger
{
	enum LogType
	{
		LOGGER_DEBUG = 0,
		LOGGER_INFO,
		LOGGER_NOTICE,
		LOGGER_WARNING,
		LOGGER_ERR,
		LOGGER_CRIT,
		LOGGER_ALERT,
		LOGGER_EMERG,
	};

	const std::string LogTypeToStr(LogType Type);
};




