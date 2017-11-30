
#include "liblogger.h"

namespace liblogger
{

LogMQ::LogMQ(const std::string &qname) :
	m_QName(qname)
{
	m_id = mq_open(qname.c_str(), O_WRONLY,  S_IRUSR | S_IWUSR, NULL);
	if (m_id < 0) {
		std::stringstream ss;
		ss << "failed to open queue '" << qname << "'";
		throw(LogException(ss.str()));
	}
}

LogMQ::~LogMQ() {
	if (mq_close(m_id) < 0)
		abort();
}

std::string LogMQ::GetName() const {
	return "LogMQ";
}

std::string LogMQ::GetDesc() const {
	return "Logs to a POSIX Message Queue";
}

void LogMQ::Log(const LogType Type, const std::string &str) {
	char *buf = 0;
	int len = asprintf(&buf, "%d:%s", Type, str.c_str());
	if (!buf) {
		throw(LogException("LogMQ::Log Malloc Failed"));
	}

	if (mq_send(m_id, buf, len, 0) < 0) {
		std::stringstream ss;
		ss << "LogMQ::Log failed to write to queue: " << m_QName << "' error: " << strerror(errno);
		free(buf);
		throw(LogException(ss.str()));
	}

	free(buf);
}

};

