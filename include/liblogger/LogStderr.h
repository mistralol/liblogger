
namespace liblogger {
	class LogStderr : public ILogger
	{
		public:
			LogStderr() { };
			virtual ~LogStderr() { };
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(LogType Type, const std::string str);
	};
};

