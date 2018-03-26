
#include <liblogger.h>

namespace liblogger
{

LogFilterRegex::LogFilterRegex(const std::string &regex) :
	m_regex(regex),
	m_ex(regex)
{

}

LogFilterRegex::~LogFilterRegex()
{

}

bool LogFilterRegex::Filter(const LogType Type, const std::string &str)
{
	return std::regex_match(str, m_ex);
}

};

