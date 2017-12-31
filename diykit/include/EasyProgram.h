#ifndef DIYKIT_SRC_EASY_PROGRAM_H_
#define DIYKIT_SRC_EASY_PROGRAM_H_

#include "InameProgram.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class EasyProgram : public InameProgram{
	
	

public:
	EasyProgram(InameProgramConfig* config);
	void onStart();
	void tick();
	void onStop();
	cv::VideoCapture stream;
	static void CallBackFunc(int event, int x, int y, int flags, void* jajwda);

}; 


#endif