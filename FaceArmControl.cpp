#if 1
#include "FaceArmControl.h"
FaceArmControl::FaceArmControl() {
	mInput = new FaceArmInput();
	mTraking = new FaceArmTracking(this);
}
FaceArmControl::~FaceArmControl() {
	delete mInput;
	delete mTraking;
	free(mSurface->buffer);
	free(mSurface);
}
int FaceArmControl::getPreviewData(FaceArmControlSurfaceBuffer **surface) {
	if (mInput == NULL) {
		fprintf(stderr, "mInput is not init\n");
		return -1;
	}
	mSurface = (FaceArmControlSurfaceBuffer*)malloc(sizeof(FaceArmControlSurfaceBuffer));
	mSurface->buffer = (unsigned char *)malloc(mInput->getBufferSize());
	mInput->getBuffer(mSurface);
	*surface = mSurface;
	return 0;
}
int FaceArmControl::showSource() {
	if (mInput == NULL) {
		fprintf(stderr, "mInput is not init\n");
		return -1;
	}
	mInput->showCameraVedio();
}
void FaceArmControl::setRectangle(FaceArmControlRectangle rectangle) {
	mInput->setRectangle(rectangle);
}
int FaceArmControl::TrackingFace() {
	mTraking->TrackingFace();
	return 0;
}
int main() {
	FaceArmControl control;
	control.showSource();
	control.TrackingFace();
	while (1) {
		Sleep(1000);
	}
	return 0;
}
#endif