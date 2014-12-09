
namespace liblogger
{
	class LogSyslog : public ILogger
	{
		public:
			LogSyslog();
			LogSyslog(int facility);
			virtual ~LogSyslog();
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);
	};
};

