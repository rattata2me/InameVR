#ifndef DIYKIT_SRC_EASY_SERVICE_H_
#define DIYKIT_SRC_EASY_SERVICE_H_

#include "log.h"

#include "InameProgram.h"
#include "TrackerCamera.h"

class EasyService{
	
public:
	EasyService(InameProgram* program);
	
	virtual void start();
	virtual void update();
	
	void addCamera(TrackerCamera camera);
	
private:
	std::vector<TrackerCamera> cameras;
	InameProgram* program;
	
};

#endif