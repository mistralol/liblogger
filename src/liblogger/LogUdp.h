
namespace liblogger
{
	class LogUdp : public ILogger
	{
		public:
			LogUdp(const std::string addr, int port);
			virtual ~LogUdp();
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);
			void Rotate();
			
			void SetIgnoreErrors(bool value);

		private:
			std::string m_addr;
			int m_port;
			int m_fd;
			bool m_ignoreerrors;
	};
};

