
#include <liblogger.h>

namespace liblogger
{

Trace::Trace(LogType type) {
    m_type = type;
    m_active = true;
}

Trace::~Trace() {
    if (m_active) {
        LogManagerScopedLock lock = LogManagerScopedLock();
        for(auto &it : m_lst) {
            Logger(m_type, it);
        }
    }
}

void Trace::Log(const char *fmt, ...) {
	char *tmp = 0;
	
	va_list ap;
	va_start(ap, fmt);
	int res = vasprintf(&tmp, fmt, ap);
	if (res < 0)
		abort();
    
	std::string str = tmp;
    TraceLock lock(this);
	m_lst.push_back(str);
    lock.Unlock();
	free(tmp);
	va_end(ap);
}

void Trace::Cancel() {
    m_active = false;
    m_lst.clear();
}

void Trace::Lock() {
    m_mutex.Lock();
}

void Trace::Unlock() {
    m_mutex.Unlock();
}

};