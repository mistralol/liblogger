
add_executable(logmq
    logmq.cpp
)

target_link_libraries(logmq
    logger
    -lrt
)
