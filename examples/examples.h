

void examples()
{
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

	LogEmergency("Emergency!");
	LogEmergency("Emergency! %s", "Black Hole detected");

}

