#ifndef DIYKIT_SRC_EASY_PROGRAM_H_
#define DIYKIT_SRC_EASY_PROGRAM_H_

#include "InameProgram.h"

class EasyProgram : public InameProgram{
	
public:
	EasyProgram(InameProgramConfig* config);
	void onStart();
	void tick();
	void onStop();
}; 

#endif