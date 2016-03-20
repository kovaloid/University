#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "Model.h"

class Manager {
private:
	Model* _model;

	bool _rotateCamera = false;
	double _camRadius = 20;
	double _alpha = 0.3;
	double _beta = 1.3;
	int mouseOldX = 0;
	int mouseOldY = 0;

public:
	const int WIDTH = 1200;
	const int HEIGHT = 700;

	Manager();

	void init();

	void display();
	void resize(int w, int h);
	void processNormalKeys(unsigned char key, int x, int y);
	void processSpecialKeys(int key, int x, int y);
	void onMouseClick(int button, int state, int x, int y);
	void onMouseMove(int x, int y);

	void setAlphaBeta(double a, double b);
	void setCamRadius(double rad);

};

#endif