
namespace liblogger
{
	class LogStdoutColor : public ILogger
	{
		public:
			LogStdoutColor() { };
			virtual ~LogStdoutColor() { };
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);
	};
};

