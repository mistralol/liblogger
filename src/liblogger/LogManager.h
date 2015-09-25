
namespace liblogger 
{
	class LogManager 
	{
		public:
			static void Add(ILogger *Log);

			static void Send(const LogType Type, const std::string &str);

			static void Rotate();

			static void Remove(ILogger *Log);
			static void RemoveAll(bool destroy);

			static std::string GetVersion();
		
			static void Lock();
			static void Unlock();
			
			static void SetLevel(LogType Type);
			static LogType GetLevel();

		private:
			static std::list<ILogger *> m_loggers;
			static pthread_mutex_t m_mutex;
			static bool m_locked;
			static LogType m_Type;

			static uint64_t m_TotalMessages;
	};
};

