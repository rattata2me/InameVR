#ifndef INAME_SRC_LOG_H_
#define INAME_SRC_LOG_H_

#include <string>

#include "common.h"


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

enum PRIORITY_CODE{
	WARNING,
	ERROR,
	INFO
};



#ifdef DEBUG_MODE
	static bool LOG_DEBUG = true;
#else 
	static bool LOG_DEBUG = true;
#endif

void LOG(PRIORITY_CODE code, std::string message);

void LOG(PRIORITY_CODE code, std::string message, bool onlydebug);

#endif