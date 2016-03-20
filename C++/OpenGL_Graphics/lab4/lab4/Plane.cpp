#include "Plane.h"
#include <GL/glut.h>

Plane::Plane(int listId, int textureId){
	_materialAmbient = new float[3]  { 0.4f, 0.4f, 0.4f };
	_materialDiffuse = new float[3]  { 0.5f, 0.5f, 0.5f };
	_materialSpecular = new float[3] { 1.0f, 1.0f, 1.0f };
	_shininess = 1 * 128;

	_coords = new float[3] {0, 0, 0};

	_listId = listId;
	_textureId = textureId;

	glNewList(_listId, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(-size, 0, -size);
	glTexCoord2d(1.0, 0.0);
	glVertex3d(size, 0, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3d(size, 0, size);
	glTexCoord2d(0.0, 1.0);
	glVertex3d(-size, 0, size);
	glEnd();
	glEndList();
}


void Plane::display(){
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