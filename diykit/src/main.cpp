
#include "EasyProgram.h"

int main(){
	
	InameProgramConfig* config = new InameProgramConfig();
	
	config->tickrate = -1;
	
	EasyProgram* ep = new EasyProgram(config);
	
	ep->start();
	
	
	return 0;
}