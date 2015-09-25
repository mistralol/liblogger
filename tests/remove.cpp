

#include <liblogger.h>

using namespace liblogger;

#include "examples.h"

int main(int argc, char ** argv)
{
	std::shared_ptr<LogPipe> pipe(new LogPipe("cat"));
	LogManager::Add(pipe);

	examples();

	LogManager::Remove(pipe);
	return 0;
}

