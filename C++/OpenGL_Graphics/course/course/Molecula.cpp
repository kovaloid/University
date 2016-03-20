#include "Molecula.h"
#include <GL\glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

Molecula::Molecula(int listId, int textureId)
{
	_materialAmbient = new float[4]  { 0.2f, 0.2f, 0.2f, ALPHA };
	_materialDiffuse = new float[4]  { 0.5f, 0.5f, 0.5f, ALPHA };
	_materialSpecular = new float[4] { 0.5f, 0.5f, 0.5f, ALPHA };
	_shininess = 0.01 * 128;

	_coords = new float[3] {0, 0, 0};

	GLUquadricObj* _molecula = gluNewQuadric();
	_listId = listId;
	_textureId = textureId;

	gluQuadricTexture(_molecula, GL_TRUE);
	gluQuadricNormals(_molecula, GLU_SMOOTH);

	glNewList(_listId, GL_COMPILE);
	
	gluSphere(_molecula, radius, 30, 30);

	glEndList();
	gluDeleteQuadric(_molecula);


	srand(rand() % 100000);

	float sphere_radius = 3.0;
	float a = rand() % 2000 - 1000;
	float b = rand() % 2000 - 1000;
	_x_start = sphere_radius*cos(a)*cos(b);
	_y_start = sphere_radius*sin(a)*cos(b);
	_z_start = sphere_radius*sin(b);

	_x_dest = _x_start * 100;
	_y_dest = _y_start * 100;
	_z_dest = _z_start * 100;

	_x_current = _x_start;
	_y_current = _y_start;
	_z_current = _z_start;

	_speed = 1000;
	_accel = -5;

	srand(rand() % 10000);
	float red = rand() % 2000 - 1000;
	float green = rand() % 2000 - 1000;
	float blue = rand() % 2000 - 1000;
	red = red*0.001;
	green = green*0.001;
	blue = blue*0.001;
	_materialDiffuse = new float[4]  { red, green, blue, ALPHA };
}


void Molecula::display()
{
	if (texFlag) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _textureId);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	}
	else {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _materialDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, _shininess);

	glPushMatrix();

	Molecula::moveMolecula();

	glCallList(_listId);
	glPopMatrix();


	if (texFlag) {
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_2D);
	}
	else {
		glDisable(GL_BLEND);
	}
	
}

void Molecula::moveMolecula()
{
	glPushMatrix();
	glTranslatef(_x_old1, _y_old1, _z_old1);
	glutSolidSphere(0.25, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(_x_old2, _y_old2, _z_old2);
	glutSolidSphere(0.20, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(_x_old3, _y_old3, _z_old3);
	glutSolidSphere(0.15, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(_x_old4, _y_old4, _z_old4);
	glutSolidSphere(0.10, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(_x_old5, _y_old5, _z_old5);
	glutSolidSphere(0.05, 5, 5);
	glPopMatrix();

	if (_x_current <= -5 && _y_current <= -5 && _z_current <= -5 &&
		_x_current >= -15 && _y_current >= -15 && _z_current >= -15) {

		_x_start = _x_current;
		_y_start = _y_current;
		_z_start = _z_current;

		_x_dest = 10000.0;
		_y_dest = 10000.0;
		_z_dest = 1000.0;

		_speed = 50;

		_x_current += _speed * (_x_dest - _x_start) / _dtime;
		_y_current += _speed * (_y_dest - _y_start) / _dtime;
		_z_current += _speed * (_z_dest - _z_start) / _dtime;

		flag = true;
	}
	else {
		if (!flag) {
			if (_speed < 1)
				_speed = 0;
			else
				_speed += _accel;
		}


		_x_current += _speed * (_x_dest - _x_start) / _dtime;
		_y_current += _speed * (_y_dest - _y_start) / _dtime;
		_z_current += _speed * (_z_dest - _z_start) / _dtime;
	}

	glTranslatef(_x_current, _y_current, _z_current);

	_x_old5 = _x_old4;
	_y_old5 = _y_old4;
	_z_old5 = _z_old4;

	_x_old4 = _x_old3;
	_y_old4 = _y_old3;
	_z_old4 = _z_old3;

	_x_old3 = _x_old2;
	_y_old3 = _y_old2;
	_z_old3 = _z_old2;

	_x_old2 = _x_old1;
	_y_old2 = _y_old1;
	_z_old2 = _z_old1;

	_x_old1 = _x_current;
	_y_old1 = _y_current;
	_z_old1 = _z_current;

}

void Molecula::turnTextFlag()
{
	if (texFlag)
		texFlag = false;
	else
		texFlag = true;
}