
#include <liblogger.h>

using namespace liblogger;

class MyClass : public ProxyLogger {
    public:
        MyClass() :
            ProxyLogger("TESTPROXY")
        {

        }

        void Test() {
            LogDebug("Debug Logging #1");
            LogDebug("Debug Logging #%d", 2);

            LogInfo("Info Logging #1");
            LogInfo("Info Logging #%d", 2);

            LogNotice("Notice Logging #1");
            LogNotice("%s Logging #2", "Notice");

            LogWarning("Warning!!!!!!");
            LogWarning("Warning!!!!!! #%d", 2);

            LogError("This is an Error");
            LogError("This is an Error %d", 2);

            LogError("Something Critical happened");
            LogError("Something Critical happened %s", "Really BAD!");

            LogAlert("Alert Alert");
            LogAlert("Alert Alert %s", "Alert");

            LogCritical("TestLog Critical!");

            LogEmergency("TestLog Emergency!");
        }
};

int main(int argc, char ** argv)
{
	LogManager::Add(new LogStdout());

    MyClass C;
    C.Test();

	LogManager::RemoveAll();
	return 0;
}

