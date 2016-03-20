#ifndef _TEAPOT_H_
#define _TEAPOT_H_

#include <GL/glut.h>

class Teapot{
private:
	double size = 2;

	float* _materialAmbient;
	float* _materialDiffuse;
	float* _materialSpecular;
	float _shininess;

	float* _coords;

	int _listId;
	int _textureId;

	GLUquadricObj* _cone;

public:
	Teapot(int listId, int textureId);

	void display();

};

#endif