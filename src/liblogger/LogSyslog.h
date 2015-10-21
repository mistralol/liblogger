
namespace liblogger
{
	class LogSyslog : public ILogger
	{
		public:
			LogSyslog();
			LogSyslog(const std::string ident);
			LogSyslog(const std::string ident, int options);
			LogSyslog(const std::string ident, int options, int facility);
			LogSyslog(int facility);
			virtual ~LogSyslog();
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);
	};
};

