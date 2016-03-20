#include "Sphere.h"
#include <GL/glut.h>

Sphere::Sphere(int listId, int textureId){
	_materialAmbient = new float[3]  { 0.2f, 0.2f, 0.2f };
	_materialDiffuse = new float[3]  { 0.5f, 0.5f, 0.5f };
	_materialSpecular = new float[3] { 0.5f, 0.5f, 0.5f };
	_shininess = 0.01 * 128;

	_coords = new float[3] {0, 0, 0};

	float radius = 3.0;

	GLUquadricObj* sphere = gluNewQuadric();
	_listId = listId;
	_textureId = textureId;

	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	glNewList(_listId, GL_COMPILE);
	//gluSphere(sphere, 3, 3, 10, 50, 50);
		glTranslatef(0.0, 0.0, radius);
		glutSolidSphere(radius, 30, 30);
	glEndList();
	gluDeleteQuadric(sphere);
}


void Sphere::display(){
	/* ��������� ������ ��������� �������� */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	//+++++++++++++++++++++++++++++++
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//+++++++++++++++++++++++++++++++

	/* ����������� ������� ��������� */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _materialDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, _shininess);

	glPushMatrix();
	glTranslatef(_coords[0], _coords[1], _coords[2]);
	glRotatef(-90, 1, 0, 0);
	glCallList(_listId);
	glPopMatrix();

	//+++++++++++++++++++++++++++++++
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	//+++++++++++++++++++++++++++++++


	glDisable(GL_TEXTURE_2D);

}