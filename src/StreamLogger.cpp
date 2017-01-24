#include <stdio.h>
#include <sstream>

#include "liblogger.h"

namespace liblogger
{

StreamLogger::StreamLogger() :
	m_type(LOGGER_INFO)
{

}

StreamLogger::~StreamLogger() {

}

//FIXME: This method of per thrad instance creation / destruction
//will leak a single instance onthe main thread at exit time
//I think we can live with that! unless you want to go fix pthreads?
static pthread_key_t key;
static void Cleanup(void *arg) {
	StreamLogger *p = (StreamLogger *) arg;
	if (p) {
		delete p;
	}
}

static void MakeKey() {
	if (pthread_key_create(&key, Cleanup) != 0)
		abort();
}

StreamLogger &GetStreamLogger()
{
	static pthread_once_t once = PTHREAD_ONCE_INIT;
	if (pthread_once(&once, MakeKey) != 0)
		abort();
	
	StreamLogger *p = (StreamLogger *) pthread_getspecific(key);
	if (!p) {
		p = new StreamLogger();
		pthread_setspecific(key, p);
	}
	return *p;
}

};

