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
		for(unsigned int i = 0; i < camerasjson.size(); i++){
			json ji = camerasjson.at(i);
			json colorsjs = ji.at("colors");
			bool correctly_loaded = true;
			std::vector<int> colors;
			if(colorsjs.is_array()){
				for(int e = 0; e < colorsjs.size(); e++){
					json colorjs = colorsjs.at(e);
					if(colorjs.is_array()){
						for(int u = 0; u < colorjs.size(); u++){
							json colorval =  colorjs.at(u);
							if(colorval.is_number_integer()){
								int col =  colorval.get<int>();
								colors.push_back(col);
							}else correctly_loaded = false;
						}
					}else correctly_loaded = false;
				}
			}else correctly_loaded = false;
	
			TrackerCamera camera(0, true, colors);
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


