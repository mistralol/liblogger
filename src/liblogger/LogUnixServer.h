
namespace liblogger
{
	class LogUnixServer : public ILogger
	{
		public:
			LogUnixServer(const std::string &path);
			virtual ~LogUnixServer();

			std::string GetName() const;
			std::string GetDesc() const;
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
			std::string m_path;
			int m_acceptfd;		//Socket we listen on
			int m_ctlfd[2];		//Event fd to exit again
			bool m_running;
	};
};

