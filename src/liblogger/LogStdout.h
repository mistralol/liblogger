
namespace liblogger
{
	class LogStdout : public ILogger
	{
		public:
			LogStdout() { };
			virtual ~LogStdout() { };
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);
	};
};

