
namespace liblogger
{
	class LogUdp : public ILogger
	{
		public:
			LogUdp(const std::string &addr, uint16_t port);
			virtual ~LogUdp();

			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);
			void Rotate();

			void SetIgnoreErrors(bool value);

		private:
			std::string m_addr;
			uint16_t m_port;
			int m_fd;
			bool m_ignoreerrors;
	};
};

