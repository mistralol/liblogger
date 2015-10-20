

namespace liblogger
{
	class LogManagerScopedLock
	{
		public:
			LogManagerScopedLock();
			~LogManagerScopedLock();

			void Unlock();
		private:
			bool m_locked;
	};
};



