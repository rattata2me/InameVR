
#include "EasyProgram.h"

EasyProgram::EasyProgram(InameProgramConfig* config): InameProgram(config)
{

}


cv::Mat cameraFrame;
cv::Mat hsv;
cv::Vec3b colour = cv::Vec3b(128,128,128);
void EasyProgram::tick()
{
	cameraFrame;
	stream.read(cameraFrame); 
	cv::flip(cameraFrame, cameraFrame,-1);
	cv::Mat mask;
	cv::Mat threshold;
	cv::threshold(cameraFrame, threshold, 50, 255, cv::THRESH_BINARY);
	//cv::bitwise_and(cameraFrame, threshold, cameraFrame);
	cv::cvtColor(cameraFrame, hsv, cv::COLOR_BGR2HSV);
	cv::Scalar up;
	up.val[0] = colour.val[0] - 20;
	up.val[1] = colour.val[1] - 30;
	up.val[2] =  colour.val[2] - 20;
	cv::Scalar down;
	down.val[0] = colour.val[0] + 20;
	down.val[1] = colour.val[1] + 80;
	down.val[2] = colour.val[2] + 80;
	cv::blur(hsv, hsv, cv::Size(4,4));
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
	//cv::minEnclosingCircle(mask, center, radius);
	cv::imshow("The window", mask);
	cv::imshow("The window 2", cameraFrame);
	char key = (char)cv::waitKey(1);
	
}

void EasyProgram::CallBackFunc(int event, int x, int y, int flags, void* sajaja)
{
       if(event == CV_EVENT_LBUTTONDOWN){
	       colour = hsv.at<cv::Vec3b>(cv::Point(x, y));
	       LOG(WARNING, "[ "+std::to_string((int)colour.val[0])+ ", "+std::to_string((int)colour.val[1])+ ", "+std::to_string((int)colour.val[0])+ " ]");
	}
}

void EasyProgram::onStart()
{
	stream.open(0);
	if (!stream.isOpened()) {
		LOG(ERROR, "Can not open the camera, is it connected correctly?");
	}
	cv::namedWindow("The window", cv::WINDOW_KEEPRATIO);
	cv::namedWindow("The window 2", cv::WINDOW_KEEPRATIO);
	cv::setMouseCallback("The window 2", EasyProgram::CallBackFunc, this);
}



void EasyProgram::onStop()
{

}
