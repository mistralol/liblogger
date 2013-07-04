
namespace liblogger 
{
	class LogManager 
	{
		public:
			static void Init();
		
			static void Add(ILogger *Log);

			static void Send(const LogType Type, const std::string &str);

			static void Rotate();

			static void Remove(ILogger *Log);
			static void RemoveAll(bool destroy);
		
			static void Lock();
			static void Unlock();

			static bool GetThreadPrefixEnabled();
			static void SetThreadPrefixEnabled(bool bEnabled);
		
			static bool GetProcessPrefixEnabled();
			static void SetProcessPrefixEnabled(bool bEnabled);

		private:
			static std::list<ILogger *> m_loggers;
			static pthread_mutex_t m_mutex;
			static bool m_locked;
			static bool m_threadprefix;
			static bool m_processprefix;
	};
};

