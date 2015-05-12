
namespace liblogger
{
	class LogPipe : public ILogger
	{
		public:
			LogPipe(const std::string command);
			virtual ~LogPipe();
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);
		private:
			std::string m_command;
			FILE *m_fp;
	};
};

