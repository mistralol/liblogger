

#include <liblogger.h>

using namespace liblogger;

#include "examples.h"

int main(int argc, char ** argv)
{
	LogManager::Add(new LogTcpServer(54321));

	sleep(2);

	examples();

	LogManager::RemoveAll();
	return 0;
}

