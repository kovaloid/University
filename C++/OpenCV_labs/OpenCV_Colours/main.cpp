/*
10. ��� � OpenCV. ��������� ���������� ����� � avi-����. ����
��� � ����������� ����� ������������ ����� ��� ������������
����� � ���...
*/

#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define RECT_COLORS_SIZE 10
// ��������� ������� ����������� (�� ���� �������� � �����������)
#define CV_PIXEL(type,img,x,y) (((type*)((img)->imageData+(y)*(img)->widthStep))+(x)*(img)->nChannels)

using namespace std;

// ��������� �����
//        0        1      2      3      4        5        6      7      8       9           10
enum {cBLACK=0, cWHITE, cGREY, cRED, cORANGE, cYELLOW, cGREEN, cAQUA, cBLUE, cPURPLE, NUM_COLOR_TYPES};
char* sCTypes[NUM_COLOR_TYPES] = {"Black", "White","Grey","Red","Orange","Yellow","Green","Aqua","Blue","Purple"};
uchar cCTHue[NUM_COLOR_TYPES] =    {0,       0,      0,     0,     20,      30,      60,    85,   120,    138  };
uchar cCTSat[NUM_COLOR_TYPES] =    {0,       0,      0,    255,   255,     255,     255,   255,   255,    255  };
uchar cCTVal[NUM_COLOR_TYPES] =    {0,      255,    120,   255,   255,     255,     255,   255,   255,    255  };

typedef unsigned int uint;
int flag_1=0, flag_2=0, flag_3=0, flag_4=0, flag_5=0, flag_exit=0;

// ���������� ������ ����� HSV ������ � ���������� colorType ����� 0 � NUM_COLOR_TYPES.
int getPixelColorType(int H, int S, int V)
{
        int color = cBLACK;

#if 1
        if (V < 75)
                color = cBLACK;
        else if (V > 190 && S < 27)
                color = cWHITE;
        else if (S < 53 && V < 185)
                color = cGREY;
        else 
#endif
        {       
                if (H < 7)
                        color = cRED;
                else if (H < 25)
                        color = cORANGE;
                else if (H < 34)
                        color = cYELLOW;
                else if (H < 73)
                        color = cGREEN;
                else if (H < 102)
                        color = cAQUA;
                else if (H < 140)
                        color = cBLUE;
                else if (H < 170)
                        color = cPURPLE;
                else    // full circle 
                        color = cRED;   // back to Red
        }
        return color;
}

// ���������� ������ �� ����������
bool colors_sort(std::pair< int, uint > a, std::pair< int, uint > b)
{
        return (a.second > b.second);
}

// �-� ���������� ������ �� ������ ���������� ������� � ������������ (x,y) � ����������� image
char* gsp(IplImage *image, int x, int y)
{
	return image->imageData + y*image->width*3 + x*3;
}

// �-� ������� �������� ������� r � ����������� image
void Frame(IplImage *image, CvRect *r)
{
	CvPoint pt1 = { r->x, r->y };
	CvPoint pt2 = { r->x + r->width, r->y + r->height };
	cvRectangle(image, pt1, pt2, CV_RGB(0,0,255), 3, 4, 0);
}

void ClickOnMenu(int event, int x, int y, int flags, void* param)
{
	switch(event)
	{
	case CV_EVENT_MOUSEMOVE:
		break;
	case CV_EVENT_LBUTTONDOWN:
		{
			if((y>150) && (y<200))  //�������
			{
				if((x>0) && (x<170))
					flag_1 = 1;
				if((x>170) && (x<340))
					flag_2 = 1;
				if((x>340) && (x<505))
					flag_3 = 1;
				if((x>505) && (x<675))
					flag_4 = 1;
				if((x>675) && (x<845))
					flag_5 = 1;
			}
			if((y>200) && (y<250))  //�������
			{
				if((x>0) && (x<170))
					flag_1 = 0;
				if((x>170) && (x<340))
					flag_2 = 0;
				if((x>340) && (x<505))
					flag_3 = 0;
				if((x>505) && (x<675))
					flag_4 = 0;
				if((x>675) && (x<845))
					flag_5 = 0;
			}
			if((y>255) && (y<305))  //�����
				flag_exit = 1;
			break;
		}
	case CV_EVENT_LBUTTONUP:
		break;
	}
}


