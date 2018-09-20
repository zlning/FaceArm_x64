#include "FaceArmInput.h"
using namespace std;

FaceArmInput::FaceArmInput() {
	mCap = new cv::VideoCapture(0);
	isShow = false;
	mRectangle.isShow = false;
	mRectangle.left = 0;
	mRectangle.right = 0;
	mRectangle.bottom = 0;
	mRectangle.top = 0;
	if (!mCap->isOpened())
	{
		fprintf(stderr, "camera can not init\n");
		mCap = NULL;
		return;
	}
	//thread td(&FaceArmInput::InputThread,this);
	//td.join();
	mInputThread = new thread(&FaceArmInput::InputThread, this);
}
void FaceArmInput::getBufferSize(int *size) {
	if (mCap == NULL) {
		fprintf(stderr, "mCap is not init\n");
		return;
	}
	//*mCap >> frame;
	*size = frame.total();
}
void FaceArmInput::getBuffer(unsigned char *buffer) {
	if (mCap==NULL) {
		fprintf(stderr, "mCap is not init\n");
		return;
	}
	//*mCap >> frame;
	//frame.data
	memcpy(buffer, frame.data, frame.total());
}
void FaceArmInput::showCameraVedio() {
	/*using namespace cv;
	while (1) {
		*mCap >> frame;
		if (mRectangle.isShow) {
			rectangle(frame, Rect(mRectangle.left, mRectangle.top, mRectangle.right - mRectangle.left, mRectangle.bottom - mRectangle.top)
				, Scalar(0, 0, 255), 1, 1, 0);
		}
		imshow("当前视频", frame);
		waitKey(30);
	}*/
	isShow = true;
}
void FaceArmInput::setRectangle(FaceArmControlRectangle rectangle) {
	mRectangle = rectangle;
}
void  FaceArmInput::InputThread() {
	using namespace cv;
	while (true) {
		*mCap >> frame;
		if (isShow) {
			if (mRectangle.isShow) {
				rectangle(frame, Rect(mRectangle.left, mRectangle.top, mRectangle.right - mRectangle.left, mRectangle.bottom - mRectangle.top)
					, Scalar(0, 0, 255), 1, 1, 0);
			}
			imshow("当前视频", frame);
			waitKey(30);
		}
		else {
			Sleep(500);
		}
	}
}