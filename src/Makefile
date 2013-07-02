
include ../Makefile.Rules

SRCS= 	Logger.cpp	\
		LogStdout.cpp \
		LogStderr.cpp \
		LogSyslog.cpp \
		LogCallBack.cpp \
		LogManager.cpp

OBJS=$(SRCS:%.cpp=%.o)

all: $(OBJS) .depend

.cpp.o:
	$(CPP) $(CPPFLAGS) $(INCLUDE) -c $< -o $@

.depend: $(SRCS)
	$(MKDEP) $(INCLUDE) $(SRCS) > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif

clean:
	$(RM) $(OBJS) .depend

	
