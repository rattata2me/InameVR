
#include "EasyProgram.h"

EasyProgram::EasyProgram(InameProgramConfig* config): InameProgram(config)
{
	service = new EasyService(this);
}

void EasyProgram::tick()
{
	
	service->update();
	
}

void EasyProgram::onStart()
{
	service->start();
}

void EasyProgram::onStop()
{

}
