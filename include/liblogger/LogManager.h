
namespace liblogger {
	class LogManager {
		public:
			static void Init();
		
			static void Add(ILogger *Log);

			static void Send(LogType Type, std::string str);

			static void Remove(ILogger *Log);
			static void RemoveAll(bool destroy);
		
			static void Lock();
			static void Unlock();

			static bool GetThreadPrefix();
			static void SetThreadPrefix(bool value);
		
			static bool GetProcessPrefix();
			static void SetProcessPrefix(bool value);

		private:
			static std::list<ILogger *> m_loggers;
			static pthread_mutex_t m_mutex;
			static bool m_locked;
			static bool m_threadprefix;
			static bool m_processprefix;
	};
};

