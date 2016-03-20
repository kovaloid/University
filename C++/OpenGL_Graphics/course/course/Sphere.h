#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <GL/glut.h>

class Sphere{
private:
	double size = 2;

	float radius;
	float ALPHA = 0.4f;

	float* _materialAmbient;
	float* _materialDiffuse;
	float* _materialSpecular;
	float _shininess;

	float* _coords;

	int _listId;
	int _textureId;
public:
	Sphere(int listId, int textureId, float x, float y, float z, float radius);
	void display();

};

#endif