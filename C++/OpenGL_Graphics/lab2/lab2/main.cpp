#include <GL\glut.h>
#include <GL\glaux.h>
#include <windows.h>
#include <math.h>

#define NUM_TEXTURES 2

//----------------------------------------------------------
// Function Prototypes
//----------------------------------------------------------
void display();
void specialKeys();
void TextureInit();

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;

double height = 0.8;
double radius = 0.3;

GLUquadricObj *sphere;

GLuint TexId[NUM_TEXTURES];
AUX_RGBImageRec *pImage1;
AUX_RGBImageRec *pImage2;
wchar_t strFile1[] = L"texture_3.bmp";
wchar_t strFile2[] = L"texture_2.bmp";


float xx = 0.0, yy = 0.0, zz = 0.0;
float step = 1.0;

float light1_x = -1.0, light1_y = 1.0;


/* параметры материала тора */
float mat1_dif[] = { 0.8f, 0.8f, 0.0f };
float mat1_amb[] = { 0.2f, 0.2f, 0.2f };
float mat1_spec[] = { 0.6f, 0.6f, 0.6f };
float mat1_shininess = 0.3f * 128;

/* параметры материала конуса */
float mat2_dif[] = { 0.0f, 0.0f, 0.8f };
float mat2_amb[] = { 0.2f, 0.2f, 0.2f };
float mat2_spec[] = { 0.6f, 0.6f, 0.6f };
float mat2_shininess = 0.4f * 128;

/* параметры материала шара */
float mat3_dif[] = { 0.9f, 0.2f, 0.0f };
float mat3_amb[] = { 0.2f, 0.2f, 0.2f };
float mat3_spec[] = { 1.0f, 1.0f, 1.0f };
float mat3_shininess = 0.1f * 128;

/* Инициализируем параметры материалов и
* источника света
*/
void init(void)
{
	GLfloat light0_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_position[] = { 1.0, 1.0, 1.0, 0.0 };

	GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light1_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat light1_position[] = { light1_x, light1_y, 1.0, 1.0 };
	GLfloat light1_direction[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light1_cutoff = 60.0;
	GLfloat light1_exp = 15.0;


	/* устанавливаем параметры источника света */
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	/* устанавливаем параметры источника света */
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1_cutoff);
	//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, light1_exp);

	/* включаем освещение и источник света */
	glEnable(GL_LIGHTING);
	//GLfloat param[] = { 3.5, 3.5, 3.5, 0.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, param);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	/* включаем z-буфер */
	glEnable(GL_DEPTH_TEST);

}


// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){

	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	init();



	glLoadIdentity();

	gluLookAt(
		0.0f + xx, 0.0f + yy, 5.0f + zz, /* положение камеры */
		0.0f, 0.0f, 0.0f, /* центр сцены */
		0.0f, 1.0f, 0.0f); /* положительное направление оси y */




	// Reset transformations
	//glLoadIdentity();

	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TexId[1]);

	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	/* отображаем шар */
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat3_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat3_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat3_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, mat3_shininess);
	gluSphere(sphere, radius, 30, 30);


	glDisable(GL_TEXTURE_2D);

	
	//glLoadIdentity();

	// Rotate when user changes rotate_x and rotate_y
	//glRotatef(rotate_x, 1.0, 0.0, 0.0);
	//glRotatef(rotate_y, 0.0, 1.0, 0.0);

	//glRotatef(-70, 1.0, 0.0, 0.0);
	//glRotatef(40, 0.0, 1.0, 0.0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	glBindTexture(GL_TEXTURE_2D, TexId[0]);

	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor4f(1.0, 0.0, 0.0, 0.5);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat2_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat2_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, mat2_shininess);
	glutSolidCube(0.6);


	/* отображаем тор */
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat1_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, mat1_shininess);
	glutSolidTorus(0.15, 0.6, 30, 30);

	glDisable(GL_BLEND);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	glFlush();
	glutSwapBuffers();
}


void reshape(int w, int h)
{
	/* устанавливаем размер области вывода
	* равным размеру окна
	*/
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	/* задаем матрицу проекции с учетом размеров окна */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluPerspective(
	//	40.0, /* угол зрения в градусах */
	//	(GLfloat)w / h, /* коэффициент сжатия окна */
	//	1, 100.0);  /* расстояние до плоскостей отсечения */

	glOrtho(-1.2, 1.2, -1.2, 1.2, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
}


void TextureInit()
{
	/* Создание идентификаторов для текстур */
	glGenTextures(NUM_TEXTURES, TexId);
	
	sphere = gluNewQuadric();


	/* Выравнивание в *.bmp по байту */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	/* Загрузка изображения в память */
	pImage1 = auxDIBImageLoad(strFile1);

	/* Начало описания свойств текстуры */
	glBindTexture(GL_TEXTURE_2D, TexId[0]);
	/* Создание уровней детализации и инициализация текстуры
	*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pImage1->sizeX,
		pImage1->sizeY, GL_RGB, GL_UNSIGNED_BYTE,
		pImage1->data);
	/* Разрешение наложения этой текстуры на quadric-объекты
	*/
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricDrawStyle(sphere, GLU_FILL);

	/* Задание параметров текстуры */
	/* Повтор изображения по параметрическим осям s и t */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/* Не использовать интерполяцию при выборе точки на
	* текстуре
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	/* Совмещать текстуру и материал объекта */
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//----------------------------------------------------------

	/* Выравнивание в *.bmp по байту */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	/* Загрузка изображения в память */
	pImage2 = auxDIBImageLoad(strFile2);

	/* Начало описания свойств текстуры */
	glBindTexture(GL_TEXTURE_2D, TexId[1]);
	/* Создание уровней детализации и инициализация текстуры
	*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pImage2->sizeX,
		pImage2->sizeY, GL_RGB, GL_UNSIGNED_BYTE,
		pImage2->data);
	/* Разрешение наложения этой текстуры на quadric-объекты
	*/
	

	/* Задание параметров текстуры */
	/* Повтор изображения по параметрическим осям s и t */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/* Не использовать интерполяцию при выборе точки на
	* текстуре
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	/* Совмещать текстуру и материал объекта */
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys(int key, int x, int y) {

	//  Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;


	else if (key == GLUT_KEY_F1)
		xx -= step;

	else if (key == GLUT_KEY_F2)
		xx += step;

	else if (key == GLUT_KEY_PAGE_DOWN)
		yy -= step;

	else if (key == GLUT_KEY_PAGE_UP)
		yy += step;

	else if (key == GLUT_KEY_F3)
		zz -= step;

	else if (key == GLUT_KEY_F4)
		zz += step;

	/*if (key == GLUT_KEY_RIGHT)
		light1_x += 1.0;

	else if (key == GLUT_KEY_LEFT)
		light1_x -= 1.0;

	else if (key == GLUT_KEY_UP)
		light1_y += 1.0;

	else if (key == GLUT_KEY_DOWN)
		light1_y -= 1.0;*/

	//  Request display update
	glutPostRedisplay();

}

//----------------------------------------------------------
//main() function
//----------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	

	// Create window
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Light");

	//  Enable Z-buffer depth test
	//glEnable(GL_DEPTH_TEST);

	TextureInit();
	//init();

	// Callback functions
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	// Pass control to GLUT for events
	glutMainLoop();

}