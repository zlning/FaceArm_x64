#if 1
#include "FaceArmInput.h"
using namespace std;

FaceArmInput::FaceArmInput() {
	mCap = new cv::VideoCapture(0);
	//mCap = new cv::VideoCapture("E:\\TDDOWNLOAD\\13948491-1-hd.mp4");

	/*mCap->set(CV_CAP_PROP_FRAME_WIDTH, 1080);
	mCap->set(cv::CV_CAP_PROP_FRAME_HEIGHT, 960);
	mCap->set(cv::CV_CAP_PROP_FPS, 30);*/

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
	mInputThread = new thread(&FaceArmInput::InputThread, this);
}
FaceArmInput::~FaceArmInput() {
}
int FaceArmInput::getBufferSize() {
	if (mCap == NULL) {
		fprintf(stderr, "mCap is not init\n");
		return -1;
	}
	//*mCap >> frame;
	return frame.total()*3;
}
void FaceArmInput::getBuffer(FaceArmControlSurfaceBuffer *surface) {
	using namespace cv;
	if (mCap==NULL) {
		fprintf(stderr, "mCap is not init\n");
		return;
	}
	surface->width = frame.cols;
	surface->height = frame.rows;
	surface->buffersize = frame.total()*3;
	memcpy(surface->buffer, frame.data, frame.total()*3);
	/*
	for (int i = 0; i < frame.rows; ++i)
	{
		for (int j = 0; j < frame.cols; ++j)
		{
			cv::Vec3b p;
			surface->buffer[i * frame.cols * 3 + j * 3] = frame.at<cv::Vec3b>(i, j)[0];
			surface->buffer[i * frame.cols * 3 + j * 3 + 1] = frame.at<cv::Vec3b>(i, j)[1];
			surface->buffer[i * frame.cols * 3 + j * 3 + 2] = frame.at<cv::Vec3b>(i, j)[2];
		}
	}*/
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
#if 0
			for (int i = 0; i < frame.rows; ++i)
			{
				for (int j = 0; j < frame.cols; ++j)
				{
					Vec3b p;
					p[0] = rand() % 255;
					p[1] = rand() % 255;
					p[2] = rand() % 255;
				//	frame.at<Vec3b>(i, j) = p;
					frame.at<Vec3b>(i, j)[0]= rand() % 255;
				}
			}
#endif
			imshow("当前视频", frame);
			waitKey(30);
		}
		else {
			Sleep(500);
		}
	}
}
#endif