#include "Model.h"
#include "loadbmp.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>



Model::Model(){

	_camRadius = 30;
	_alpha = 1.0;
	_beta = 1.0;
	calculateCameraLocation();
	
	_coordsMaterialAmbient = new float[3] { 1, 1, 0 };
	_coordsMaterialDiffuse = new float[3] {1, 1, 0};
	_coordsMaterialSpecular = new float[3] { 0, 0, 0 };

	lightColor = new GLfloat[3] {1.0f, 1.0f, 1.0f};
	calculateLightColors();
	//light_ambient = new GLfloat[4] {0.5f, 0.5f, 0.5f, 1.0f};
	//light_diffuse = new GLfloat[4] {0.7f, 0.7f, 0.7f, 1.0f};
	//light_specular = new GLfloat[4] {1.0f, 1.0f, 1.0f, 1.0f};
	light_position = new GLfloat[4] {5.0f, 5.0f, 20.0f, 0.0f};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	/* Создание идентификатора для текстуры */
	_textures = new GLuint[TEXTURES_NUMBER];
	glGenTextures(TEXTURES_NUMBER, _textures);

	/* Определение свойств текстуры */
	textureInit("teapot.bmp", _textures[0]);
	textureInit("bump.bmp", _textures[1]);
	textureInit("sphere2.bmp", _textures[2]);
	textureInit("texture_1.bmp", _textures[3]);
	textureInit("texture_2.bmp", _textures[4]);

	_room = new Room(genListId());
	_teapot = new Teapot(genListId(), _textures[3]);
	_cube = new Cube(genListId(), _textures[1]);
//	_cyl = new Cylinder(genListId(), _textures[1]);
	_sphere = new Sphere(genListId(), _textures[2]);
}


void Model::calculateLightColors(){
	if (light_ambient != NULL){
		delete[] light_ambient;
	}
	if (light_diffuse != NULL){
		delete[] light_diffuse;
	}
	if (light_specular != NULL){
		delete[] light_specular;
	}
	
	light_ambient = new GLfloat[4] {lightColor[0] / 2, lightColor[1] / 2, lightColor[2] / 2, 1.0f};
	light_diffuse = new GLfloat[4] {lightColor[0] * 0.7f, lightColor[1] * 0.7f, lightColor[2] * 0.7f, 1.0f};
	light_specular = new GLfloat[4] {lightColor[0], lightColor[1], lightColor[2], 1.0f};
}


void Model::setAlphaBeta(double a, double b){
	_alpha = a;
	_beta = b;
	calculateCameraLocation();
}

void Model::setCamRadius(double rad){
	_camRadius = rad;
	calculateCameraLocation();
}

void Model::calculateCameraLocation(){
	_cameraX = _camRadius*sin(_beta)*cos(_alpha);
	_cameraZ = _camRadius*sin(_beta)*sin(_alpha);
	_cameraY = _camRadius*cos(_beta);
}


void Model::processNormalKeys(unsigned char key, int x, int y){
	//switch (key)
	//{
	//case 'a':
	//	light_position[0] -= 0.4f;
	//	break;
	//case 'd':
	//	light_position[0] += 0.4f;
	//	break;
	//case 'w':
	//	light_position[1] += 0.4f;
	//	break;
	//case 's':
	//	light_position[1] -= 0.4f;
	//	break;
	////Light Color
	//case 'u':
	//	lightColor[0] += 0.2f;
	//	if (lightColor[0] > 1)
	//		lightColor[0] = 1;
	//	break;
	//case 'j':
	//	lightColor[0] -= 0.2f;
	//	if (lightColor[0] < 0)
	//		lightColor[0] = 0;
	//	break;
	//case 'i':
	//	lightColor[1] += 0.2f;
	//	if (lightColor[1] > 1)
	//		lightColor[1] = 1;
	//	break;
	//case 'k':
	//	lightColor[1] -= 0.2f;
	//	if (lightColor[1] < 0)
	//		lightColor[1] = 0;
	//	break;
	//case 'o':
	//	lightColor[2] += 0.2f;
	//	if (lightColor[2] > 1)
	//		lightColor[2] = 1;
	//	break;
	//case 'l':
	//	lightColor[2] -= 0.2f;
	//	if (lightColor[2] < 0)
	//		lightColor[2] = 0;
	//	break;
	//}
	//calculateLightColors();
}

void Model::processSpecialKeys(int key, int x, int y){
	switch (key)
	{
	case GLUT_KEY_PAGE_UP:
		light_position[2] -= 0.4f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		light_position[2] += 0.4f;
		break;
	case GLUT_KEY_LEFT:
		light_position[0] -= 0.4f;
		break;
	case GLUT_KEY_RIGHT:
		light_position[0] += 0.4f;
		break;
	case GLUT_KEY_UP:
		light_position[1] += 0.4f;
		break;
	case GLUT_KEY_DOWN:
		light_position[1] -= 0.4f;
		break;
	//Light Color
	case GLUT_KEY_F1:
		lightColor[0] += 0.2f;
		if (lightColor[0] > 1)
			lightColor[0] = 1;
		break;
	case GLUT_KEY_F2:
		lightColor[0] -= 0.2f;
		if (lightColor[0] < 0)
			lightColor[0] = 0;
		break;
	case GLUT_KEY_F3:
		lightColor[1] += 0.2f;
		if (lightColor[1] > 1)
			lightColor[1] = 1;
		break;
	case GLUT_KEY_F4:
		lightColor[1] -= 0.2f;
		if (lightColor[1] < 0)
			lightColor[1] = 0;
		break;
	case GLUT_KEY_F5:
		lightColor[2] += 0.2f;
		if (lightColor[2] > 1)
			lightColor[2] = 1;
		break;
	case GLUT_KEY_F6:
		lightColor[2] -= 0.2f;
		if (lightColor[2] < 0)
			lightColor[2] = 0;
		break;
	}
	calculateLightColors();
}



