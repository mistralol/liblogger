
namespace liblogger
{
	class LogPipe : public ILogger
	{
		public:
			LogPipe(const std::string &command);
			virtual ~LogPipe();

			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);
		private:
			std::string m_command;
			FILE *m_fp;
	};
};

