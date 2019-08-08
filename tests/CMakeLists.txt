

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark logger)

add_executable(callback callback.cpp)
target_link_libraries(callback logger)

add_executable(file file.cpp)
target_link_libraries(file logger)

add_executable(filedaily filedaily.cpp)
target_link_libraries(filedaily logger)

add_executable(filehourly filehourly.cpp)
target_link_libraries(filehourly logger)
add_test(filehourly "./filehourly")

add_executable(function function.cpp)
target_link_libraries(function logger)
add_test(function "./function")

add_executable(logmqtest logmq.cpp)
target_link_libraries(logmqtest logger)
#add_test(logmq "./logmqtest")

add_executable(logonce logonce.cpp)
target_link_libraries(logonce logger)
add_test(logonce "./logonce")

add_executable(logperiod logperiod.cpp)
target_link_libraries(logperiod logger)
add_test(logperiod "./logperiod")

add_executable(pipe pipe.cpp)
target_link_libraries(pipe logger)
add_test(pipe "./pipe")

add_executable(proxylogger proxylogger.cpp)
target_link_libraries(proxylogger logger)
add_test(proxylogger "./proxylogger")

add_executable(remove remove.cpp)
target_link_libraries(remove logger)
add_test(remove "./remove")

add_executable(stderr stderr.cpp)
target_link_libraries(stderr logger)
add_test(stderr "./stderr")

add_executable(stdoutcolor stdoutcolor.cpp)
target_link_libraries(stdoutcolor logger)
add_test(stdoutcolor "./stdoutcolor")

add_executable(stdout stdout.cpp)
target_link_libraries(stdout logger)
add_test(stdout "./stdout")

add_executable(streamlogger streamlogger.cpp)
target_link_libraries(streamlogger logger)
add_test(streamlogger "./streamlogger")

add_executable(syslog syslog.cpp)
target_link_libraries(syslog logger)
#add_test(syslog "./syslog")

add_executable(tail tail.cpp)
target_link_libraries(tail logger)
add_test(tail "./tail")

add_executable(tcpserver tcpserver.cpp)
target_link_libraries(tcpserver logger)
add_test(tcpserver "./tcpserver")

add_executable(testfilter testfilter.cpp)
target_link_libraries(testfilter logger)
add_test(testfilter "./testfilter")

add_executable(unixserver unixserver.cpp)
target_link_libraries(unixserver logger)
add_test(unixserver "./unixserver")
