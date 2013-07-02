
class ILogger {
	public:
		ILogger() { }
		virtual ~ILogger() { }

		virtual void GetName(std::string *str) { };
		virtual void GetDesc(std::string *str) { };
		virtual void Log(LogType Type, const std::string str) { };

};

