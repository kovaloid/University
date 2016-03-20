#ifndef _PLANE_H_
#define _PLANE_H_

#include <GL/glut.h>

class Plane{
private:
	double size = 20;

	float* _materialAmbient;
	float* _materialDiffuse;
	float* _materialSpecular;
	float _shininess;

	float* _coords;

	int _listId;
	int _textureId;

public:
	Plane(int listId, int textureId);

	void display();

};

#endif