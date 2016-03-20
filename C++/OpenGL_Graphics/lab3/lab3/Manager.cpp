#include "Manager.h"
#include "Model.h"

#include <GL/glut.h>
#include <stdio.h>

Manager::Manager(){
	_camRadius = 40;
	_alpha = 1.4;
	_beta = 1.4;
}

void Manager::init(){
	_model = new Model();
	_model->setAlphaBeta(_alpha, _beta);
	_model->setCamRadius(_camRadius);
}


void Manager::resize(int w, int h){
	if (h == 0)
		h = 1;

	float ratio = 1.0 * w / h;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);

}



void Manager::onMouseClick(int button, int state, int x, int y){
	_rotateCamera = false;
	if (button == GLUT_LEFT_BUTTON){
		mouseOldX = x;
		mouseOldY = y;
		_rotateCamera = true;
	}
	if (button == 3){
		_camRadius -= 1;
		if (_camRadius < 1)
			_camRadius = 1;
		_model->setCamRadius(_camRadius);
	}
	else if (button == 4){
		_camRadius += 1;
		if (_camRadius > 70)
			_camRadius = 70;
		_model->setCamRadius(_camRadius);
	}
}


void Manager::onMouseMove(int x, int y){
	if (_rotateCamera){
		_alpha += (x - mouseOldX)*0.005;
		_beta -= (y - mouseOldY)*0.005;

		if (_beta < 0){
			_beta = 0.00001;
		}
		else if (_beta > 3.1415){
			_beta = 3.1415;
		}

		_model->setAlphaBeta(_alpha, _beta);

		mouseOldX = x;
		mouseOldY = y;

		glutPostRedisplay();
	}
}



void Manager::processNormalKeys(unsigned char key, int x, int y){
	//switch (key)
	//{
	//case VK_ESCAPE:
	//	exit(0);
	//	break;
	//}
	_model->processNormalKeys(key, x, y);
}



void Manager::processSpecialKeys(int key, int x, int y){
	_model->processSpecialKeys(key, x, y);

}



void Manager::display(){
	_model->display();
}