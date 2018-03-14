

namespace liblogger
{
	class LogFilterDup : public ILogFilter
	{
		public:
			LogFilterDup();
			virtual ~LogFilterDup();

			virtual bool Filter(const LogType Type, const std::string &str);

		private:
			bool m_busy;
			std::string m_last;
			LogType m_lasttype;
			int m_matched;
	};
};


