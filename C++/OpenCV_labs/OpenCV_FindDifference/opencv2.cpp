#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

int main(int argc, char* argv[])
{
	IplImage *img1=0, *img2=0, *diff=0, *sub=0;

	// ��������� �������� �������� ��� ���������
	char file1[] = "tup.png";
	char file2[] = "tup2.png";

	// ��� �������� ������� ������ ����������
	char* filename1 = argc >= 2 ? argv[1] : file1;
	// �������� ��������
	img1 = cvLoadImage(filename1);
	printf("[i] first image: %s\n", filename1);

	// ��� �������� ������� ������ ����������
	char* filename2 = argc >= 3 ? argv[2] : file2;
	// �������� ��������
	img2 = cvLoadImage(filename2);
	printf("[i] second image: %s\n", filename2);

	if(!img1){
		printf("[!] cant load image: %s\n", filename1);
		return -1;
	}
	if(!img2){
		printf("[!] cant load image: %s\n", filename2);
		return -1;
	}

	if(img1->width!=img2->width || img1->height!=img2->height){
		printf("[!] different image size!\n");
		return -2;
	}

	// ������� �����������
	cvNamedWindow( "image1");
	cvShowImage( "image1", img1 );
	cvNamedWindow( "image2");
	cvShowImage( "image2", img2 );

	// ������ �������� ��� �������� �������
	diff = cvCloneImage(img1);
	sub = cvCloneImage(img1);

	cvZero(diff);

	// ����������� �� ���� �������� �����������
	for( int y=0; y<diff->height; y++ ) {
		uchar* ptr1 = (uchar*) (img1->imageData + y * img1->widthStep);
		uchar* ptr2 = (uchar*) (img2->imageData + y * img2->widthStep);
		uchar* ptr = (uchar*) (diff->imageData + y * diff->widthStep);
		for( int x=0; x<diff->width; x++ ) {
			// 3 ������:
			// B
			ptr[3*x] = ptr1[3*x] + ptr2[3*x] - 2 * min(ptr1[3*x], ptr2[3*x]);
			// G
			ptr[3*x+1] = ptr1[3*x+1] + ptr2[3*x+1] - 2 * min(ptr1[3*x+1], ptr2[3*x+1]);
			// R
			ptr[3*x+2] = ptr1[3*x+2] + ptr2[3*x+2] - 2 * min(ptr1[3*x+2], ptr2[3*x+2]);
		}
	}

	// �������� 
	cvSub(img2, img1, sub);

	// ������� ���������
	cvNamedWindow( "diff");
	cvShowImage( "diff", diff );

	cvNamedWindow( "sub");
	cvShowImage( "sub", sub );

	// ��� ������� �������
	cvWaitKey(0);

	// ����������� �������
	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	cvReleaseImage(&diff);
	cvReleaseImage(&sub);

	// ������� ����
	cvDestroyAllWindows();
	return 0;
}