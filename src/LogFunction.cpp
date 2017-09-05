
#include <stdio.h>

#include "liblogger.h"

namespace liblogger
{

LogFunction::LogFunction(std::function<void(const LogType, const std::string &)> func) :
	m_function(func)
{

}

void LogFunction::GetName(std::string *str)
{
	*str = "Function";
}

void LogFunction::GetDesc(std::string *str)
{
	*str = "Logs to a function / callback";
}

void LogFunction::Log(const LogType Type, const std::string &str)
{
	m_function(Type, str);
}

};

