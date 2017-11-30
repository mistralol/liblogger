
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>

#include "liblogger.h"

namespace liblogger {

std::list<std::shared_ptr<ILogger> > LogManager::m_loggers;
std::list<std::shared_ptr<ILogFilter> > LogManager::m_filters;
LogMutex LogManager::m_mutex = LogMutex();
bool LogManager::m_catcherrors = false;
uint64_t LogManager::m_TotalMessages = 0;
uint64_t LogManager::m_TotalDroppedMessages = 0;
uint64_t LogManager::m_TotalErrors = 0;
uint64_t LogManager::m_TotalFiltered = 0;
LogType LogManager::m_Type = LOGGER_DEBUG;

void LogManager::Send(const LogType Type, const std::string &str)
{
	LogManagerScopedLock lock = LogManagerScopedLock();

	try
	{
		m_TotalMessages++;
		if (Type < m_Type)
		{
			m_TotalDroppedMessages++;
			return;
		}

		//Filter any messages
		for(auto &it : m_filters) {
			bool filter = it->Filter(Type, str);
			if (filter) {
				m_TotalFiltered++;
				return;
			}
		}

		//Send to all loggers
		for(auto &it : m_loggers) {
			it->Log(Type, str);
		}
	}
	catch(LogException &ex)
	{
		m_TotalErrors++;
		if (m_catcherrors == false)
		{
			throw(ex);
		}
	}
}

void LogManager::Rotate()
{
	LogManagerScopedLock lock = LogManagerScopedLock();
	for(auto &it : m_loggers) {
		it->Rotate();
	}
}

void LogManager::Add(std::shared_ptr<ILogger> Log)
{
	LogManagerScopedLock lock = LogManagerScopedLock();
	m_loggers.push_back(Log);
	lock.Unlock();
#ifdef DEBUG
	std::string str = Log->GetName();
	Logger(LOGGER_DEBUG, "Added Logger: %s", str.c_str());
#endif
}

void LogManager::Remove(std::shared_ptr<ILogger> Log)
{
	LogManagerScopedLock lock = LogManagerScopedLock();
	size_t size = m_loggers.size();
	m_loggers.remove(Log);
	if (size == m_loggers.size())
		throw(LogException("LogManager::Remove cannot find logging module"));
#ifdef DEBUG
	std::string str = Log->GetName();
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
	LogManagerScopedLock lock = LogManagerScopedLock();
	m_loggers.clear();
}

void LogManager::FilterAdd(ILogFilter *filter)
{
	LogManagerScopedLock lock = LogManagerScopedLock();
	std::shared_ptr<ILogFilter> ptr(filter);
	FilterAdd(ptr);
}

void LogManager::FilterAdd(std::shared_ptr<ILogFilter> filter)
{
	LogManagerScopedLock lock = LogManagerScopedLock();
	m_filters.push_back(filter);
}

void LogManager::FilterRemove(std::shared_ptr<ILogFilter> filter)
{
	LogManagerScopedLock lock = LogManagerScopedLock();
	size_t size = m_filters.size();
	m_filters.remove(filter);
	if (size == m_filters.size())
		throw(LogException("LogManager::FilterRemove cannot find filter module"));
}

void LogManager::FilterRemoveAll()
{
	LogManagerScopedLock lock = LogManagerScopedLock();
	m_filters.clear();
}

std::string LogManager::GetVersion()
{
	return PACKAGE_VERSION;
}

void LogManager::Lock()
{
	m_mutex.Lock();
}

void LogManager::Unlock()
{
	m_mutex.Unlock();
}

void LogManager::SetLevel(LogType Type)
{
	LogManagerScopedLock lock = LogManagerScopedLock();
	m_Type = Type;
}

LogType LogManager::GetLevel()
{
	return m_Type;
}

void LogManager::PrintAll()
{
	LogManagerScopedLock lock = LogManagerScopedLock();
	for(const auto &it : m_loggers) {
		std::string Name = it->GetName();
		std::string Desc = it->GetDesc();
		LogInfo("LogName: '%s' Desc: '%s'", Name.c_str(), Desc.c_str());
	}
}

};
