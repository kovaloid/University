#include <cv.h>
#include <highgui.h>
#include <stdio.h>

//#include <iostream>
//#include <..\opencv2\core\core.hpp> 
//#include <..\opencv2\imgproc\imgproc.hpp> 
//#include <..\opencv2\imgproc\imgproc_c.h>

//#pragma comment(lib, "opencv_highgui249.lib")
//#pragma comment(lib, "opencv_core249.lib")
//#pragma comment(lib, "opencv_objdetect249.lib")
//#pragma comment(lib, "opencv_imgproc249.lib")

int main(int argc, char* argv[])
{
        cvNamedWindow("capture");

        // �������� ����� ������������ ������
        CvCapture * capture = cvCreateCameraCapture(CV_CAP_ANY);
        if(!capture){  // ���� �� ���������� - �������
        return -1;
    }

        const char * filename = "cam_video.avi";

        // ������� ������
        double fps = 24;

        // ������ ��������
        CvSize size = cvSize( (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH), (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT));
        //CvSize size = cvSize(640, 480);
		//CvSize size = cvSize(1280, 1024);

		CvVideoWriter * writer = cvCreateVideoWriter(filename, -1, fps, size, 1);

        IplImage *frame=0;

        while(true){
                // �������� ����
                frame = cvQueryFrame( capture );

                // ��������� � ����
                cvWriteFrame(writer, frame);

                // ����������
                cvShowImage("capture", frame);  
                char c = cvWaitKey(1);
                if (c == 27) { // ���� ������ ESC - �������
                        break;
                }
        }

        // ����������� �������
        cvReleaseCapture( &capture );
        cvReleaseVideoWriter(&writer);
        cvDestroyWindow("capture");
        return 0;
}