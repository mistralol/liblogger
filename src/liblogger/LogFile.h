
namespace liblogger
{
	class LogFile : public ILogger
	{
		public:
			LogFile(const std::string &fname);
			virtual ~LogFile();

			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);
			void Rotate();
		private:
			std::string m_fname;
			FILE *m_fp;
	};
};

