
namespace liblogger
{
	class LogFunction : public ILogger
	{
		public:
			LogFunction(std::function<void(const LogType, const std::string &)>);
			virtual ~LogFunction() { };

			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);

		private:
			std::function<void(const LogType, const std::string &)> m_function;
	};
};


