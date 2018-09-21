#if 0
#include"FaceArmInput.h"
#include<stdio.h>

void main() {
	fprintf(stderr, "main\n");
	FaceArmInput *input = new FaceArmInput();
	fprintf(stderr, "showCameraVedio\n");
	//input->showCameraVedio();
	FaceArmControlRectangle tmp = {10,10,100, 100,true };
	input->setRectangle(tmp);
	int size = 0;
	//input->getBufferSize(&size);
	//fprintf(stderr, "getBufferSize size=%d\n", size);
	//unsigned char *buffer = (unsigned char *)malloc(size);
	//input->getBuffer(buffer);
	//FILE *fp = fopen("C:\\Users\\zhengln\\Desktop\\test.bmp","wb");
	//fwrite(buffer,size,1,fp);
	//fclose(fp);
	while (1);
}
#endif