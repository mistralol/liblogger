

namespace liblogger
{
	class LogManagerScopedLock
	{
		public:
			LogManagerScopedLock() {
				LogManager::Lock();
				m_locked = true;
			}
			~LogManagerScopedLock() {
				if (m_locked == true) {
					LogManager::Unlock();
				}
			}

			void Unlock() {
				m_locked = false;
				LogManager::Unlock();
			}
		private:
			bool m_locked;
	};
};
