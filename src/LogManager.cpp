
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>

#include "liblogger.h"

namespace liblogger {

std::list<ILogger *> LogManager::m_loggers;
pthread_mutex_t LogManager::m_mutex;
bool LogManager::m_locked = false;
uint64_t LogManager::m_TotalMessages = 0;
std::string LogManager::m_DateFormat = "%F %T";
std::string LogManager::m_ProcessName = "";

bool LogManager::m_AddSeq = true;
bool LogManager::m_AddDate = true;
bool LogManager::m_AddProcessName = true;
bool LogManager::m_AddProcessID = true;
bool LogManager::m_AddThreadID = false;
bool LogManager::m_AddSeperator = true;

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
	Lock();
	m_TotalMessages++;	
	for( std::list<ILogger *>::iterator i = m_loggers.begin(); i != m_loggers.end(); i++)
	{
		std::stringstream ss;

		if (m_AddDate && (*i)->AddDate())
		{
			time_t current;
			struct tm timeinfo;
			char buf[128];
			time(&current);
			localtime_r(&current, &timeinfo);
			strftime(buf, sizeof(buf), m_DateFormat.c_str(), &timeinfo);
			ss << buf << " ";
		}

		if (m_AddSeq && (*i)->AddSeq())
			ss << "<" << m_TotalMessages << "> ";

		if (m_AddProcessName && (*i)->AddProcessName())
		{
			ss << m_ProcessName << " ";
		}

		if (m_AddProcessID && (*i)->AddProcessID())
		{
			ss << "[PID:" << getpid() << "] ";
		}

		if (m_AddThreadID && (*i)->AddThreadID())
		{
			ss << "[TID:" << pthread_self() << "] ";
		}

		if (m_AddSeperator && (*i)->AddSeperator())
		{
			ss << "- ";
		}

		ss << str;
		(*i)->Log(Type, ss.str());
	}
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

bool LogManager::GetAddSeq()
{
	return m_AddSeq;
}

void LogManager::SetAddSeq(bool bEnabled)
{
	m_AddSeq = bEnabled;
}

bool LogManager::GetAddDate()
{
	return m_AddDate;
}

void LogManager::SetAddDate(bool bEnabled)
{
	m_AddDate = bEnabled;
}

std::string LogManager::GetDateFormat()
{
	return m_DateFormat;
}

void LogManager::SetDateFormat(const std::string &str)
{
	m_DateFormat = str;
}

bool LogManager::GetAddProcessName()
{
	return m_AddProcessName;
}

void LogManager::SetAddProcessName(bool bEnabled)
{
	m_AddProcessName = bEnabled;
}

std::string LogManager::GetProcessName()
{
	return m_ProcessName;
}

void LogManager::SetProcessName(const std::string &str)
{
	m_ProcessName = str;
}

bool LogManager::GetAddProcessID()
{
	return m_AddProcessID;
}

void LogManager::SetAddProcessID(bool bEnabled)
{
	m_AddProcessID = bEnabled;
}

bool LogManager::GetAddThreadID()
{
	return m_AddThreadID;
}

void LogManager::SetAddThreadID(bool bEnabled)
{
	m_AddThreadID = bEnabled;
}

bool LogManager::GetAddSeperator()
{
	return m_AddSeperator;
}

void LogManager::SetAddSeperator(bool bEnabled)
{
	m_AddSeperator = bEnabled;
}

};
