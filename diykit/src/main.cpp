
#include "EasyProgram.h"

int main(){
	
	InameProgramConfig* config = new InameProgramConfig();
	
	config->tickrate = 1000;
	
	EasyProgram* ep = new EasyProgram(config);
	
	ep->start();
	
	
	return 0;
}