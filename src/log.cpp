
#include "log.h"

void LOG(PRIORITY_CODE code, std::string message, bool onlydebug)
{
	if(LOG_DEBUG | (!onlydebug)){
	
		std::string prefix = "";
		bool colors = true;
		
#ifndef  __WINDOWS__
		colors = true;
#endif
		
		switch(code){
			
			case ERROR:
				prefix = "ERROR";
				if(colors) prefix = ANSI_COLOR_RED + prefix + ANSI_COLOR_RESET;
				break;
			case WARNING:
				prefix = "WARNING";
				if(colors) prefix = ANSI_COLOR_YELLOW + prefix + ANSI_COLOR_RESET;
				break;
			case INFO:
				prefix = "Info";
				break;
			default:
				prefix = "ERROR";
				break;
			
		}
		
		
		std::cout << prefix << ": " << message << "\n";
	}
}

void LOG(PRIORITY_CODE code, std::string message)
{
	LOG(code, message, true);
}