#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include <GL/glut.h>

class Sphere{
private:
	double size = 2;

	float ALPHA = 0.4f;

	float* _materialAmbient;
	float* _materialDiffuse;
	float* _materialSpecular;
	float _shininess;

	float* _coords;

	int _listId;
	int _textureId;

	GLUquadricObj* _cone;

public:
	Sphere(int listId, int textureId);

	void display();

};

#endif