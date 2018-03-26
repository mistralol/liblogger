


namespace liblogger
{
	class LogFilterRegex : public ILogFilter
	{
		public:
			LogFilterRegex(const std::string &regex);
			~LogFilterRegex();

			virtual bool Filter(const LogType Type, const std::string &str);

		private:
			std::string m_regex;
			std::regex m_ex;
	};
};


