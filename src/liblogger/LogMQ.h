
namespace liblogger
{
	class LogMQ : public ILogger
	{
		public:
			LogMQ(const std::string &qname = "/liblogger");
			virtual ~LogMQ();

			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);

		private:
			std::string m_QName;
			mqd_t m_id;
	};
};


