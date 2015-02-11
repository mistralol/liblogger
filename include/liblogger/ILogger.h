

namespace liblogger
{
	class ILogger
	{
		public:
			ILogger() { }
			virtual ~ILogger() { }

			virtual void GetName(std::string *str) { };
			virtual void GetDesc(std::string *str) { };

			virtual void Rotate() { Log(LOGGER_INFO, "LogRorate"); };
			virtual void Log(const LogType Type, const std::string &str) { };

			virtual bool AddSeq() { return true; }
			virtual bool AddDate() { return true; }
			virtual bool AddProcessName() { return true; }
			virtual bool AddProcessID() { return true; }
			virtual bool AddThreadID() { return true; }
			virtual bool AddSeperator() { return true; }
	};
};


