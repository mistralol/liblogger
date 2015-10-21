

namespace liblogger
{
	class LogFilterType
	{
		public:
			LogFilterType(LogType type);
			virtual ~LogFilterType();

			virtual bool Filter(const LogType Type, const std::string &str);
		private:
			LogType m_type;
			
	};
};

