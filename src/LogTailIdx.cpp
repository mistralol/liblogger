#include <stdio.h>
#include <sstream>

#include "liblogger.h"

namespace liblogger
{

LogTailIdx::LogTailIdx(size_t length)
{
	m_length = length;
	m_current = 0;
}

void LogTailIdx::GetName(std::string *str)
{
	*str = "TailIdx";
}

void LogTailIdx::GetDesc(std::string *str)
{
	*str = "Keeps Last 'n' Messages in memory";
}

void LogTailIdx::Log(const LogType Type, const std::string &str)
{
	m_data.insert(std::make_pair(m_current, str));
	m_current++;
	if (m_data.size() >= m_length)
	{
		m_data.erase(m_data.begin());
	}
}

std::list<std::string> LogTailIdx::GetList()
{
	LogManager::Lock();
	std::map<uint64_t, std::string>::iterator it = m_data.begin();
	std::list<std::string> lst;
	while(it != m_data.end())
	{
		lst.push_back(it->second);
	}
	LogManager::Unlock();
	return lst;
}

std::list<std::string> LogTailIdx::GetList(uint64_t *idx)
{
	return LogTailIdx::GetList(idx, 0);
}

std::list<std::string> LogTailIdx::GetList(uint64_t *idx, int maxitems)
{
	LogManager::Lock();
	std::list<std::string> lst;
	
	if (*idx > m_current)
	{
		*idx = m_current;
		LogManager::Unlock();
		return lst;
	}
		
	//skip idx to first item in case it has not been used in a while
	std::map<uint64_t, std::string>::iterator it = m_data.begin();
	if (*idx < it->first)
	{
		*idx = it->first;
	}
	
	int count = 0;
	for(uint64_t i=*idx;i<m_current;i++)
	{
		if (maxitems > 0 && count > maxitems)
		{
			*idx = i;
			LogManager::Unlock();
			return lst;
		}
		lst.push_back(m_data[i]);
		count++;
	}
	*idx = m_current;	
	LogManager::Unlock();
	return lst;
}

};

