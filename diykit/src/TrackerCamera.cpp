#include "TrackerCamera.h"

TrackerCamera::TrackerCamera(int device_id, bool flip, std::vector<int> color)
{
	capturedevice.open(device_id);
	this->flip = flip;
	this->color = color;
	if (!capturedevice.isOpened()) {
		LOG(ERROR, "Can not open the camera, is it connected correctly?");
		exit(0); //TODO Handle exceptions.
	}
	cv::namedWindow("ViewTestWindow", cv::WINDOW_KEEPRATIO);
	
	
	
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
    }
}

void TrackerCamera::doTrackingStuff()
{
	//Capture image data from camera
	cv::Mat cameraFrame;
	capturedevice.read(cameraFrame);
	
	//my camera is crazy lel
	if(flip) cv::flip(cameraFrame, cameraFrame,-1);
	
	cv::Mat mask;
	cv::Mat threshold;
	cv::Mat hsv;
	
	//cv::threshold(cameraFrame, threshold, 50, 255, cv::THRESH_BINARY);
	
	cv::cvtColor(cameraFrame, hsv, cv::COLOR_BGR2HSV);
	
	cv::Scalar up;
	up.val[0] = color.at(0);
	up.val[1] = color.at(1);
	up.val[2] = color.at(2);
	cv::Scalar down;
	down.val[0] = color.at(3);
	down.val[1] = color.at(4);
	down.val[2] = color.at(5);
	//cv::blur(hsv, hsv, cv::Size(4,4));
	cv::inRange(hsv, up, down, mask);
	cv::erode(mask, mask, 3);
	cv::dilate(mask, mask, 3);
	
	
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::Point2f fcenter = cv::Point2f(0,0);
	float fradius = 0;
	cv::findContours( mask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
	for( int i = 0; i < contours.size(); i++ )
	{
		cv::Point2f center;
		float radius = 0;
		cv::minEnclosingCircle( contours[i], center, radius );
		if(radius > fradius){
			fradius = radius;
			fcenter = center;
		}
	}
	cv::line(cameraFrame, fcenter, fcenter, cv::Scalar(0,0,255), 10, cv::LINE_AA);
	cv::circle(cameraFrame, fcenter, fradius, cv::Scalar(0,0,255), 3, cv::LINE_AA);
	fradius *= 0.6f;
	fcenter = (fcenter-cv::Point2f(hsv.size().width, hsv.size().height)/2)/fradius;
	
	//SOCKET
	std::string e = std::to_string(hsv.size().width/fradius) + "," + std::to_string(fcenter.x) + "," + std::to_string(-fcenter.y);
	std::cout << e << std::endl;
	const char *hello = e.c_str();
	char buffer[1024] = {0};
    
	send(sock , hello , strlen(hello) , 0 );
	
	
	
	
	
	//Only for debug
	cv::imshow("ViewTestWindow", cameraFrame);
	cv::waitKey(1);
}