void Model::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(_cameraX, _cameraY, _cameraZ,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glClearColor(0.5f, 0.5f, 0.5f, 0);

	//displayCoordLines();
	displayLights();
	
	/* очищаем буфер маски*/
	glClearStencil(0x0);
	/* включаем тест */
	glEnable(GL_STENCIL_TEST);

	/* условие всегда выполнено и значение в буфере будет равно 1*/
	glStencilFunc(GL_ALWAYS, 0x1, 0xffffffff);
	/* в любом случае заменяем значение в буфере маски*/
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	/* выводим геометрию, по которой затем будет отсечена тень*/
	_room->display(true);
	displayFigures();

	/* условие выполнено и тест дает истину только если значение в буфере маски равно 1 */
	glStencilFunc(GL_EQUAL, 0x1, 0xffffffff);
	/* значение в буфере равно 2,если тень уже выведена */
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	
	/* выводим тени */
	displayShadows();
	


	glutSwapBuffers();

}



void Model::displayShadows(){
	/* Делаем тени полупрозрачными с использованием смешения цветов(blending) */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Теперь рисуем тень...
	glDisable(GL_LIGHTING);
	glColor4f(0.0, 0.0, 0.0, 0.5);

	for (int i = 0; i < 5; i++){
		glPushMatrix();
		shadowmatrix(shadowMatrix, _room->getNormal(i), light_position);
		glMultMatrixf((GLfloat *)shadowMatrix);
		displayFigures();
		glPopMatrix();
	}

	
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);

}



void Model::displayLights(){
	glPushMatrix();

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
	glTranslatef(light_position[0], light_position[1], light_position[2]);
	glutSolidSphere(0.5, 10, 10);
	glPopMatrix();
}



void Model::displayFigures(){
	/* Включение режима нанесения текстуры */
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, _textures[2]);
	_cube->display();
	_sphere->display();
	_teapot->display();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}


/* параметры:	 plane – коэффициенты уравнения плоскости
lightpos – координаты источника света
возвращает: matrix – результирующая матрица
*/
void Model::shadowmatrix(GLfloat matrix[4][4], GLfloat plane[4], GLfloat lightpos[4])
{
	GLfloat dot;

	dot = plane[0] * lightpos[0] +
		plane[1] * lightpos[1] +
		plane[2] * lightpos[2] +
		plane[3] * lightpos[3];

	matrix[0][0] = dot - lightpos[0] * plane[0];
	matrix[1][0] = 0.f - lightpos[0] * plane[1];
	matrix[2][0] = 0.f - lightpos[0] * plane[2];
	matrix[3][0] = 0.f - lightpos[0] * plane[3];

	matrix[0][1] = 0.f - lightpos[1] * plane[0];
	matrix[1][1] = dot - lightpos[1] * plane[1];
	matrix[2][1] = 0.f - lightpos[1] * plane[2];
	matrix[3][1] = 0.f - lightpos[1] * plane[3];

	matrix[0][2] = 0.f - lightpos[2] * plane[0];
	matrix[1][2] = 0.f - lightpos[2] * plane[1];
	matrix[2][2] = dot - lightpos[2] * plane[2];
	matrix[3][2] = 0.f - lightpos[2] * plane[3];

	matrix[0][3] = 0.f - lightpos[3] * plane[0];
	matrix[1][3] = 0.f - lightpos[3] * plane[1];
	matrix[2][3] = 0.f - lightpos[3] * plane[2];
	matrix[3][3] = dot - lightpos[3] * plane[3];
}



void Model::displayCoordLines(){

	/* Определение свойств материала */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _coordsMaterialAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _coordsMaterialDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _coordsMaterialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, _coordsShininess);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(10.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 10.0);
	glEnd();

	/* Определение свойств материала */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _coordsMaterialAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _coordsMaterialDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _coordsMaterialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, _coordsShininess);

	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(
			light_position[0], 
			light_position[1], 
			light_position[2]);
		
	glEnd();
}


void Model::textureInit(char fileName[], GLuint textureId)
{
	char* strFile = fileName;
	IMAGE img;

	/* Выравнивание в *.bmp по байту */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/* Загрузка изображения в память */
	if (!LoadBMP(strFile, &img))
		return;

	/* Начало описания свойств текстуры */
	glBindTexture(GL_TEXTURE_2D, textureId);
	/* Создание уровней детализации и инициализация текстуры
	*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img.width, img.height, GL_RGB, GL_UNSIGNED_BYTE, img.data);

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



int Model::genListId(){
	return _listIdCount++;
}

int Model::genTextureId(){
	return _textureIdCount++;
}