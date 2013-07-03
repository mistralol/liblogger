
namespace liblogger
{
	class LogSyslog : public ILogger
	{
		public:
			LogSyslog() { };
			virtual ~LogSyslog() { };
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(LogType Type, const std::string str);
	};
};

