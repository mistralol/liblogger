
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>

#include "liblogger.h"

namespace liblogger {

std::list<std::shared_ptr<ILogger> > LogManager::m_loggers;
pthread_mutex_t LogManager::m_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
bool LogManager::m_locked = false;
uint64_t LogManager::m_TotalMessages = 0;
LogType LogManager::m_Type = LOGGER_DEBUG;

void LogManager::Send(const LogType Type, const std::string &str)
{
	Lock();
	
	if (Type < m_Type)
	{
		Unlock();
		return;
	}
	
	m_TotalMessages++;	
	for( std::list<std::shared_ptr<ILogger> >::iterator i = m_loggers.begin(); i != m_loggers.end(); i++)
	{
		(*i)->Log(Type, str);
	}
	Unlock();
}

void LogManager::Rotate()
{
	Lock();
	for( std::list<std::shared_ptr<ILogger> >::iterator it = m_loggers.begin(); it != m_loggers.end(); it++)
		(*it)->Rotate();
	Unlock();
}

void LogManager::Add(std::shared_ptr<ILogger> Log)
{
	Lock();
	m_loggers.push_back(Log);
	Unlock();
#ifdef DEBUG
	std::string str;
	Log->GetName(&str);
	Logger(LOGGER_DEBUG, "Added Logger: %s", str.c_str());
#endif
}

void LogManager::Remove(std::shared_ptr<ILogger> Log)
{
	Lock();
	size_t size = m_loggers.size();
	m_loggers.remove(Log);
	if (size == m_loggers.size())
		abort();
	Unlock();
#ifdef DEBUG
	std::string str;
	Log->GetName(&str);
	Logger(LOGGER_DEBUG, "Removed Logger: %s", str.c_str());
#endif
}

void LogManager::Add(ILogger *Log)
{
	std::shared_ptr<ILogger> ptr(Log);
	Add(ptr);
}

void LogManager::RemoveAll()
{
	Lock();
	while(m_loggers.empty() == false)
	{
		std::shared_ptr<ILogger> p = m_loggers.front();
		m_loggers.remove(p);
	}
	Unlock();
}

std::string LogManager::GetVersion()
{
	return PACKAGE_VERSION;
}

void LogManager::Lock()
{
	if (pthread_mutex_lock(&m_mutex) < 0)
		abort();
	m_locked = true;
}

void LogManager::Unlock()
{
	m_locked = false;
	if (pthread_mutex_unlock(&m_mutex) < 0)
		abort();
}

void LogManager::SetLevel(LogType Type)
{
	Lock();
	m_Type = Type;
	Unlock();
}

LogType LogManager::GetLevel()
{
	return m_Type;
}

};
