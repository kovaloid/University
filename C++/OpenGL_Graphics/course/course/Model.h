#ifndef _MODEL_H_
#define _MODEL_H_

#include "Model.h"
#include "Sphere.h"
#include "Molecula.h"

#include <GL/glut.h>

class Model {
protected:

	static const int TEXTURES_NUMBER = 3;
	static const int LIGHTS_NUMBER = 1;

	double _camRadius = 20;
	double _alpha = 0.3;
	double _beta = 1.3;

	float _cameraX;
	float _cameraY;
	float _cameraZ;

	float* _coordsMaterialAmbient;
	float* _coordsMaterialDiffuse;
	float* _coordsMaterialSpecular;
	float _coordsShininess = 0;

	GLfloat* lightColor;
	GLfloat* light_ambient;
	GLfloat* light_diffuse;
	GLfloat* light_specular;
	GLfloat* light_position;

	GLuint* _textures;

	float shadowMatrix[4][4];

	//Objects
	const static int molecula_count = 500;
	Sphere* _sphere;
	Sphere* _sphere2;
	Molecula* _molecula[molecula_count];
	

	int _listIdCount = 1;
	int _textureIdCount = 1;

	int genListId();
	int genTextureId();

	void calculateLightColors();

public:
	Model();

	void display();
	void displayFigures();
	void displayLights();

	void processNormalKeys(unsigned char key, int x, int y);
	void processSpecialKeys(int key, int x, int y);

	void setAlphaBeta(double a, double b);
	void setCamRadius(double rad);
	void calculateCameraLocation();

	void textureInit(wchar_t fileName[], GLuint textureId);

};

#endif