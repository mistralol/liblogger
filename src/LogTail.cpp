#include <stdio.h>
#include <sstream>

#include "liblogger.h"

namespace liblogger
{

LogTail::LogTail(size_t length)
{
	m_length = length;
}

void LogTail::GetName(std::string *str)
{
	*str = "Tail";
}

void LogTail::GetDesc(std::string *str)
{
	*str = "Keeps Last 'n' Messages in memory";
}

void LogTail::Log(const LogType Type, const std::string &str)
{
	if (m_data.size() >= m_length)
		m_data.pop_front();
	m_data.push_back(str);
}

std::string LogTail::GetData()
{
	std::list<std::string>::iterator it = m_data.begin();
	std::stringstream ss;
	while(it != m_data.end())
	{
		ss << *it << '\n';
		it++;
	}
	return ss.str();
}

};

