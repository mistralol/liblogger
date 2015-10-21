

namespace liblogger
{
	class LogFilterDup
	{
		public:
			LogFilterDup();
			virtual ~LogFilterDup();

			virtual bool Filter(const LogType Type, const std::string &str);
			
			uint64_t GetDropped();
		private:
			bool m_busy;
			std::string m_last;
			LogType m_lasttype;
			int m_matched;
			uint64_t m_dropped;
			
	};
};


