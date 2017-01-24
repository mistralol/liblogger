

#include <liblogger.h>

using namespace liblogger;

int main(int argc, char ** argv)
{
	LogManager::Add(new LogStdout());

	LOGGER << LOGGER_INFO << "Test StreamLogger" << std::endl;

	LogManager::RemoveAll();
	return 0;
}

