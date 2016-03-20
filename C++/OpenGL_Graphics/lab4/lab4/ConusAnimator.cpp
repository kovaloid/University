#include "ConusAnimator.h"
#include <GL/glut.h>
//#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

ConusAnimator::ConusAnimator(int listId, int textureId) : Conus(listId, textureId){

	_coords = new double[3] {0, 5, 0};
}


void ConusAnimator::display(){

	glRotated(_circleAngle, 0, 1, 0);	// �������� ������ ������� �������
	glTranslatef(0, _yOffset, 0);	// ���������� �� ������
	glTranslatef(0, 0, -_radius);		// �������, ����� ������� ����
	glRotated(_tiltAngle, 1, 0, 0);		// ��������� ������
	glRotated(_wheelAngle, 0, 0, 1);	// �������� ������

	/*glBegin(GL_LINES);
	glVertex3f(-10.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glVertex3f(0.0, -10.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glVertex3f(0.0, 0.0, -10.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();*/

	Conus::display();

	_circleAngle += _stepCircleAngle;
	_wheelAngle += _stepWheelAngle;
}
