#include "Teapot.h"
#include <GL/glut.h>

Teapot::Teapot(int listId, int textureId){
	_materialAmbient = new float[3] { 0.2f, 0.2f, 0.2f };
	_materialSpecular = new float[3] { 0.5f, 0.5f, 0.5f };
	_materialDiffuse = new float[3] { 0.5f, 0.5f, 0.5f };
	_shininess = 1 * 128;

	_coords = new float[3] {1, -4.5, 3};

	_listId = listId;
	_textureId = textureId;

	glNewList(_listId, GL_COMPILE);
	glutSolidTeapot(size);
	glEndList();
}


void Teapot::display(){
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