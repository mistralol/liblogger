
namespace liblogger
{
	class LogMQ : public ILogger
	{
		public:
			LogMQ(const std::string &qname = "/liblogger");
			virtual ~LogMQ();

			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);

		private:
			std::string m_QName;
			mqd_t m_id;
	};
};


