#ifndef _CUBE_H_
#define _CUBE_H_

#include <GL/glut.h>

struct Coords{
	float x, y, z;
	float nx, ny, nz;
};


class Cube{
private:
	static const int PARTS_HORIZONTAL = 200;
	static const int PARTS_VERTICAL = 200;
	static const int RADIUS = 2;
	static const int CYLINDER_HEIGHT = 4;
	static const int vertexNumber = PARTS_HORIZONTAL * (PARTS_VERTICAL + 1);
	int bumpPriods = 5;


	float* _materialAmbient;
	float* _materialDiffuse;
	float* _materialSpecular;
	float _shininess;

	float* _coords;

	float* cubeVertex;
	int cubeTotalVertex;
	float* cubeTexCoords;
	float* cubeNormals;
	Coords* cube;
	int vertexToDraw = 4 * PARTS_HORIZONTAL * PARTS_VERTICAL;

	int _listId;
	int _textureId;

	GLUquadricObj* _cone;

public:
	Cube(int listId, int textureId);

	void display();

	void drawCyl(double r, double c, int rSeg, int cSeg, int texture);

	void initVertexCube();
	void generateArrayToDraw(float* &vertexArr, float* &texCoords, Coords* coords);

};

#endif