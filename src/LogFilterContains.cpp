
#include <liblogger.h>

namespace liblogger
{

LogFilterContains::LogFilterContains(const std::string &str, bool matchcase) :
	m_match(str),
	m_case(matchcase)
{

}

LogFilterContains::~LogFilterContains()
{

}

bool LogFilterContains::Filter(const LogType Type, const std::string &str)
{
	if (m_case == false)
	{
		if (strcasecmp(m_match.c_str(), str.c_str()) == 0)
		{
			return true;
		}
	}
	else
	{
		if (str.find(m_match) != std::string::npos)
		{
			return true;
		}
	}

	return false;
}

};

