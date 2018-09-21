#if 1
#include"FaceArmTracking.h"
#pragma comment(lib,"libarcsoft_fsdk_face_tracking.lib")

#define WORKBUF_SIZE        (40*1024*1024)
#define APPID		"9GZf8wkVFqBEvHW56EfWXUBrtQqjY9N1CATwKSZrUVuY"			//APPID
#define SDKKey		"G8EkecWGgWV5kfj6EQ1mjPxs28x3tyePyWEVLrmryNw2"			//SDKKey
using namespace std;

FaceArmTracking::FaceArmTracking(FaceArmControl *Control) {
	/* 初始化引擎和变量 */
	MRESULT nRet = MERR_UNKNOWN;
	MInt32 nScale = 16;
	MInt32 nMaxFace = 10;
	pWorkMem = (MByte *)malloc(WORKBUF_SIZE);
	if (pWorkMem == nullptr)
	{
		fprintf(stderr, "pWorkMem is not init\n");
		return ;
	}
	nRet = AFT_FSDK_InitialFaceEngine(APPID, SDKKey, pWorkMem, WORKBUF_SIZE, &hEngine, AFT_FSDK_OPF_0_HIGHER_EXT, nScale, nMaxFace);
	if (nRet != MOK)
	{
		fprintf(stderr, "FaceEngine is not init\n");
		return ;
	}
	/* 打印版本信息 */
	const AFT_FSDK_Version * pVersionInfo = nullptr;
	pVersionInfo = AFT_FSDK_GetVersion(hEngine);
	fprintf(stdout, "%d %d %d %d\n", pVersionInfo->lCodebase, pVersionInfo->lMajor, pVersionInfo->lMinor, pVersionInfo->lBuild);
	fprintf(stdout, "%s\n", pVersionInfo->Version);
	fprintf(stdout, "%s\n", pVersionInfo->BuildDate);
	fprintf(stdout, "%s\n", pVersionInfo->CopyRight);

	/* 读取视频帧数据，并保存到ASVLOFFSCREEN结构体 */
	//ASVLOFFSCREEN offInput = { 0 };
	mTrackThread = new thread(&FaceArmTracking::TrackingThread,this);
	mFaceArmControl = Control;
	isTracking = false;
}
FaceArmTracking::~FaceArmTracking() {
	MRESULT nRet = MERR_UNKNOWN;
	nRet = AFT_FSDK_UninitialFaceEngine(hEngine);
	if (nRet != MOK)
	{
		fprintf(stderr, "UninitialFaceEngine failed , errorcode is %d \n", nRet);
	}
	free(offInput.ppu8Plane[0]);
	free(pWorkMem);
}
void FaceArmTracking::TrackingFace() {
	isTracking = true;
}
void FaceArmTracking::TrackingThread() {
	MRESULT nRet = MERR_UNKNOWN;
	int frame = 1;
	while (true) {
		if (isTracking) {
			FaceArmControlSurfaceBuffer *surface = NULL;
			mFaceArmControl->getPreviewData(&surface);
			//==========offInput==========
			offInput.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
			offInput.ppu8Plane[0] = nullptr;

			offInput.i32Width = surface->width;
			offInput.i32Height = surface->height;
			offInput.pi32Pitch[0] = offInput.i32Width * 3;
			memcpy(offInput.ppu8Plane[0], surface->buffer, surface->buffersize);
			//=======================//
			LPAFT_FSDK_FACERES	FaceRes = nullptr;

			/* 人脸跟踪 */
			nRet = AFT_FSDK_FaceFeatureDetect(hEngine, &offInput, &FaceRes);
			if (nRet != MOK)
			{
				fprintf(stderr, "Face Tracking failed, error code: %d\n", nRet);
			}
			else
			{
				fprintf(stdout, "The number of face: %d\n", FaceRes->nFace);
				for (int i = 0; i < FaceRes->nFace; i++)
				{
					if (i == 0) {
						FaceArmControlRectangle tmp = { 10,10,100, 100,true };
						tmp.left = FaceRes->rcFace[i].left;
						tmp.right = FaceRes->rcFace[i].right;
						tmp.top = FaceRes->rcFace[i].top;
						tmp.bottom = FaceRes->rcFace[i].bottom;
						tmp.isShow = true;
						mFaceArmControl->setRectangle(tmp);
					}
					fprintf(stdout, "Frame : %d, Face[%d]: rect[%d,%d,%d,%d]\n", frame++, i, FaceRes->rcFace[i].left, FaceRes->rcFace[i].top, FaceRes->rcFace[i].right, FaceRes->rcFace[i].bottom);
				}
			}
		}
	}
}
#endif