
#include <liblogger.h>

namespace liblogger
{

LogFilterCallBack::LogFilterCallBack(bool (*CallBack) (const LogType Type, const std::string &str)) :
	m_CallBack(CallBack)
{

}

LogFilterCallBack::~LogFilterCallBack()
{

}

bool LogFilterCallBack::Filter(const LogType Type, const std::string &str)
{
	return m_CallBack(Type, str);
}

};

