

namespace liblogger {

	/* Global Functions for logging */
	extern void Logger(LogType Type, std::string str);
	extern void Logger(LogType Type, const char *fmt, ...);
	extern void Logger(const char *fmt, ...);
	extern void Logger(const std::string str);

};

