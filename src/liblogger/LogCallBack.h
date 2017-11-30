
namespace liblogger
{
	class LogCallBack : public ILogger
	{
		public:
			LogCallBack(void *arg, void (*CallBack) (void *arg, const LogType Type, const std::string &str));
			virtual ~LogCallBack() { };

			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);

		private:
			void (*m_CallBack) (void *arg, const LogType Type, const std::string &str);
			void *m_arg;
	};
};


