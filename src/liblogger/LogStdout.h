
namespace liblogger
{
	class LogStdout : public ILogger
	{
		public:
			LogStdout() { };
			virtual ~LogStdout() { };

			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);
	};
};

