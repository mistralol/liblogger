
#include <liblogger.h>

LogException::LogException(const std::string exception)
{
	m_message = exception;
}

LogException::~LogException()
{

}
		
const char *LogException::what() const throw()
{
	return m_message.c_str();
}

