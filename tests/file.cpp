

#include <liblogger.h>

using namespace liblogger;

#include "examples.h"

int main(int argc, char ** argv)
{
	LogManager::Add(new LogFile("/proc/self/fd/1"));

	examples();

	LogManager::RemoveAll();
	return 0;
}

