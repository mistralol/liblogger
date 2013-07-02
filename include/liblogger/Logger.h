

namespace liblogger {

	/* Global Functions for logging */
	extern void Logger(const LogType Type, const std::string &str);
	extern void Logger(const LogType Type, const char *fmt, ...);
	extern void Logger(const char *fmt, ...);
	extern void Logger(const std::string &str);
};


