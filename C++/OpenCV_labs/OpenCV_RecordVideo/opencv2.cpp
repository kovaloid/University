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

        // получаем любую подключЄнную камеру
        CvCapture * capture = cvCreateCameraCapture(CV_CAP_ANY);
        if(!capture){  // ≈сли не получилось - выходим
        return -1;
    }

        const char * filename = "cam_video.avi";

        // частота кадров
        double fps = 24;

        // размер картинки
        CvSize size = cvSize( (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH), (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT));
        //CvSize size = cvSize(640, 480);
		//CvSize size = cvSize(1280, 1024);

		CvVideoWriter * writer = cvCreateVideoWriter(filename, -1, fps, size, 1);

        IplImage *frame=0;

        while(true){
                // получаем кадр
                frame = cvQueryFrame( capture );

                // сохран€ем в файл
                cvWriteFrame(writer, frame);

                // показываем
                cvShowImage("capture", frame);  
                char c = cvWaitKey(1);
                if (c == 27) { // если нажата ESC - выходим
                        break;
                }
        }

        // освобождаем ресурсы
        cvReleaseCapture( &capture );
        cvReleaseVideoWriter(&writer);
        cvDestroyWindow("capture");
        return 0;
}