

namespace liblogger
{
	class LogMutex
	{
		public:
			LogMutex() {
				pthread_mutexattr_t attr;
				if (pthread_mutexattr_init(&attr) != 0)
					abort();

				if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0)
					abort();

				if (pthread_mutex_init(&m_mutex, &attr) != 0)
					abort();

				if (pthread_mutexattr_destroy(&attr) != 0)
					abort();
			}

			~LogMutex() { 
				if (pthread_mutex_destroy(&m_mutex) != 0)
					abort();
			}

			void Lock() {
				if (pthread_mutex_lock(&m_mutex) < 0)
					throw(LogException("pthread_mutex_lock failed"));
			}

			void Unlock() {
				if (pthread_mutex_unlock(&m_mutex) < 0)
					throw(LogException("pthread_mutex_unlock failed"));
			}
		private:
			pthread_mutex_t m_mutex;
	};
};


