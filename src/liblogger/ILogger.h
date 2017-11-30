

namespace liblogger
{
	class ILogger
	{
		public:
			virtual ~ILogger() { }

			virtual std::string GetName() const = 0;
			virtual std::string GetDesc() const = 0;

			virtual void Rotate() { };
			virtual void Log(const LogType Type, const std::string &str) = 0;
	};
};
