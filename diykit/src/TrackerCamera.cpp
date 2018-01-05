#include "TrackerCamera.h"

TrackerCamera::TrackerCamera(int device_id, bool flip)
{
	capturedevice.open(device_id);
	this->flip = flip;
	if (!capturedevice.isOpened()) {
		LOG(ERROR, "Can not open the camera, is it connected correctly?");
		exit(0); //TODO Handle exceptions.
	}
	cv::namedWindow("ViewTestWindow", cv::WINDOW_KEEPRATIO);
}

void TrackerCamera::doTrackingStuff()
{
	//Capture image data from camera
	cv::Mat cameraFrame;
	capturedevice.read(cameraFrame);
	
	//my camera is crazy lel
	if(flip) cv::flip(cameraFrame, cameraFrame,-1);
	
	
	
	//Only for debug
	cv::imshow("ViewTestWindow", cameraFrame);
	cv::waitKey(1);
}
