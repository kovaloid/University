#ifndef _ROOM_H_
#define _ROOM_H_

#include <GL/glut.h>

class Room{
private:
	const double SIDE = 20;
	const double SIDE_2 = SIDE / 2;
	
	float R;
	float ALPHA = 1.0f;

	float* _materialAmbient;
	float* _materialDiffuse;
	float* _materialSpecular;
	float _shininess;

	float* vertexArr;
	float* displayArr;
	float* textureArr;
	float* normalsArr;

	double* _coords;

	int _listId = 0;

	void justDisplay(bool textured);

public:
	Room(int listId);

	void display(bool textured);
	void display1();
	float* getNormal(int plane);

};

#endif