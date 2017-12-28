
#include "EasyProgram.h"

EasyProgram::EasyProgram(InameProgramConfig* config): InameProgram(config)
{

}


void EasyProgram::onStart()
{
	std::cout << "Nice work, you got this thing working! \n";
}
