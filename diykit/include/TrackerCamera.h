#ifndef DIYKIT_SRC_TRACKER_CAMERA_H_
#define DIYKIT_SRC_TRACKER_CAMERA_H_

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <sys/socket.h>
#define PORT 2035
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "log.h"

#include <iostream>

class TrackerCamera{
	
public:
	TrackerCamera(int device_id, bool flip, std::vector<int> colors);
	void doTrackingStuff();
	
private:
	cv::VideoCapture capturedevice;
	bool flip;
	std::vector<int> color;
	
	struct sockaddr_in address;
	 int sock = 0, valread;
	struct sockaddr_in serv_addr;
};


#endif