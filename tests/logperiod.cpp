

#include <liblogger.h>

using namespace liblogger;


int main(int argc, char **argv)
{
	LogManager::Add(new LogStdout());

    LogInfo("Should be a message every second");

    for(int i =0;i<15;i++) {
        usleep(100000); //Sleep 100ms
        LogPeriod(1, LOGGER_INFO, "Test %d", i);
    }

	LogManager::RemoveAll();
	return 0;
}

