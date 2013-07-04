
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>

#include "liblogger.h"

namespace liblogger {

std::list<ILogger *> LogManager::m_loggers;
pthread_mutex_t LogManager::m_mutex;
bool LogManager::m_locked = false;
bool LogManager::m_threadprefix = true;
bool LogManager::m_processprefix = true;

void LogManager::Init()
{
	pthread_mutexattr_t attr;
	
	if (pthread_mutexattr_init(&attr) < 0)
		abort();
		
	if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) < 0)
		abort();
		
	if (pthread_mutex_init(&m_mutex, &attr) < 0)
		abort();

}

void LogManager::Add(ILogger *Log)
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

void LogManager::Send(const LogType Type, const std::string &str)
{
	std::stringstream ss;

	Lock();
	if (m_processprefix)
		ss << "[" << getpid() << "] ";

	if (m_threadprefix)
		ss << "[" << (int) pthread_self() << "] ";
	
	for( std::list<ILogger *>::iterator i = m_loggers.begin(); i != m_loggers.end(); i++)
		(*i)->Log(Type, ss.str());
	Unlock();
}

void LogManager::Rotate()
{
	Lock();
	for( std::list<ILogger *>::iterator i = m_loggers.begin(); i != m_loggers.end(); i++)
		(*i)->Rotate();
	Unlock();
}

void LogManager::Remove(ILogger *Log)
{
	Lock();
	m_loggers.remove(Log);
	Unlock();
#ifdef DEBUG
	std::string str;
	Log->GetName(&str);
	Logger(LOGGER_DEBUG, "Removed Logger: %s", str.c_str());
#endif
}

void LogManager::RemoveAll(bool destroy)
{
	Lock();
	while(m_loggers.empty() == false)
	{
		ILogger *p = m_loggers.front();
		m_loggers.remove(p);
		if (destroy)
			delete p;
	}
	Unlock();
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

bool LogManager::GetThreadPrefixEnabled()
{
	return m_threadprefix;
}

void LogManager::SetThreadPrefixEnabled(bool bEnabled)
{
	m_threadprefix = bEnabled;
}
		
bool LogManager::GetProcessPrefixEnabled()
{
	return m_processprefix;
}

void LogManager::SetProcessPrefixEnabled(bool bEnabled)
{
	m_processprefix = bEnabled;
}

};
