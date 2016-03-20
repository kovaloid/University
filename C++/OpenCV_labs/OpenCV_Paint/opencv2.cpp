#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <cmath>

using namespace std;

#define blue  CV_RGB(0,0,255)
#define green CV_RGB(0,255,0)
#define red   CV_RGB(255,0,0)
#define white CV_RGB(255,255,255)
#define black CV_RGB(0,0,0)

void ClearScreen(IplImage* imgScribble, IplImage* imgDrawing)
{
    cvSet(imgScribble, black);
    cvSet(imgDrawing, white);
}

IplImage* GetThresholdedImage(IplImage* img, CvScalar& lowerBound, CvScalar& upperBound)
{
    // Convert the image into an HSV image
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);

    IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);

    cvInRangeS(imgHSV, lowerBound, upperBound, imgThreshed);

    cvReleaseImage(&imgHSV);
    return imgThreshed;
}

int main()
{
    // controls
    double area_limit = 700;
    //CvScalar lowerBound = cvScalar(20, 100, 100);  // yellow
    //CvScalar upperBound = cvScalar(30, 255, 255);
	CvScalar lowerBound = cvScalar(70, 100, 50);  // green
    CvScalar upperBound = cvScalar(90, 255, 255);

    // defaults
    int lineThickness = 2;
    CvScalar lineColor = blue;


    CvCapture* capture = 0;
    capture = cvCaptureFromCAM(0);
    if(!capture)
    {
        cout << "Could not initialize capturing...\n";
        return -1;
    }

    // This image holds the "scribble" data...
    // the tracked positions of the pointer object
    IplImage* imgScribble = NULL;


    IplImage* imgColorPanel = 0;
    imgColorPanel = cvLoadImage( "cvPaint.panel",  CV_LOAD_IMAGE_COLOR ); // load the panel image. (This is a png image, not designed/included in the source code!) 
    if(!imgColorPanel)
    {
        cout << "cvPaint.panel is not found !!! \n";
        return -1;
    }

    IplImage* imgDrawing = 0;
    imgDrawing = cvCreateImage( cvSize(cvQueryFrame(capture)->width,cvQueryFrame(capture)->height),
                                cvQueryFrame(capture)->depth,     //Bit depth per channel
                                3  //number of channels
                              );
    cvSet(imgDrawing, white);

    CvFont font, fontbig;
    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 1, .6, 0, 2, CV_AA);
    cvInitFont( &fontbig, CV_FONT_HERSHEY_COMPLEX, 3, .6, 0, 3, CV_AA);

    int confirm_close = 10, confirm_clear = 20; // counters for clear and exit confirmation
    char buffer [50]; // buffer for cvPutText
    int image_num = 0; // to keep track of image numbers for saving
    int posX = 0;
    int posY = 0;

    while(true)
    {
        IplImage* frame = 0;
        frame = cvQueryFrame(capture);
        if(!frame)
            break;
        cvFlip(frame,NULL,1); // flip the frame to overcome mirroring problem



        // If this is the first frame, we need to initialize it
        if(imgScribble == NULL)
            imgScribble = cvCreateImage(cvGetSize(frame), 8, 3);

        // Median filter to decrease the background noise
        cvSmooth( frame, frame,
                  CV_MEDIAN,
                  5, 5 //parameters for filter, in this case it is filter size
                );


        // Holds the thresholded image (tracked color -> white, the rest -> black)
        IplImage* imgThresh = GetThresholdedImage(frame,lowerBound,upperBound);

        // Calculate the moments to estimate the position of the object
        CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
        cvMoments(imgThresh, moments, 1);


        // The actual moment values
        double moment10 = cvGetSpatialMoment(moments, 1, 0);
        double moment01 = cvGetSpatialMoment(moments, 0, 1);
        double area = cvGetCentralMoment(moments, 0, 0);

        // Holding the last and current positions
        int lastX = posX;
        int lastY = posY;

        posX = 0;
        posY = 0;


        if(moment10/area>=0 && moment10/area < 1280 && moment01/area >=0 && moment01/area < 1280
           && area>area_limit /* to control the limit */ )
        {
            posX = moment10/area;
            posY = moment01/area;
        }



        CvPoint cvpoint = cvPoint(150,30); // location of the text
        if(posX < 90 && posY > 400) // clear
        {
            lineColor = white; // white color works as eraser
            cvPutText( frame, "Eraser selected.", cvpoint, &font, white );
            sprintf (buffer, "Clearing the screen in %d",confirm_clear); // count-down for clearing the screen
            cvPutText( frame, buffer, cvPoint(150,70), &font, red );
            confirm_clear--;
            if(confirm_clear < 0) // confirm in 10 frames before clearing
            {
                confirm_clear = 20;
                sprintf (buffer, "d0%d.jpg",image_num++);
                cvSaveImage(buffer ,imgDrawing); // save the frame into an image
                ClearScreen(imgScribble,imgDrawing);
                cvPutText( frame, "Cleared the screen.", cvPoint(150,110), &font, white );
            }
        }
        else if(posX  > 540 && posY > 360)  // blue
        {
            lineColor = blue;
            cvPutText( frame, "Blue color selected.", cvpoint, &font, blue );
        }

        else if(posX  > 540 && posY > 200 && posY < 280) // green
        {
            lineColor = green;
            cvPutText( frame, "Green color selected.", cvpoint, &font, green );
        }

        else if(posX  > 540 && posY < 120) // red
        {
            lineColor = red;
            cvPutText( frame, "Red color selected.", cvpoint, &font, red );
        }

        else if(posX > 0 && posX  < 90 && posY > 0 && posY < 120) // exit
        {
            sprintf (buffer, "EXITING in %d",confirm_close);
            cvPutText( frame, buffer, cvpoint, &font, red );
            confirm_close--;
            if(confirm_close < 0) // confirm in 10 frames before exit
                break;
        }
        else if(posX < 90 && posY > 130 && posY < 390) // line thickness
        {
            lineThickness = 6 - ( posY/60-1 );  // change the thickness of line from 1 - 5 based on posY
        }


        sprintf (buffer, "%d",lineThickness);
        cvPutText( frame, buffer, cvPoint(40,255), &fontbig, lineColor );

		double diff_X = lastX-posX;
		double diff_Y = lastY-posY;
        double magnitude = sqrt(   pow(diff_X,2) + pow(diff_Y,2)   );
        // We want to draw a line only if its a valid position
        //if(lastX>0 && lastY>0 && posX>0 && posY>0)
        if(magnitude > 0 && magnitude < 100 && posX > 120 && posX<530)
        {
            // Draw a line from the previous point to the current point
            cvLine(imgDrawing, cvPoint(posX, posY), cvPoint(lastX, lastY), lineColor, lineThickness,CV_AA);
        }


        //cout << "position = " << posX << "\t" <<  posY << "\t";
        //cout << "moment = " << moment10 << "\t" <<  moment01 << "\n";
        //cout << "d->" << magnitude << endl;
        //cout << "area = " << area << endl;

        // Add the scribbling image and the frame...
        cvAdd(imgDrawing, imgScribble, imgDrawing);

        // Combine everything in frame
        cvAnd(frame, imgDrawing, frame);
        cvAnd(imgColorPanel, frame, frame);

        cvShowImage("Threshold", imgThresh);
        cvShowImage("Drawing", imgDrawing);
        cvShowImage("Video", frame);


        int c = cvWaitKey(10);
        if(c==27)  //ESC key
            break;
        //else if(c==49) // 1 key


        cvReleaseImage(&imgThresh);
        delete moments;
    }

    cvReleaseCapture(&capture);
    cvReleaseImage(&imgColorPanel);
    cvReleaseImage(&imgScribble);

    return 0;
}