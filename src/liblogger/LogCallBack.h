
namespace liblogger
{
	class LogCallBack : public ILogger
	{
		public:
			LogCallBack( void (*CallBack) (const LogType Type, const std::string &str));
			virtual ~LogCallBack() { };
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);

		private:
			void (*m_CallBack) (const LogType Type, const std::string &str);
	};
};


