
#include "InameProgram.h"

InameProgram::InameProgram(InameProgramConfig* config)
{
	//Here everything is set up
	
}

InameProgram::~InameProgram()
{
	
	components.clear();
	delete &components;
}

void InameProgram::start()
{
	
	//Call the public method OnStart
	onStart();
}

void InameProgram::enterMainLoop()
{
	
}

void InameProgram::addComponent(InameComponent* component_p)
{
	unsigned int index = components.size();
	component_p->setId(index);
	
	components.insert(std::pair<int, InameComponent*>(index, component_p));
	
}


InameComponent* InameProgram::getComponent(int id)
{
	return (components.find(id)->second);
}


