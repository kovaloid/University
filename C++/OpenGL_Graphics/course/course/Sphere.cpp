#include "Sphere.h"
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

Sphere::Sphere(int listId, int textureId, float x, float y, float z, float radius){
	_materialAmbient = new float[3]  { 0.2f, 0.2f, 0.2f };
	_materialDiffuse = new float[3]  { 0.5f, 0.5f, 0.5f };
	_materialSpecular = new float[3] { 0.5f, 0.5f, 0.5f };
	_shininess = 0.01 * 128;

	_coords = new float[3] {x, y, z};

	this->radius = radius;

	GLUquadricObj* sphere = gluNewQuadric();
	_listId = listId;
	_textureId = textureId;

	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	glNewList(_listId, GL_COMPILE);
	gluSphere(sphere, radius, 30, 30);

	glEndList();
	gluDeleteQuadric(sphere);
}

void Sphere::display(){
	/* Включение режима нанесения текстуры */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	/* Определение свойств материала */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _materialDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, _shininess);

	glPushMatrix();
	glTranslatef(_coords[0], _coords[1], _coords[2]);
	
	glCallList(_listId);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}

