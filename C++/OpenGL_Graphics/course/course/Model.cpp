#include "Model.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include <GL\glaux.h>


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
	light_position = new GLfloat[4] {5.0f, 5.0f, 20.0f, 0.0f};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	/* Создание идентификатора для текстуры */
	_textures = new GLuint[TEXTURES_NUMBER];
	glGenTextures(TEXTURES_NUMBER, _textures);

	/* Определение свойств текстуры */
	textureInit(L"tex_0.bmp", _textures[0]);
	textureInit(L"tex_1.bmp", _textures[1]);
	textureInit(L"tex_2.bmp", _textures[2]);

	_sphere = new Sphere(genListId(), _textures[1], 0.0, 0.0, 0.0, 3.0);
	_sphere2 = new Sphere(genListId(), _textures[0], -10.0, -10.0, -10.0, 5.0);
	for (int i = 0; i < molecula_count; i++) {
		_molecula[i] = new Molecula(genListId(), _textures[2]);
	}
	
	
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
	
	light_ambient = new GLfloat[4] {lightColor[0] * 0.7f, lightColor[1] * 0.7f, lightColor[2] * 0.7f, 1.0f};
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
	switch (key)
	{
	case 't':
		for (int i = 0; i < molecula_count; i++) {
			_molecula[i]->turnTextFlag();
		}
		break;
	case 'r':
		for (int i = 0; i < molecula_count; i++) {
			_molecula[i]->turnTextFlag();
		}
		break;
	case 'a':
		light_position[0] -= 0.4f;
		break;
	case 'd':
		light_position[0] += 0.4f;
		break;
	case 'w':
		light_position[1] += 0.4f;
		break;
	case 's':
		light_position[1] -= 0.4f;
		break;
	}
	calculateLightColors();
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
	}
}



void Model::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(_cameraX, _cameraY, _cameraZ,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glClearColor(0.5f, 0.5f, 0.5f, 0);

	displayLights();
	
	displayFigures();

	glutSwapBuffers();

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

	glPopMatrix();
}



void Model::displayFigures(){
	/* Включение режима нанесения текстуры */
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	_sphere->display();
	_sphere2->display();

	for (int i = 0; i < molecula_count; i++) {
		_molecula[i]->display();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}




void Model::textureInit(wchar_t fileName[], GLuint textureId)
{
	wchar_t* strFile = fileName;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	AUX_RGBImageRec *img = auxDIBImageLoad(strFile);

	/* Начало описания свойств текстуры */
	glBindTexture(GL_TEXTURE_2D, textureId);
	/* Создание уровней детализации и инициализация текстуры
	*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img->sizeX, img->sizeY, GL_RGB, GL_UNSIGNED_BYTE, img->data);

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