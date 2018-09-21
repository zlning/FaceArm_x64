#pragma once
#include "FaceArmInput.h"
#include "FaceArmTracking.h"
#include "FaceArmType.h"
class FaceArmInput;
class FaceArmTracking;
class FaceArmControl {
public:
	FaceArmControl();
	~FaceArmControl();
	int getPreviewData(FaceArmControlSurfaceBuffer **surface);
	int showSource();
	int TrackingFace();
	void setRectangle(FaceArmControlRectangle rectangle);
private:
	FaceArmInput *mInput;
	FaceArmTracking *mTraking;
	FaceArmControlSurfaceBuffer *mSurface;
};
