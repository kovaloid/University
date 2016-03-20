#include "Sphere.h"
#include <GL/glut.h>
#include <math.h>

Sphere::Sphere(int listId, int textureId){
	_materialAmbient = new float[4]  { 0.2f, 0.2f, 0.2f, ALPHA };
	_materialDiffuse = new float[4]  { 0.5f, 0.5f, 0.5f, ALPHA };
	_materialSpecular = new float[4] { 0.5f, 0.5f, 0.5f, ALPHA };
	_shininess = 0.1 * 128;

	_coords = new float[3] {-4, -8, 5};

	_listId = listId;
	_textureId = textureId;

	glNewList(_listId, GL_COMPILE);
	drawSphere(0.5, 2, 20, 50, _textureId);
	glEndList();
}


void Sphere::display(){
	/* Включение режима нанесения текстуры */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

//+++++++++++++++++++++++++++++++
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
//+++++++++++++++++++++++++++++++

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Определение свойств материала */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _materialDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, _shininess);

	glPushMatrix();
	glTranslatef(_coords[0], _coords[1], _coords[2]);
	glCallList(_listId);
	glPopMatrix();

	glDisable(GL_BLEND);

//+++++++++++++++++++++++++++++++
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
//+++++++++++++++++++++++++++++++

	glDisable(GL_TEXTURE_2D);

}


void Sphere::drawSphere(double r = 0.07, double c = 0.15, int rSeg = 16,
	int cSeg = 8, int texture = 0)
{
	glFrontFace(GL_CW);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	const double PI = 3.1415926535897932384626433832795;
	const double TAU = 2 * PI;

	/*for (int i = 0; i < rSeg; i++) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= cSeg; j++) {
			for (int k = 0; k <= 1; k++) {
				double s = (i + k) % rSeg + 0.5;
				double t = j % (cSeg + 1);

				double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
				double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
				double z = r * sin(s * TAU / rSeg);

				double u = (i + k) / (float)rSeg;
				double v = t / (float)cSeg;

				double xc = c * cos(t * TAU / cSeg);
				double yc = c * sin(t * TAU / cSeg);
				double zc = 0;

				glTexCoord2d(u, v);
				glNormal3f(x - xc, y - yc, z - zc);
				glVertex3d(2 * x, 2 * y, 2 * z);
			}
		}
		glEnd();
	}*/
	glutSolidSphere(2, 30, 30);

	glFrontFace(GL_CCW);
}