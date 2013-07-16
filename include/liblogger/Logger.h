

namespace liblogger
{
	/* Global Functions for logging */
	extern void Logger(const LogType Type, const std::string &str);
	extern void Logger(const LogType Type, const char *fmt, ...);
	extern void Logger(const char *fmt, ...);
	extern void Logger(const std::string &str);

	extern void LogDebug(const char *fmt, ...);
	extern void LogDebug(const std::string &str);
	extern void LogInfo(const char *fmt, ...);
	extern void LogInfo(const std::string &str);
	extern void LogNotice(const char *fmt, ...);
	extern void LogNotice(const std::string &str);
	extern void LogWarning(const char *fmt, ...);
	extern void LogWarning(const std::string &str);
	extern void LogError(const char *fmt, ...);
	extern void LogError(const std::string &str);
	extern void LogCritical(const char *fmt, ...);
	extern void LogCritical(const std::string &str);
	extern void LogAlert(const char *fmt, ...);
	extern void LogAlert(const std::string &str);
	extern void LogEmergency(const char *fmt, ...);
	extern void LogEmergency(const std::string &str);


	/* Ask for log rotation */
	extern void LoggerRotate();
};


