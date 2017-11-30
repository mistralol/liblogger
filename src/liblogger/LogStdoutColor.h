
namespace liblogger
{
	class LogStdoutColor : public ILogger
	{
		public:
			LogStdoutColor() { };
			virtual ~LogStdoutColor() { };

			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);
	};
};

