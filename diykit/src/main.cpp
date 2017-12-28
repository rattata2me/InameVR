
#include "EasyProgram.h"

int main(){
	
	InameProgramConfig* config = new InameProgramConfig();
	EasyProgram* ep = new EasyProgram(config);
	
	ep->start();
	
	delete config;
	delete ep;
	
	return 0;
}