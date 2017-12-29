
#include "InameProgram.h"

InameProgram::InameProgram(InameProgramConfig* config)
{
	//Here everything is set up
	tickrate = config->tickrate;
}

InameProgram::~InameProgram()
{
	running = false;
	components.clear();
	delete &components;
}

void InameProgram::start()
{
	LOG(INFO, "Running iname vr version " + std::to_string(INAME_MAJOR_VERSION) + "." + std::to_string(INAME_MINOR_VERSION) + "." + std::to_string(INAME_PATCH_VERSION));
	
	running = true;
	
	//Call the public method OnStart
	onStart();
	enterMainLoop();
	
}

void InameProgram::enterMainLoop()
{
	
	
	//Main loop.
	while(running){
		
		auto last_current = std::chrono::system_clock::now();
		
		//Now call tick
		tick();
		
		
		//The simpliest way to control tick rate.
		auto current = std::chrono::system_clock::now();
		auto delta = (current-last_current);
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(delta);
		long delta_time = millis.count();
		long time_to_sleep = (tickrate*1000) - delta_time;
		if (time_to_sleep < 0) time_to_sleep = 0;
		std::this_thread::sleep_for(std::chrono::microseconds(time_to_sleep));
		
	}
	
}

void InameProgram::stop()
{
	running = false;
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


