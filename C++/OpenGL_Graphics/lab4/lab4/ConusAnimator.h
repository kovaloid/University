#ifndef _TORUS_ANIMATOR_H_
#define _TORUS_ANIMATOR_H_

#include "Conus.h"
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <math.h>

class ConusAnimator : public Conus{
private:
	double _radius = 20;		// ������ �� ������� ���������
	double _circleAngle = 0;	// ���� ���������� �� ������� ����
	double _wheelAngle = 0;		// ���� ������
	double _speed = 0.03;		// ��������

	double _circumference = 2 * M_PI * _fullRadius;	// ����� ���������� ������
	
	double _stepCircleAngle = _speed / _radius * 180 / M_PI;		// ���� �� ���. ��������� ������
	double _stepWheelAngle = _speed / _fullRadius * 180 / M_PI;	// ���� �� ��� �������������� ������

	double _tiltAngle = 20; // ���� ������� ������ � ��������
	double _yOffset = _centerRadius * cos(_tiltAngle * M_PI / 180) + _tubeRadius;

	double* _coords;

public:
	ConusAnimator(int listId, int textureId);

	void display();

};

#endif