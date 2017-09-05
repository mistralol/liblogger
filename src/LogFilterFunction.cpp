
#include <liblogger.h>

namespace liblogger
{

LogFilterFunction::LogFilterFunction(std::function<bool (const LogType Type, const std::string &str)> func) :
	m_function(func)
{

}

LogFilterFunction::~LogFilterFunction()
{

}

bool LogFilterFunction::Filter(const LogType Type, const std::string &str)
{
	return m_function(Type, str);
}

};

