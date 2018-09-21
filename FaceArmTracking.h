#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#pragma once
#include <thread>
#include <Windows.h>
#include "arcsoft_fsdk_face_tracking.h"
#include "merror.h"
#include "FaceArmControl.h"
#include "FaceArmType.h"
//typedef void(FaceArmControl::*getFunc)(FaceArmControlSurfaceBuffer *surface);
class FaceArmControl;
class FaceArmTracking{
public:
	FaceArmTracking(FaceArmControl *Control);
	~FaceArmTracking();
	void TrackingThread();
	void TrackingFace();
private:
	bool isTracking;
	MHandle hEngine;
	MByte *pWorkMem;
	ASVLOFFSCREEN offInput;
	FaceArmControl *mFaceArmControl;
	std::thread *mTrackThread;
};
