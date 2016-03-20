/*#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

int main()
{
	CvCapture *capture = cvCreateCameraCapture(0);
	if(capture == NULL)
	return 0;
	IplImage *frame = NULL;
	IplImage* gray = 0;
	IplImage* bin = 0;
	IplImage* dst = 0;
	cvNamedWindow("camera", CV_WINDOW_AUTOSIZE);
	while(1)
	{
		frame = cvQueryFrame(capture); 

		gray = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );
		bin = cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );

		dst = cvCloneImage(frame);

		cvCvtColor(frame, gray, CV_RGB2GRAY);

		cvInRangeS(gray, cvScalar(40), cvScalar(150), bin); // atoi(argv[2])
		CvMemStorage* storage = cvCreateMemStorage(0);
		CvSeq* contours=0;

		int contoursCont = cvFindContours( bin, storage,&contours,sizeof(CvContour),
		CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));

		for(CvSeq* seq0 = contours;seq0!=0;seq0 = seq0->h_next){
			cvDrawContours(dst, seq0, CV_RGB(255,0,0), CV_RGB(0,0,250), 0, 1, 8);
		}

		cvShowImage("camera", dst); 
		cvReleaseImage(&gray);
		cvReleaseImage(&bin);
		cvReleaseImage(&dst);
		char c = cvWaitKey(33); 
		if(c == 27)break; 
	}
	cvReleaseCapture(&capture);
	return 0;
}*/

//----------------------------------------------------------------------------------

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <stdio.h>
#include <conio.h>

int main()
{
	IplImage *src, *templ,*ftmp[6]; //ftmp is what to display on
	int i;

	char* filename = "cat.jpg";
	char* filename0 = "eye.jpg";
	

	// загрузка изображения
	if((src=cvLoadImage(filename, 1))== 0) {
		printf("Error on reading src image\n");
		_getch();
		return(-1);
	}

	// загрузка шаблона
	if((templ=cvLoadImage(filename0, 1))== 0) {
		printf("Error on reading template\n");
		_getch();
		return(-1);
	}

	int patchx = templ->width;
	int patchy = templ->height;
	int iwidth = src->width - patchx + 1;
	int iheight = src->height - patchy + 1;
	for(i=0; i<6; ++i){
		ftmp[i] = cvCreateImage( cvSize(iwidth,iheight),32,1);
	}

	// сравнение шаблона с изображением
	for(i=0; i<6; ++i){
		cvMatchTemplate( src, templ, ftmp[i], i); 
		//		double min,max;
		//		cvMinMaxLoc(ftmp,&min,&max);
		cvNormalize(ftmp[i],ftmp[i],1,0,CV_MINMAX);
	}
	// показываем
	cvNamedWindow( "Template");
	cvShowImage(   "Template", templ );
	cvNamedWindow( "Image");
	cvShowImage(   "Image", src );

	cvNamedWindow( "SQDIFF" );
	cvShowImage( "SQDIFF", ftmp[0] );

	cvNamedWindow( "SQDIFF_NORMED" );
	cvShowImage(   "SQDIFF_NORMED", ftmp[1] );

	cvNamedWindow( "CCORR" );
	cvShowImage(   "CCORR", ftmp[2] );

	cvNamedWindow( "CCORR_NORMED" );
	cvShowImage(   "CCORR_NORMED", ftmp[3] );

	cvNamedWindow( "CCOEFF" );
	cvShowImage(   "CCOEFF", ftmp[4] );

	cvNamedWindow( "CCOEFF_NORMED" );
	cvShowImage(   "CCOEFF_NORMED", ftmp[5] );

	// ждём нажатия клавиши
	cvWaitKey(0);
	return 0;
} 