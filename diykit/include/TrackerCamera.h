#ifndef DIYKIT_SRC_TRACKER_CAMERA_H_
#define DIYKIT_SRC_TRACKER_CAMERA_H_

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "log.h"

#include <iostream>

class TrackerCamera{
	
public:
	TrackerCamera(int device_id, bool flip);
	void doTrackingStuff();
	
private:
	cv::VideoCapture capturedevice;
	bool flip;
};


#endif