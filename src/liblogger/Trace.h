

namespace liblogger 
{
    class Trace {
        public:
            Trace(LogType type = LOGGER_CRIT);
            ~Trace();

            void Log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
            void Cancel();

            void Lock();
            void Unlock();

        private:
            LogMutex m_mutex;
            LogType m_type;
            std::list<std::string> m_lst;
            bool m_active;
    };
};
