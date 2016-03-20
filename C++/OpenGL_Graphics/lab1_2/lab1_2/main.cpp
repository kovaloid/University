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

GLUquadricObj *cylinder;
GLUquadricObj *conus;
GLUquadricObj *disk1;
GLUquadricObj *disk2;
GLUquadricObj *disk3;

GLuint TexId[NUM_TEXTURES];
AUX_RGBImageRec *pImage1;
AUX_RGBImageRec *pImage2;
wchar_t strFile1[] = L"texture_1.bmp";
wchar_t strFile2[] = L"texture_2.bmp";

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){

	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	// Reset transformations
	glLoadIdentity();

	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	glRotatef(-70, 1.0, 0.0, 0.0);
	glRotatef(40, 0.0, 1.0, 0.0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindTexture(GL_TEXTURE_2D, TexId[1]);

	gluCylinder(cylinder, radius, radius, height, 30, 30);
	gluDisk(disk1, 0.0, radius, 30, 30);
	glTranslatef(0.0, 0.0, height);
	gluDisk(disk2, 0.0, radius, 30, 30);

	// CONUS
	glLoadIdentity();

	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	glRotatef(-70, 1.0, 0.0, 0.0);
	glRotatef(40, 0.0, 1.0, 0.0);

	glBindTexture(GL_TEXTURE_2D, TexId[0]);

	glTranslatef(0.0, 0.0, -height);
	gluCylinder(conus, radius, 0, height, 30, 30);
	gluDisk(disk3, 0.0, radius, 30, 30);

	glFlush();
	glutSwapBuffers();
}


void TextureInit()
{
	/* Создание идентификаторов для текстур */
	glGenTextures(NUM_TEXTURES, TexId);

	cylinder = gluNewQuadric();
	conus = gluNewQuadric();
	disk1 = gluNewQuadric();
	disk2 = gluNewQuadric();
	disk3 = gluNewQuadric();

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
	gluQuadricTexture(cylinder, GL_TRUE);
	gluQuadricTexture(conus, GL_TRUE);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricDrawStyle(conus, GLU_FILL);

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
	gluQuadricTexture(disk1, GL_TRUE);
	gluQuadricTexture(disk2, GL_TRUE);
	gluQuadricTexture(disk3, GL_TRUE);
	gluQuadricDrawStyle(disk1, GLU_FILL);
	gluQuadricDrawStyle(disk2, GLU_FILL);
	gluQuadricDrawStyle(disk3, GLU_FILL);

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

	//  Request display update
	glutPostRedisplay();

}

//----------------------------------------------------------
//main() function
//----------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Conus and cylinder");

	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	TextureInit();

	// Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	// Pass control to GLUT for events
	glutMainLoop();

}