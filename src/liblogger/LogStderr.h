
namespace liblogger {
	class LogStderr : public ILogger
	{
		public:
			LogStderr() { };
			virtual ~LogStderr() { };

			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);
	};
};

