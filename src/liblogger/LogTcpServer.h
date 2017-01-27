
namespace liblogger
{
	class LogTcpServer : public ILogger
	{
		public:
			LogTcpServer(int port);
			virtual ~LogTcpServer();
		
			void GetName(std::string *str);
			void GetDesc(std::string *str);
			void Log(const LogType Type, const std::string &str);
			void Rotate();

		private:
			void Lock();
			void Unlock();
		
			static void *Run(void *);

		private:
			pthread_t m_thread;
			pthread_mutex_t m_mutex;
			std::list<int> m_list;  //List of connected clients
			int m_port;
			int m_acceptfd;		//Socket we listen on
			int m_ctlfd[2];		//Event fd to exit again
			bool m_running;
	};
};

