


namespace liblogger
{
	class LogFilterCallBack : public ILogFilter
	{
		public:
			LogFilterCallBack(void *arg, bool (*CallBack) (void *arg, const LogType Type, const std::string &str));
			~LogFilterCallBack();

			bool Filter(const LogType Type, const std::string &str);

		private:
			bool (*m_CallBack) (void *arg, const LogType Type, const std::string &str);
			void *m_arg;
	};
};


