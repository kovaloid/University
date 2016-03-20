#include <GL\glut.h>
#include <GL\glaux.h>
#include <windows.h>
#include <math.h>


//----------------------------------------------------------
// Function Prototypes
//----------------------------------------------------------
void display();
void specialKeys();

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;

double cube_side = 0.5;
double radius = sqrt(3 * (cube_side / 2) * (cube_side / 2));

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){

	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// CUBE
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRotatef(10, -1.0, 1.0, 0.0);
	glTranslatef(radius, 0.0, 0.0);

	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	//Red side - FRONT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(cube_side / 2, -cube_side / 2, -cube_side / 2);      
	glVertex3f(cube_side / 2, cube_side / 2, -cube_side / 2);         
	glVertex3f(-cube_side / 2, cube_side / 2, -cube_side / 2);     
	glVertex3f(-cube_side / 2, -cube_side / 2, -cube_side / 2);      
	glEnd();

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(cube_side / 2, -cube_side / 2, cube_side / 2);
	glVertex3f(cube_side / 2, cube_side / 2, cube_side / 2);
	glVertex3f(-cube_side / 2, cube_side / 2, cube_side / 2);
	glVertex3f(-cube_side / 2, -cube_side / 2, cube_side / 2);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(cube_side / 2, -cube_side / 2, -cube_side / 2);
	glVertex3f(cube_side / 2, cube_side / 2, -cube_side / 2);
	glVertex3f(cube_side / 2, cube_side / 2, cube_side / 2);
	glVertex3f(cube_side / 2, -cube_side / 2, cube_side / 2);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-cube_side / 2, -cube_side / 2, cube_side / 2);
	glVertex3f(-cube_side / 2, cube_side / 2, cube_side / 2);
	glVertex3f(-cube_side / 2, cube_side / 2, -cube_side / 2);
	glVertex3f(-cube_side / 2, -cube_side / 2, -cube_side / 2);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(cube_side / 2, cube_side / 2, cube_side / 2);
	glVertex3f(cube_side / 2, cube_side / 2, -cube_side / 2);
	glVertex3f(-cube_side / 2, cube_side / 2, -cube_side / 2);
	glVertex3f(-cube_side / 2, cube_side / 2, cube_side / 2);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(cube_side / 2, -cube_side / 2, -cube_side / 2);
	glVertex3f(cube_side / 2, -cube_side / 2, cube_side / 2);
	glVertex3f(-cube_side / 2, -cube_side / 2, cube_side / 2);
	glVertex3f(-cube_side / 2, -cube_side / 2, -cube_side / 2);
	glEnd();

	glLoadIdentity();

	// SPHERE
	glScalef(0.5, 0.5, 0.5);
	glColor3f(1.0, 1.0, 1.0);

	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GLUquadricObj *quadObj;
	quadObj = gluNewQuadric();
	gluSphere(quadObj, radius, 30, 30);


	glFlush();
	glutSwapBuffers();

}

// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys(int key, int x, int y) {

	//  Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	//  Request display update
	glutPostRedisplay();

}

//----------------------------------------------------------
//main() function
//----------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Cube and sphere");

	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	// Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	// Pass control to GLUT for events
	glutMainLoop();

}