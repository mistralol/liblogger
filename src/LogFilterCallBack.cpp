
#include <liblogger.h>

namespace liblogger
{

LogFilterCallBack::LogFilterCallBack(void *arg, bool (*CallBack) (void *arg, const LogType Type, const std::string &str)) :
	m_CallBack(CallBack),
	m_arg(arg)
{

}

LogFilterCallBack::~LogFilterCallBack()
{

}

bool LogFilterCallBack::Filter(const LogType Type, const std::string &str)
{
	return m_CallBack(m_arg, Type, str);
}

};

