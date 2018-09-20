#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/types_c.h>
#include <thread>
#include <windows.h>
#include "FaceArmControl.h"

class FaceArmInput
{
public:
	FaceArmInput();
	void getBuffer(unsigned char *buffer);
	void showCameraVedio();
	void getBufferSize(int *size);
	void setRectangle(FaceArmControlRectangle rectangle);
	std::thread *mInputThread;
private:
	void InputThread();
	bool isShow;
	cv::Mat frame;
	FaceArmControlRectangle mRectangle;
	cv::VideoCapture *mCap;
};
