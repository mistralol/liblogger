prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=@CMAKE_INSTALL_PREFIX@
libdir=@CMAKE_INSTALL_PREFIX@/lib
includedir=@CMAKE_INSTALL_PREFIX@/include

Name: liblogger
Description: Another C++ logging library
URL: http://github.com/mistralol/liblogger
Version: @VERSION@
Requires:
Libs: -L${libdir} -llogger
Cflags: -I${includedir}
