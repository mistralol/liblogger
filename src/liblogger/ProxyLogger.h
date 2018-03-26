
namespace liblogger
{
    class ProxyLogger {
        public:
            ProxyLogger();
            ProxyLogger(const std::string &prefix);

            void Logger(const LogType Type, const std::string &str);
            void Logger(const LogType Type, const char *fmt, ...) __attribute__ ((format (printf, 3, 4)));
            void Logger(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
            void Logger(const std::string &str);

            /* Cleaner Aliases for the above */
            void LogDebug(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
            void LogDebug(const std::string &str);
            void LogInfo(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
            void LogInfo(const std::string &str);
            void LogNotice(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
            void LogNotice(const std::string &str);
            void LogWarning(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
            void LogWarning(const std::string &str);
            void LogError(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
            void LogError(const std::string &str);
            void LogCritical(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
            void LogCritical(const std::string &str);
            void LogAlert(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
            void LogAlert(const std::string &str);
            void LogEmergency(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
            void LogEmergency(const std::string &str);

        private:
            std::string m_prefix;
    };
};
