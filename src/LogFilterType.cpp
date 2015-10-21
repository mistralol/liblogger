#include <stdio.h>

#include "liblogger.h"

namespace liblogger
{

LogFilterType::LogFilterType(LogType type) :
	m_type(type)
{

}

LogFilterType::~LogFilterType()
{

}

bool LogFilterType::Filter(const LogType Type, const std::string &str)
{
	if (Type == m_type)
		return true;
	return false;
}

};

