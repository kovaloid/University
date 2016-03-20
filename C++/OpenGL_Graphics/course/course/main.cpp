#include <gl/glut.h>
#include <windows.h>
#include "Manager.h"

Manager* manager;


void display(){
	manager->display();
}


void resize(int w, int h){
	manager->resize(w, h);
}


void processNormalKeys(unsigned char key, int x, int y){
	manager->processNormalKeys(key, x, y);
}


void processSpecialKeys(int key, int x, int y){
	manager->processSpecialKeys(key, x, y);
}


void onMouseClick(int button, int state, int x, int y){
	manager->onMouseClick(button, state, x, y);
}


void onMouseMove(int x, int y){
	manager->onMouseMove(x, y);
}


//void timer(int i){
	// keeps calling display every 30 milliseconds
	//display();
	//glutTimerFunc(1000, timer, 0);
//}


// *** MAIN ***
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	manager = new Manager();
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);

	glutInitWindowSize(manager->WIDTH, manager->HEIGHT);
	glutInitWindowPosition(5, 5);
	glutCreateWindow("Course");

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(resize);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(onMouseClick);
	glutMotionFunc(onMouseMove);

	manager->init();

	//timer(0);

	glutMainLoop();

	//return 0;
}