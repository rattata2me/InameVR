#ifndef DIYKIT_SRC_EASY_SERVICE_H_
#define DIYKIT_SRC_EASY_SERVICE_H_

#include "log.h"

#include "TrackerCamera.h"

class EasyService{
	
public:
	EasyService();
	
	virtual void start();
	virtual void update();
	
private:
	std::vector<TrackerCamera> cameras;
	
};

#endif