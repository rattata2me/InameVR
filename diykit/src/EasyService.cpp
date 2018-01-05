#include "EasyService.h"

EasyService::EasyService(InameProgram* program)
{
	this->program = program;
}

void EasyService::start()
{
	
	//Start reading the configuration file
	
	//Read cameras configuration
	json camerasjson = program->getValueFromSettings("cameras");
	
	if(!camerasjson.is_null() && camerasjson.is_array()){
		for(int i = 0; i < camerasjson.size(); i++){
			json ji = camerasjson.at(i);
			TrackerCamera camera(0, true);
			cameras.push_back(camera);
		}
	}else{
		LOG(WARNING, "No cameras set up, please select one in the settings file.");
	}
	
}

void EasyService::update()
{
	for(int i = 0; i < cameras.size(); i++){
		cameras.at(i).doTrackingStuff();
	}
}

void EasyService::addCamera(TrackerCamera camera)
{
	cameras.push_back(camera);
}


