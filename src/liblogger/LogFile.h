
namespace liblogger
{
	class LogFile : public ILogger
	{
		public:
			LogFile(const std::string fname);
			virtual ~LogFile();
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);
			void Rotate();
		private:
			std::string m_fname;
			FILE *m_fp;
	};
};

