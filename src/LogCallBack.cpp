
#include <stdio.h>

#include "liblogger.h"

namespace liblogger {

LogCallBack::LogCallBack( void (*CallBack) (LogType Type, const std::string str) ) {
	m_CallBack = CallBack;
}

void LogCallBack::GetName(std::string *str) {
	*str = "CallBack";
}

void LogCallBack::GetDesc(std::string *str) {
	*str = "Logs to a function callback";
}

void LogCallBack::Log(LogType Type, const std::string str) {
	m_CallBack(Type, str);
}

};

