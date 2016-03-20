#include "Conus.h"
#include <GL/glut.h>
#include <math.h>

Conus::Conus(int listId, int textureId){
	_materialAmbient = new float[3]  { 0.2f, 0.2f, 0.2f };
	_materialDiffuse = new float[3]  { 0.5f, 0.5f, 0.5f };
	_materialSpecular = new float[3] { 0.5f, 0.5f, 0.5f };
	_shininess = 0.01 * 128;

	_coords = new float[3] {0, 0, 0};

	_listId = listId;
	_textureId = textureId;

	glNewList(_listId, GL_COMPILE);
	drawConus(_tubeRadius, _centerRadius, 20, 50);
	glEndList();
}


void Conus::display(){
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


void Conus::drawConus(double r, double c, int rSeg,	int cSeg)
{
	glFrontFace(GL_CW);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	GLUquadricObj *disk;
	disk = gluNewQuadric();
	float radius = 3.0;

	glTranslatef(0.0, 0.0, 3.0);
	glutSolidCone(radius, 8, 30, 30);
	gluDisk(disk, 0.0, radius, 30, 30);

	glFrontFace(GL_CCW);
}