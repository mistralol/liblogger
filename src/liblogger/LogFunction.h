
namespace liblogger
{
	class LogFunction : public ILogger
	{
		public:
			LogFunction(std::function<void(const LogType, const std::string &)>);
			virtual ~LogFunction() { };

			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);

		private:
			std::function<void(const LogType, const std::string &)> m_function;
	};
};

