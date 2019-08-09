

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

#define LogOnce(type, str, ...) {\
	static bool HasLogged = false; \
	if (!HasLogged) { \
		HasLogged = true; \
		Logger(type, str, __VA_ARGS__); \
	} \
}

#define LogPeriod(interval, type, str, ...) {\
	static struct timespec LogLast = {0, 0}; \
	struct timespec LogNow; \
	if (clock_gettime(CLOCK_MONOTONIC, &LogNow) != 0) abort(); \
	if (LogNow.tv_sec > LogLast.tv_sec + interval) {\
		LogLast = LogNow; \
		Logger(type, str, __VA_ARGS__); \
	} \
}


	/* Ask for log rotation */
	extern void LoggerRotate();
};


