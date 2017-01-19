


namespace liblogger
{
	class LogFilterContains : public ILogFilter
	{
		public:
			LogFilterContains(const std::string &str, bool matchcase = false);
			~LogFilterContains();

			virtual bool Filter(const LogType Type, const std::string &str);

		private:
			std::string m_match;
			bool m_case;
	};
};


