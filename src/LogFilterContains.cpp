
#include <liblogger.h>

namespace liblogger
{

LogFilterContains::LogFilterContains(const std::string &str) :
	m_match(str),
	m_case(false)
{

}

LogFilterContains::~LogFilterContains()
{

}

bool LogFilterContains::Filter(const LogType Type, const std::string &str)
{
	if (str.find(m_match) != std::string::npos)
	{
		return true;
	}

	return false;
}

};

