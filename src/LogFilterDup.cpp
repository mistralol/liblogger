#include <sstream>

#include "liblogger.h"

namespace liblogger
{

LogFilterDup::LogFilterDup() :
	m_busy(false),
	m_last(""),
	m_lasttype(LOGGER_DEBUG),
	m_matched(0)
{

}

LogFilterDup::~LogFilterDup()
{

}

bool LogFilterDup::Filter(const LogType Type, const std::string &str)
{
	if (m_busy)
		return false; //Being reentered
	m_busy = true;
	try
	{
		if (Type == m_lasttype && str == m_last)
		{
			m_matched++;
			m_busy = false;
			return true;
		}
	
		if (m_matched)
		{
			std::stringstream ss;
			ss << "Last message repeated " << m_matched << " times";
			LogManager::Send(m_lasttype, ss.str());
		}
		m_matched = 0;
		m_last = str;
		m_lasttype = Type;
		m_busy = false;
		return false;
	}
	catch(std::exception &ex)
	{
		m_busy = false;
		throw(ex);
	}
}

};

