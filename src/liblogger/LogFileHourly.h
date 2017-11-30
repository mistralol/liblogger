
namespace liblogger
{
	class LogFileHourly : public ILogger
	{
		public:
			LogFileHourly(const std::string &dir, const std::string &prefix, int maxage);
			virtual ~LogFileHourly();

			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);
			void Rotate();

		protected:
			void RemoveOld();

		private:
			std::string m_dir;
			std::string m_prefix;
			int m_maxage;
			std::string m_fname; //Current filename
			FILE *m_fp;
	};
};

