#include "EasyService.h"

EasyService::EasyService(InameProgram* program)
{
	this->program = program;
}

void EasyService::start()
{
	
	//Start reading the configuration file
	
	//Read cameras configuration
	json cameras = program->getValueFromSettings("cameras");
	
	if(cameras != VALUE_NULL){
		
	}else{
		LOG(WARNING, "No cameras set up, please select one in the settings file.");
	}
	
}

void EasyService::update()
{

}

void EasyService::addCamera(TrackerCamera camera)
{
	cameras.push_back(camera);
}


