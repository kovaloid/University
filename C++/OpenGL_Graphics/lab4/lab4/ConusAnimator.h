#ifndef _TORUS_ANIMATOR_H_
#define _TORUS_ANIMATOR_H_

#include "Conus.h"
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <math.h>

class ConusAnimator : public Conus{
private:
	double _radius = 20;		// радиус по коротой вращается
	double _circleAngle = 0;	// угол окружности по поторой вращ
	double _wheelAngle = 0;		// угол колеса
	double _speed = 0.03;		// скорость

	double _circumference = 2 * M_PI * _fullRadius;	// длина окружности колеса
	
	double _stepCircleAngle = _speed / _radius * 180 / M_PI;		// угол на кот. смещается колесо
	double _stepWheelAngle = _speed / _fullRadius * 180 / M_PI;	// угол на кот поворачивается колесо

	double _tiltAngle = 20; // угол наклона колеса в градусах
	double _yOffset = _centerRadius * cos(_tiltAngle * M_PI / 180) + _tubeRadius;

	double* _coords;

public:
	ConusAnimator(int listId, int textureId);

	void display();

};

#endif