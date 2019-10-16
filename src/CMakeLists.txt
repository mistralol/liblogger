
set(LOGGER_SOURCES
    LogCallBack.cpp
    LogException.cpp
    LogFile.cpp
    LogFileDaily.cpp
    LogFileHourly.cpp
    LogFilterCallBack.cpp
    LogFilterContains.cpp
    LogFilterDup.cpp
    LogFilterFunction.cpp
    LogFilterRegex.cpp
    LogFilterType.cpp
    LogFunction.cpp
    Logger.cpp
    LogManager.cpp
    LogMQ.cpp
    LogPipe.cpp
    LogStderr.cpp
    LogStdoutColor.cpp
    LogStdout.cpp
    LogSyslog.cpp
    LogTail.cpp
    LogTailIdx.cpp
    LogTcpServer.cpp
    LogType.cpp
    LogUdp.cpp
    LogUnixServer.cpp
    ProxyLogger.cpp
    StreamLogger.cpp
    Trace.cpp
    TraceLock.cpp
)

add_library(logger SHARED ${LOGGER_SOURCES})
add_library(loggerstatic STATIC ${LOGGER_SOURCES})
set_target_properties(loggerstatic PROPERTIES OUTPUT_NAME logger)

target_include_directories(logger PUBLIC .)
target_include_directories(loggerstatic PUBLIC .)
target_compile_options(logger PRIVATE -fPIC)
target_compile_options(loggerstatic PRIVATE -fPIC)
target_link_libraries(logger PRIVATE -lpthread -lrt)
target_link_libraries(loggerstatic PUBLIC -lpthread -lrt)

install(TARGETS logger loggerstatic
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES liblogger.h
    DESTINATION include
)

install(DIRECTORY liblogger
    DESTINATION include
)

