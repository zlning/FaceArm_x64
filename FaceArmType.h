#pragma once
#define FaceArm_FACENUM 4
struct FaceArmControlRectangle {
	int left;
	int top;
	int right;
	int bottom;
	bool isShow;
};
struct FaceArmControlSurfaceBuffer {
	int width;
	int height;
	bool isShow;
	int buffersize;
	unsigned char *buffer;
	int biBitCount;
	int type;
}; 