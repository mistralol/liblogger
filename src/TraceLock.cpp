
#include <liblogger.h>

namespace liblogger
{


TraceLock::TraceLock(Trace *p) {
    p->Lock();
    m_trace = p;
    m_locked = true;
}

TraceLock::~TraceLock() {
    if (m_locked) {
        m_trace->Unlock();
    }
}

void TraceLock::Unlock() {
    if (m_locked == false)
        abort();
    m_trace->Unlock();
}

};
