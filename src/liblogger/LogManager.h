
namespace liblogger 
{
	class LogManager 
	{
		public:
			static void Send(const LogType Type, const std::string &str);
			static void Rotate();

			static void Add(ILogger *Log);
			static void Add(std::shared_ptr<ILogger> Log);
			static void Remove(std::shared_ptr<ILogger> Log);
			static void RemoveAll();

			static void FilterAdd(ILogFilter *filter);
			static void FilterAdd(std::shared_ptr<ILogFilter> filter);
			static void FilterRemove(std::shared_ptr<ILogFilter> filter);
			static void FilterRemoveAll();

			static std::string GetVersion();
		
			static void Lock();
			static void Unlock();
			
			static void SetLevel(LogType Type);
			static LogType GetLevel();
			
			static void SetCatchErrors(bool enable);
			static bool GetCatchErrors();

		private:
			static std::list<std::shared_ptr<ILogger> > m_loggers;
			static std::list<std::shared_ptr<ILogFilter> > m_filters;
			static pthread_mutex_t m_mutex;
			static bool m_locked;
			static bool m_catcherrors;
			static LogType m_Type;

			static uint64_t m_TotalMessages;
			static uint64_t m_TotalDroppedMessages;
			static uint64_t m_TotalErrors;
			static uint64_t m_TotalFiltered;
	};
};

