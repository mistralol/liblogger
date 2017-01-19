

namespace liblogger
{
	/* Global Functions for logging */
	extern void Logger(const LogType Type, const std::string &str);
	extern void Logger(const LogType Type, const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
	extern void Logger(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
	extern void Logger(const std::string &str);

	/* Cleaner Aliases for the above */
	extern void LogDebug(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
	extern void LogDebug(const std::string &str);
	extern void LogInfo(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
	extern void LogInfo(const std::string &str);
	extern void LogNotice(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
	extern void LogNotice(const std::string &str);
	extern void LogWarning(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
	extern void LogWarning(const std::string &str);
	extern void LogError(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
	extern void LogError(const std::string &str);
	extern void LogCritical(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
	extern void LogCritical(const std::string &str);
	extern void LogAlert(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
	extern void LogAlert(const std::string &str);
	extern void LogEmergency(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
	extern void LogEmergency(const std::string &str);

	/* Ask for log rotation */
	extern void LoggerRotate();
};


