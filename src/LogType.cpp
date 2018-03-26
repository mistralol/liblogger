

#include "liblogger.h"

static std::string Types[] {
	"DEBG",
	"INFO",
	"NOTI",
	"WARN",
	"ERRO",
	"CRIT",
	"ALER",
	"EMER"
};

namespace liblogger {

const std::string &LogTypeToStr(LogType Type) {
	return Types[Type];
}


};

