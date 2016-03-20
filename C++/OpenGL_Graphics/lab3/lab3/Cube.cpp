#include "Cube.h"
#include <GL/glut.h>
#include "loadbmp.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <stdio.h>

Cube::Cube(int listId, int textureId){
	_materialAmbient = new float[3]  { 0.2f, 0.2f, 0.2f };
	_materialDiffuse = new float[3]  { 0.2f, 0.0f, 0.0f };
	_materialSpecular = new float[3] { 0.9f, 0.0f, 0.0f };
	_shininess = 0.1 * 128;

	_coords = new float[3] {1, -8, 3};

	_listId = listId;
	_textureId = textureId;


	glNewList(_listId, GL_COMPILE);
	drawCyl(0.5, 2, 20, 50, _textureId);
	glEndList();
}

void Cube::drawCyl(double r = 0.07, double c = 0.15, int rSeg = 16,
	int cSeg = 8, int texture = 0)
{
	glFrontFace(GL_CW);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glutSolidCube(4);
	glFrontFace(GL_CCW);
}


void Cube::display(){
	/* Включение режима нанесения текстуры */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

//+++++++++++++++++++++++++++++++
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//+++++++++++++++++++++++++++++++

	/* Определение свойств материала */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _materialDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, _shininess);
	glPushMatrix();
	glTranslatef(_coords[0], _coords[1], _coords[2]);
	glCallList(_listId);
	glPopMatrix();

//+++++++++++++++++++++++++++++++
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
//+++++++++++++++++++++++++++++++

	glDisable(GL_TEXTURE_2D);
}