void main()
{
	IplImage *menu = 0;
	char img_menu[] = "menu.png";
	menu = cvLoadImage(img_menu);
	cvNamedWindow("������ OpenCV");
	cvShowImage("������ OpenCV",menu);
	cvMoveWindow("������ OpenCV",100,50);

	// ����� ROI
	int zx, zy, zwidth, zheight;
	IplImage *image2 = 0;
	int counter_x = 0, counter_y = 0;
	IplImage *tmp = 0;

	// ������ ������������� ��� ������ ���
	CvHaarClassifierCascade *pCascade = (CvHaarClassifierCascade*)cvLoad("haarcascade_frontalface_default.xml", 0, 0, 0 );
	// ������ ����������� ��������� ��� ��������� ��������
	CvMemStorage *pStorage = cvCreateMemStorage(0);
	// ��������� ����������, ��� �������� ������������������
	CvSeq *pFaceRectSeq = 0; CvRect *r = 0;

	// �������� Web-������
    CvCapture *capture = cvCaptureFromCAM(CV_CAP_ANY);
    IplImage *frame = 0, *image = 0, *hsv = 0, *dst = 0, *dst2 = 0, *color_indexes = 0, *dst3 = 0;
	int key = 0, last = 0;

	// �������� ����� �����
	const char * filename = "cam_video.avi";
    // ������� ������
	double fps = 8;
    // ������ ��������
    CvSize size = cvSize( (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH), (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT));
	CvVideoWriter * writer = cvCreateVideoWriter(filename, CV_FOURCC('I','Y','U','V') /* -1 */, fps, size, 1);

    if (!pStorage || !pCascade || !capture)
		cout << "Initialization failed" << endl;
	else
	{
		while(key != 27)
		{
			// �������� ������� ����
			frame = cvQueryFrame(capture);
			// �������� ��� ��� ���������
			image = cvCloneImage(frame);
	
			// ���
			if(key=='+')
			{
					counter_x = counter_x + 4;
					counter_y = counter_y + 3;
			}
			if(key=='-')
			{
					counter_x = counter_x - 4;
					counter_y = counter_y - 3;
			}
			if(counter_x > 300)
			{
					counter_x = 300;
					counter_y = 225;
			}
			if(counter_x < 0)
			{
					counter_x = 0;
					counter_y = 0;
			}

			zx = counter_x;
			zy = counter_y;
			zwidth = frame->width-2*counter_x;
			zheight = frame->height-2*counter_y;

			// ������������� ROI
			cvSetImageROI(frame, cvRect(zx,zy,zwidth,zheight));
			image2 = cvCloneImage(frame);
			tmp = cvCreateImage( cvSize(640, 480), frame->depth, frame->nChannels );
			cvResize(image2, tmp, 0);

			// ������������� ������
			CvFont font;
			cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX,1.0, 1.0, 0, 1, CV_AA);
			CvPoint pt = cvPoint( 150, 40 );
			cvPutText(tmp, "press '+' to increase", pt, &font, CV_RGB(150, 0, 150) );
			CvPoint pt2 = cvPoint( 165, 450 );
			cvPutText(tmp, "press '-' to reduce", pt2, &font, CV_RGB(150, 0, 150) );

			// ���������� ROI
			cvResetImageROI(frame);
			//cvShowImage("ZOOM", tmp);

			// ��������� � ����
            cvWriteFrame(writer, tmp);

			// ���� ����
			pFaceRectSeq = cvHaarDetectObjects(image, pCascade, pStorage, 1.1, 3, CV_HAAR_DO_CANNY_PRUNING, cvSize(75,75));

			// ���������� ����
			for(int i=0; i<(pFaceRectSeq? pFaceRectSeq->total:0); i++ )
			{
				// �������� ������� ����
				r = (CvRect*)cvGetSeqElem(pFaceRectSeq, i);
				// ��������� ������ �� ������
				switch(last)
				{
				case '1': Frame(image, r); break;
				//case '2': MyFilter(image, r); break;
				default: break;
				}
			}

			// ����� �������� ������� ����� �� ����������� 
			uint colorCount[NUM_COLOR_TYPES] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

			hsv = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 ); 
			cvCvtColor( image, hsv, CV_BGR2HSV );

			// �������� ��� �������� �����������
			dst = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 ); 
			dst2 = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 );
			color_indexes = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 ); //��� �������� �������� �����

			// ��� �������� RGB-� ������
			CvScalar rgb_colors[NUM_COLOR_TYPES];

			int i=0, j=0, x=0, y=0;

			// �������� �����
			for(i=0; i<NUM_COLOR_TYPES; i++) {
					rgb_colors[i] = cvScalarAll(0);
			}

			for (y=0; y<hsv->height; y++) {
					for (x=0; x<hsv->width; x++) {

							// �������� HSV-���������� �������
							uchar H = CV_PIXEL(uchar, hsv, x, y)[0];        // Hue
							uchar S = CV_PIXEL(uchar, hsv, x, y)[1];        // Saturation
							uchar V = CV_PIXEL(uchar, hsv, x, y)[2];        // Value (Brightness)

							// ���������� � ������ ����� ����� ������� ������ ��������
							int ctype = getPixelColorType(H, S, V);

							// ������������� ���� ���� � ���������� ��������
							CV_PIXEL(uchar, dst, x, y)[0] = cCTHue[ctype];  // Hue
							CV_PIXEL(uchar, dst, x, y)[1] = cCTSat[ctype];  // Saturation
							CV_PIXEL(uchar, dst, x, y)[2] = cCTVal[ctype];  // Value

							// �������� RGB-������������
							rgb_colors[ctype].val[0] += CV_PIXEL(uchar, image, x, y)[0]; // B
							rgb_colors[ctype].val[1] += CV_PIXEL(uchar, image, x, y)[1]; // G
							rgb_colors[ctype].val[2] += CV_PIXEL(uchar, image, x, y)[2]; // R

							// ��������� � ������ ���� ��������� ����
							CV_PIXEL(uchar, color_indexes, x, y)[0] = ctype;

							// ������������ :)
							colorCount[ctype]++;
					}
			}

			// ���������� RGB-������������
			for(i=0; i<NUM_COLOR_TYPES; i++) {
					rgb_colors[i].val[0] /= colorCount[i];
					rgb_colors[i].val[1] /= colorCount[i];
					rgb_colors[i].val[2] /= colorCount[i];
			}

			// ������ ������� ������ � ������ � �����������
			std::vector< std::pair< int, uint > > colors;
			colors.reserve(NUM_COLOR_TYPES);

			for(i=0; i<NUM_COLOR_TYPES; i++){
					std::pair< int, uint > color;
					color.first = i;
					color.second = colorCount[i];
					colors.push_back( color );
			}
		
			// ���������
			std::sort( colors.begin(), colors.end(), colors_sort );

			// ��� ������� - ������� ����, �������� ������ � �� ����������
			for(i=0; i<colors.size(); i++){
					printf("[i] color %d (%s) - %d\n", colors[i].first, sCTypes[colors[i].first], colors[i].second );
			}

			// ����� ��� ������ ������
			printf("[i] color code: \n");
			for(i=0; i<NUM_COLOR_TYPES; i++)
					printf("%02d ", colors[i].first);
			printf("\n");
			printf("[i] color names: \n");
			for(i=0; i<NUM_COLOR_TYPES; i++)
					printf("%s ", sCTypes[colors[i].first]);
			printf("\n");

			// ������� �����
			cvZero(dst2);
			int h = dst2->height;
			int w = dst2->width / RECT_COLORS_SIZE;
			for(i=0; i<RECT_COLORS_SIZE; i++ ){
					cvRectangle(dst2, cvPoint(i*w, 0), cvPoint(i*w+w, h), rgb_colors[colors[i].first], -1);
			}

			// ������� �������� � ��������� ������
			dst3 = cvCloneImage(image);
			for (y=0; y<dst3->height; y++) {
					for (x=0; x<dst3->width; x++) {
							int color_index = CV_PIXEL(uchar, color_indexes, x, y)[0];

							CV_PIXEL(uchar, dst3, x, y)[0] = rgb_colors[color_index].val[0];
							CV_PIXEL(uchar, dst3, x, y)[1] = rgb_colors[color_index].val[1];
							CV_PIXEL(uchar, dst3, x, y)[2] = rgb_colors[color_index].val[2];
					}
			}

			// ������������ ���������� �������� ������� � RGB
			cvCvtColor( dst, dst, CV_HSV2BGR );

			cvSetMouseCallback("������ OpenCV", ClickOnMenu, (void*) menu);

			if(flag_1 == 1)
			{
				cvNamedWindow("WebCamera", CV_WINDOW_AUTOSIZE);
				cvShowImage("WebCamera", image);
			}
			else cvDestroyWindow("WebCamera");
			if(flag_2 == 1)
			{
				cvNamedWindow("ZOOM", CV_WINDOW_AUTOSIZE);
				cvShowImage("ZOOM", tmp);
			}
			else cvDestroyWindow("ZOOM");
			if(flag_3 == 1)
			{
				cvNamedWindow("detected colors");
				cvShowImage("detected colors", dst2);
			}
			else cvDestroyWindow("detected colors");
			if(flag_4 == 1)
			{
				cvNamedWindow("picture with detected colors");
				cvShowImage("picture with detected colors", dst3);
			}
			else cvDestroyWindow("picture with detected colors");
			if(flag_5 == 1)
			{
				cvNamedWindow("from HSV to RGB");
				cvShowImage("from HSV to RGB", dst);
			}
			else cvDestroyWindow("from HSV to RGB");
			if(flag_exit == 1)
			{
				cvReleaseImage(&hsv);
				cvReleaseImage(&dst);
				cvReleaseImage(&dst2);
				cvReleaseImage(&color_indexes);
				cvReleaseImage(&dst3);
				cvReleaseImage(&image);
				cvReleaseCapture(&capture);
				cvReleaseVideoWriter(&writer);
				cvReleaseHaarClassifierCascade(&pCascade);
				cvReleaseMemStorage(&pStorage);
				cvDestroyWindow("WebCamera");
				cvDestroyWindow("ZOOM");
				cvDestroyWindow("detected colors");
				cvDestroyWindow("picture with detected colors");
				cvDestroyWindow("from HSV to RGB");
				exit(0);
			}
	
			// ����������� �������
			cvReleaseImage(&hsv);
			cvReleaseImage(&dst);
			cvReleaseImage(&dst2);
			cvReleaseImage(&color_indexes);
			cvReleaseImage(&dst3);

			//����������� ������ �� ��� �����
			cvReleaseImage(&image);
			key = cvWaitKey(1);
			if (key != -1) last = key;
		}

		// ����������� ������������������ ����� ����������
		cvReleaseCapture(&capture);
		cvReleaseVideoWriter(&writer);

		cvReleaseHaarClassifierCascade(&pCascade);
		cvReleaseMemStorage(&pStorage);
	}


}