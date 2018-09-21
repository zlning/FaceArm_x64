#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/types_c.h>
#include <thread>
#include <windows.h>
#include "FaceArmType.h"
class FaceArmInput
{
public:
	FaceArmInput();
	~FaceArmInput();
	void getBuffer(FaceArmControlSurfaceBuffer *surface);
	void showCameraVedio();
	int getBufferSize();
	void setRectangle(FaceArmControlRectangle rectangle);
	std::thread *mInputThread;
private:
	void InputThread();
	bool isShow;
	cv::Mat frame;
	FaceArmControlRectangle mRectangle;
	cv::VideoCapture *mCap;
};
