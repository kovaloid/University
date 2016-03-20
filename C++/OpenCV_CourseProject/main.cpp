#include <windows.h>
#include <cv.h>
#include <highgui.h>
#include <vector>
#include <algorithm>

#define RECT_COLORS_SIZE 10
// получение пикселя изображения (по типу картинки и координатам)
#define CV_PIXEL(type,img,x,y) (((type*)((img)->imageData+(y)*(img)->widthStep))+(x)*(img)->nChannels)

// различные цвета
//        0        1      2      3      4        5        6      7      8       9           10
enum {cBLACK=0, cWHITE, cGREY, cRED, cORANGE, cYELLOW, cGREEN, cAQUA, cBLUE, cPURPLE, NUM_COLOR_TYPES};
char* sCTypes[NUM_COLOR_TYPES] = {"Black", "White","Grey","Red","Orange","Yellow","Green","Aqua","Blue","Purple"};
uchar cCTHue[NUM_COLOR_TYPES] =    {0,       0,      0,     0,     20,      30,      60,    85,   120,    138  };
uchar cCTSat[NUM_COLOR_TYPES] =    {0,       0,      0,    255,   255,     255,     255,   255,   255,    255  };
uchar cCTVal[NUM_COLOR_TYPES] =    {0,      255,    120,   255,   255,     255,     255,   255,   255,    255  };

typedef unsigned int uint;
int flag_1=0, flag_2=0, flag_3=0, flag_4=0, flag_5=0, flag_exit=0;

// определяет какого цвета HSV пиксел и возвращает colorType между 0 и NUM_COLOR_TYPES.
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

// сортировка цветов по количеству
bool colors_sort(std::pair< int, uint > a, std::pair< int, uint > b)
{
        return (a.second > b.second);
}

// обработчик событий от мышки
void ClickOnMenu(int event, int x, int y, int flags, void* param)
{
	switch(event)
	{
	case CV_EVENT_MOUSEMOVE:
		break;
	case CV_EVENT_LBUTTONDOWN:
		{
			if((y>150) && (y<200))  //открыть
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
			if((y>200) && (y<250))  //закрыть
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
			if((y>255) && (y<305))  //выйти
				flag_exit = 1;
			break;
		}
	case CV_EVENT_LBUTTONUP:
		break;
	}
}


