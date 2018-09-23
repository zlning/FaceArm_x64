#if 0
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/types_c.h>
#include <Windows.h>
#include "arcsoft_fsdk_face_tracking.h"
#include "merror.h"

#pragma comment(lib,"libarcsoft_fsdk_face_tracking.lib")

#define WORKBUF_SIZE        (40*1024*1024)
#define APPID		"9GZf8wkVFqBEvHW56EfWXUBrtQqjY9N1CATwKSZrUVuY"			//APPID
#define SDKKey		"G8EkecWGgWV5kfj6EQ1mjPxs28x3tyePyWEVLrmryNw2"			//SDKKey

/* 获取视频帧数据，并保存到ASVLOFFSCREEN结构体中 */
MRESULT GetPreviewData(ASVLOFFSCREEN *offInput)
{
	MInt32 res = MOK;

	/* get frame data. add your code here */
	/* ... ... */
	cv::VideoCapture capture(0);
	cv::Mat edges;
	cv::Mat frame;
	capture >> frame;
	cv::waitKey(30);
	int lineByte = ((frame.cols) * 24 / 8 + 3) / 4 * 4;
	offInput->ppu8Plane[0] = (unsigned char *)malloc(lineByte * frame.rows);
	fprintf(stdout, "fram=%d ppu8Plane=%d \n", lineByte * frame.rows, frame.total());

	for (int i = 0; i < frame.rows; ++i)
	{
		for (int j = 0; j < frame.cols; ++j)
		{
			cv::Vec3b p;
			p[0] = rand() % 255;
			p[1] = rand() % 255;
			p[2] = rand() % 255;
			//	frame.at<Vec3b>(i, j) = p;
			//offInput->ppu8Plane[0][0] = frame.at<cv::Vec3b>(i, j)[0] //= rand() % 255;
			//memcpy(offInput->ppu8Plane[0] + i * (*pWidth) * 3 + j * 3, frame.at<cv::Vec3b>(i, j), 3);
			offInput->ppu8Plane[0][i * frame.cols * 3 + j * 3] = frame.at<cv::Vec3b>(i, j)[0];
			offInput->ppu8Plane[0][i * frame.cols * 3 + j * 3 + 1] = frame.at<cv::Vec3b>(i, j)[1];
			offInput->ppu8Plane[0][i * frame.cols * 3 + j * 3 + 2] =  frame.at<cv::Vec3b>(i, j)[2];
		}
	}
	offInput->u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;

	offInput->i32Height = frame.rows;
	offInput->i32Width = frame.cols;
		offInput->pi32Pitch[0] = offInput->i32Width * 3;
	return res;
}
int main()
{
	/* 初始化引擎和变量 */
	MRESULT nRet = MERR_UNKNOWN;
	MHandle hEngine = nullptr;
	MInt32 nScale = 16;
	MInt32 nMaxFace = 10;
	MByte *pWorkMem = (MByte *)malloc(WORKBUF_SIZE);
	if (pWorkMem == nullptr)
	{
		return -1;
	}
	nRet = AFT_FSDK_InitialFaceEngine(APPID, SDKKey, pWorkMem, WORKBUF_SIZE, &hEngine, AFT_FSDK_OPF_0_HIGHER_EXT, nScale, nMaxFace);
	if (nRet != MOK)
	{
		return -1;
	}
	/* 打印版本信息 */
	const AFT_FSDK_Version * pVersionInfo = nullptr;
	pVersionInfo = AFT_FSDK_GetVersion(hEngine);
	fprintf(stdout, "%d %d %d %d\n", pVersionInfo->lCodebase, pVersionInfo->lMajor, pVersionInfo->lMinor, pVersionInfo->lBuild);
	fprintf(stdout, "%s\n", pVersionInfo->Version);
	fprintf(stdout, "%s\n", pVersionInfo->BuildDate);
	fprintf(stdout, "%s\n", pVersionInfo->CopyRight);

	/* 读取视频帧数据，并保存到ASVLOFFSCREEN结构体 */
	ASVLOFFSCREEN offInput = { 0 };
	int frame = 1;
	while (MOK == GetPreviewData(&offInput))
	{
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
				fprintf(stdout, "Frame : %d, Face[%d]: rect[%d,%d,%d,%d]\n", frame++, i, FaceRes->rcFace[i].left, FaceRes->rcFace[i].top, FaceRes->rcFace[i].right, FaceRes->rcFace[i].bottom);
			}
		}
	}
	/* 释放引擎和内存 */
	nRet = AFT_FSDK_UninitialFaceEngine(hEngine);
	if (nRet != MOK)
	{
		fprintf(stderr, "UninitialFaceEngine failed , errorcode is %d \n", nRet);
	}
	free(offInput.ppu8Plane[0]);
	free(pWorkMem);
	return 0;
}
#endif
