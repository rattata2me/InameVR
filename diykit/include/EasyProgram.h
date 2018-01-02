#ifndef DIYKIT_SRC_EASY_PROGRAM_H_
#define DIYKIT_SRC_EASY_PROGRAM_H_

#include "InameProgram.h"

#include "EasyService.h"

class EasyProgram : public InameProgram{
	
public:
	
	EasyProgram(InameProgramConfig* config);
	void onStart();
	void tick();
	void onStop();
	static void CallBackFunc(int event, int x, int y, int flags, void* jajwda);
	
private:
	EasyService* service;
	
}; 


#endif