int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgs, int nWinMode)
{
	// переменные для хранения изображений
	IplImage *frame = 0, *image = 0, *hsv = 0, *dst = 0, *dst2 = 0, *color_indexes = 0, *dst3 = 0, *image2 = 0, *tmp = 0;
	int key = 0, zx = 0, zy = 0;

	// загружаем картинку из файла
	IplImage *menu = cvLoadImage("menu.png");
	// создаем главное окно проекта
	cvNamedWindow("Проект OpenCV");
	cvShowImage("Проект OpenCV",menu);
	cvMoveWindow("Проект OpenCV",100,50);

	// получаем любую подключенную Web-камеру
    CvCapture *capture = cvCaptureFromCAM(CV_CAP_ANY);

    // частота кадров
	double fps = 18;
	// инициализация записи видео в файл; 4-буквенный код кодека для обработки видео, формируется макросом CV_FOURCC
	CvVideoWriter *writer = cvCreateVideoWriter("record.avi", CV_FOURCC('I','Y','U','V'), fps, cvSize(640, 480), 1);

	if (!capture)
		return 0;
	else
	{
		while(key != 27)
		{
			// получаем текущий кадр
			frame = cvQueryFrame(capture);
			// копируем его для обработки
			image = cvCloneImage(frame);
	
			// зум
			if(key=='+')
			{
					zx = zx + 4;
					zy = zy + 3;
			}
			if(key=='-')
			{
					zx = zx - 4;
					zy = zy - 3;
			}
			if(zx > 300)
			{
					zx = 300;
					zy = 225;
			}
			if(zx < 0)
			{
					zx = 0;
					zy = 0;
			}

			// задаем ширину и высоту ROI
			int zwidth = frame->width-2*zx; 
			int zheight = frame->height-2*zy;

			// устанавливаем ROI (Region Of Interest — интересующая область изображения)
			cvSetImageROI(frame, cvRect(zx,zy,zwidth,zheight));
			// копируем интересующую область в переменную image2
			image2 = cvCloneImage(frame); 
			// создаем пустое изображение размером 640x480
			tmp = cvCreateImage( cvSize(640, 480), frame->depth, frame->nChannels );
			// размещаем ROI на пустое изображение tmp
			cvResize(image2, tmp, 0);

			// сохраняем кадр в видео-файл
            cvWriteFrame(writer, tmp);

			// сбрасываем ROI
			cvResetImageROI(frame);

			// инициализация шрифта
			CvFont font;
			cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX,1.0, 1.0, 0, 1, CV_AA);
			// используя шрифт выводим на картинку текст
			cvPutText(tmp, "press '+' to increase", cvPoint(150, 40), &font, CV_RGB(150, 0, 150) );
			cvPutText(tmp, "press '-' to reduce", cvPoint(165, 450), &font, CV_RGB(150, 0, 150) );

			// число пикселей данного цвета на изображении 
			uint colorCount[NUM_COLOR_TYPES] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

			hsv = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 ); 
			cvCvtColor( image, hsv, CV_BGR2HSV );

			// картинки для хранения результатов
			dst = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 ); 
			dst2 = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 );
			color_indexes = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 ); //для хранения индексов цвета

			// для хранения RGB цветов
			CvScalar rgb_colors[NUM_COLOR_TYPES];

			int i=0, j=0, x=0, y=0;

			// обнуляем цвета
			for(i=0; i<NUM_COLOR_TYPES; i++) {
					rgb_colors[i] = cvScalarAll(0);
			}

			for (y=0; y<hsv->height; y++) {
					for (x=0; x<hsv->width; x++) {

							// получаем HSV-компоненты пикселя
							uchar H = CV_PIXEL(uchar, hsv, x, y)[0];        // Hue
							uchar S = CV_PIXEL(uchar, hsv, x, y)[1];        // Saturation
							uchar V = CV_PIXEL(uchar, hsv, x, y)[2];        // Value (Brightness)

							// определяем к какому цвету можно отнести данные значения
							int ctype = getPixelColorType(H, S, V);

							// устанавливаем этот цвет у отладочной картинки
							CV_PIXEL(uchar, dst, x, y)[0] = cCTHue[ctype];  // Hue
							CV_PIXEL(uchar, dst, x, y)[1] = cCTSat[ctype];  // Saturation
							CV_PIXEL(uchar, dst, x, y)[2] = cCTVal[ctype];  // Value

							// собираем RGB-составляющие
							rgb_colors[ctype].val[0] += CV_PIXEL(uchar, image, x, y)[0]; // B
							rgb_colors[ctype].val[1] += CV_PIXEL(uchar, image, x, y)[1]; // G
							rgb_colors[ctype].val[2] += CV_PIXEL(uchar, image, x, y)[2]; // R

							// сохраняем к какому типу относится цвет
							CV_PIXEL(uchar, color_indexes, x, y)[0] = ctype;

							// подсчитываем
							colorCount[ctype]++;
					}
			}

			// усреднение RGB-составляющих
			for(i=0; i<NUM_COLOR_TYPES; i++) {
					rgb_colors[i].val[0] /= colorCount[i];
					rgb_colors[i].val[1] /= colorCount[i];
					rgb_colors[i].val[2] /= colorCount[i];
			}

			// теперь загоним массив в вектор и отсортируем
			std::vector< std::pair< int, uint > > colors;
			colors.reserve(NUM_COLOR_TYPES);

			for(i=0; i<NUM_COLOR_TYPES; i++){
					std::pair< int, uint > color;
					color.first = i;
					color.second = colorCount[i];
					colors.push_back( color );
			}
		
			// сортируем
			std::sort( colors.begin(), colors.end(), colors_sort );

			// покажем цвета
			cvZero(dst2);
			int h = dst2->height;
			int w = dst2->width / RECT_COLORS_SIZE;
			for(i=0; i<RECT_COLORS_SIZE; i++ ){
					cvRectangle(dst2, cvPoint(i*w, 0), cvPoint(i*w+w, h), rgb_colors[colors[i].first], -1);
			}

			// покажем картинку в найденных цветах
			dst3 = cvCloneImage(image);
			for (y=0; y<dst3->height; y++) {
					for (x=0; x<dst3->width; x++) {
							int color_index = CV_PIXEL(uchar, color_indexes, x, y)[0];

							CV_PIXEL(uchar, dst3, x, y)[0] = rgb_colors[color_index].val[0];
							CV_PIXEL(uchar, dst3, x, y)[1] = rgb_colors[color_index].val[1];
							CV_PIXEL(uchar, dst3, x, y)[2] = rgb_colors[color_index].val[2];
					}
			}

			// конвертируем отладочную картинку обратно в RGB
			cvCvtColor( dst, dst, CV_HSV2BGR );

			cvSetMouseCallback("Проект OpenCV", ClickOnMenu, (void*) menu);

			if(flag_1 == 1)
			{
				cvNamedWindow("Веб-камера", CV_WINDOW_AUTOSIZE);
				cvShowImage("Веб-камера", image);
			}
			else cvDestroyWindow("Веб-камера");
			if(flag_2 == 1)
			{
				cvNamedWindow("Zoom", CV_WINDOW_AUTOSIZE);
				cvShowImage("Zoom", tmp);
			}
			else cvDestroyWindow("Zoom");
			if(flag_3 == 1)
			{
				cvNamedWindow("Обнаруженные цвета");
				cvShowImage("Обнаруженные цвета", dst2);
			}
			else cvDestroyWindow("Обнаруженные цвета");
			if(flag_4 == 1)
			{
				cvNamedWindow("Изображение в обнаруженных цветах");
				cvShowImage("Изображение в обнаруженных цветах", dst3);
			}
			else cvDestroyWindow("Изображение в обнаруженных цветах");
			if(flag_5 == 1)
			{
				cvNamedWindow("Из HSV в RGB");
				cvShowImage("Из HSV в RGB", dst);
			}
			else cvDestroyWindow("Из HSV в RGB");
	
			// освобождаем ресурсы
			cvReleaseImage(&hsv);
			cvReleaseImage(&dst);
			cvReleaseImage(&dst2);
			cvReleaseImage(&color_indexes);
			cvReleaseImage(&dst3);
			cvReleaseImage(&image);
			cvReleaseImage(&image2);
			cvReleaseImage(&tmp);

			if(flag_exit == 1)
			{
				cvReleaseCapture(&capture);
				cvReleaseVideoWriter(&writer); // закрываем видео-файл
				return 0;
			}

			// если нажали ESC - выходим из цикла
			key = cvWaitKey(1);
		}

		// освобождаем инициализированные ранее переменные
		cvReleaseCapture(&capture);
		cvReleaseVideoWriter(&writer);

	}
    return 0;
}