

#include <liblogger.h>

using namespace liblogger;


int main(int argc, char **argv)
{
	LogManager::Add(new LogStdout());

    LogInfo("Should be 2 messages Test and Test2");

    for(int i =0;i<10;i++) {
        LogOnce(LOGGER_INFO, "Test %d", i++);
    }

    for(int i =0;i<10;i++) {
        LogOnce(LOGGER_INFO, "Test2 %d", i++);
    }

	LogManager::RemoveAll();
	return 0;
}

