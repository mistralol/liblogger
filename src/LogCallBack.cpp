
#include <stdio.h>

#include "liblogger.h"

namespace liblogger
{

LogCallBack::LogCallBack(void *arg, void (*CallBack) (void *arg, const LogType Type, const std::string &str) ) :
	m_CallBack(CallBack),
	m_arg(arg)
{

}

std::string LogCallBack::GetName() const {
	return "CallBack";
}

std::string LogCallBack::GetDesc() const {
	return "Logs to a function callback";
}

void LogCallBack::Log(const LogType Type, const std::string &str) {
	m_CallBack(m_arg, Type, str);
}

};

