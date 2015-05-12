
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

			static bool GetAddSeq();
			static void SetAddSeq(bool bEnabled);

			static bool GetAddDate();
			static void SetAddDate(bool bEnabled);

			static std::string GetDateFormat();
			static void SetDateFormat(const std::string &str);

			static bool GetAddProcessName();
			static void SetAddProcessName(bool bEnabled);

			static std::string GetProcessName();
			static void SetProcessName(const std::string &str);

			static bool GetAddProcessID();
			static void SetAddProcessID(bool bEnabled);

			static bool GetAddThreadID();
			static void SetAddThreadID(bool bEnabled);

			static bool GetAddSeperator();
			static void SetAddSeperator(bool bEnabled);

		private:
			static std::list<ILogger *> m_loggers;
			static pthread_mutex_t m_mutex;
			static bool m_locked;
			static std::string m_DateFormat;
			static std::string m_ProcessName;

			static bool m_AddSeq;
			static bool m_AddDate;
			static bool m_AddProcessName;
			static bool m_AddProcessID;
			static bool m_AddThreadID;
			static bool m_AddSeperator;

			static uint64_t m_TotalMessages;
	};
};

