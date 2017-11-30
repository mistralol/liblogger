
namespace liblogger
{
	class LogSyslog : public ILogger
	{
		public:
			LogSyslog();
			LogSyslog(const std::string &ident);
			LogSyslog(const std::string &ident, int options);
			LogSyslog(const std::string &ident, int options, int facility);
			LogSyslog(int facility);
			virtual ~LogSyslog();

			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);
	};
};

