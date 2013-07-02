

class LogCallBack : public ILogger
{
	public:
		LogCallBack( void (*CallBack) (LogType Type, const std::string str));
		virtual ~LogCallBack() { };
		
		void GetName(std::string *str);
		void GetDesc(std::string *str);
		void Log(LogType Type, const std::string str);

	private:
		void (*m_CallBack) (LogType Type, const std::string str);


};


