

namespace liblogger
{
	class LogTail : public ILogger
	{
		public:
			LogTail(size_t length);
			virtual ~LogTail() { };
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);

			std::string GetData();
			std::list<std::string> GetList();

		private:
			size_t m_length;
			std::list<std::string> m_data;
	};
};

