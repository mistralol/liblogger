


namespace liblogger
{
	class LogFilterCallBack
	{
		public:
			LogFilterCallBack(bool (*CallBack) (const LogType Type, const std::string &str));
			virtual ~LogFilterCallBack();

			virtual bool Filter(const LogType Type, const std::string &str);
			
		private:
			bool (*m_CallBack) (const LogType Type, const std::string &str);
	};
};


