#ifndef _TORUS_H_
#define _TORUS_H_

#include <GL/glut.h>

class Conus{
protected:
	double size = 2;

	float* _materialAmbient;
	float* _materialDiffuse;
	float* _materialSpecular;
	float _shininess;

	double _centerRadius = 4;
	double _tubeRadius = 0.1;
	double _fullRadius = _tubeRadius + _centerRadius;


	float* _coords;

	int _listId;
	int _textureId;

public:
	Conus(int listId, int textureId);

	virtual void display();
	void drawConus(double r, double c, int rSeg, int cSeg);

};

#endif