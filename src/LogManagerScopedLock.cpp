
#include <liblogger.h>

namespace liblogger
{

LogManagerScopedLock::LogManagerScopedLock()
{
	LogManager::Lock();
	m_locked = true;
}

LogManagerScopedLock::~LogManagerScopedLock()
{
	if (m_locked == true)
		LogManager::Unlock();
}
	
void LogManagerScopedLock::Unlock()
{
	m_locked = false;
	LogManager::Unlock();
}

};

