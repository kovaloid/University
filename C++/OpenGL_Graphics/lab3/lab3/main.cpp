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



// *** MAIN ***
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	//glutInit(&argc, argv);
	
	manager = new Manager();
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);

	glutInitWindowSize(manager->WIDTH, manager->HEIGHT);
	glutInitWindowPosition(5, 5);
	glutCreateWindow("Lab 2");

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(resize);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(onMouseClick);
	glutMotionFunc(onMouseMove);

	manager->init();

	glutMainLoop();

	return 0;
}