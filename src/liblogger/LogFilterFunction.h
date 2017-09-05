


namespace liblogger
{
	class LogFilterFunction : public ILogFilter
	{
		public:
			LogFilterFunction(std::function<bool (const LogType Type, const std::string &str)> );
			~LogFilterFunction();

			bool Filter(const LogType Type, const std::string &str);
			
		private:
			std::function<bool (const LogType Type, const std::string &str)> m_function;
	};
};


