
#include <stdio.h>

#include "liblogger.h"

namespace liblogger
{

LogFunction::LogFunction(std::function<void(const LogType, const std::string &)> func) :
	m_function(func)
{

}

std::string LogFunction::GetName() const {
	return "Function";
}

std::string LogFunction::GetDesc() const {
	return "Logs to a function / callback";
}

void LogFunction::Log(const LogType Type, const std::string &str) {
	m_function(Type, str);
}

};

