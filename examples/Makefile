
include ../Makefile.Rules

SRCS= syslog.cpp \
	stdout.cpp \
	stderr.cpp \
	pipe.cpp \
	callback.cpp \
	file.cpp \
	tail.cpp

OBJS=$(SRCS:%.cpp=%.exe)

LIBINC=
LIBDEP=../liblogger.a
LIBS=../liblogger.a -lpthread


all: $(OBJS)

%.exe: %.cpp .depend $(LIBDEP)
	$(CPP) $(CPPFLAGS) $(INCLUDE) $< -o $@ $(LIBINC) $(LIBS)

.depend: Makefile
	$(MKDEP) $(INCLUDE) $(SRCS) > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif

clean:
	$(RM) $(OBJS) .depend

