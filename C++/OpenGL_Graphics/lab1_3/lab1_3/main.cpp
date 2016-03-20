#include <GL\glut.h>
#include <GL\glaux.h>
#include <windows.h>
#include <math.h>



const int disk_size = 64;
const int conus_size = 190;
const int cylinder_size = 253;

float disk1[disk_size][3];
float disk2[disk_size][3];
float disk3[disk_size][3];
float conus[conus_size][3];
float cylinder[cylinder_size][3];


float common_radius = 0.3;
float common_height = 0.5;

float lambda = 0.01;
//float lambdainc = 0.002;



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



void draw_disk(float disk[disk_size][3], float radius, float height) {

	float angle = 0.0;
	float pi = 3.14;
	float x, y, z;
	int i = 0;

	while (angle < 2 * pi + 0.1) {
		x = radius * sin(angle);
		y = radius * cos(angle);
		z = height;
		angle = angle + 0.1;
		disk[i][0] = x;
		disk[i][1] = y;
		disk[i][2] = z;
		i++;
	}

}



void draw_conus(float conus[conus_size][3], float radius, float baseheight, float topheight) {
	float point[3] = { 0.0, 0.0, topheight };
	int i = 0, j = 0;
	float conus_disk[disk_size][3];
	draw_disk(conus_disk, radius, baseheight);

	while (i < conus_size) {

		for (int n = 0; n < 3; n++) {
			conus[i][n] = conus_disk[j][n];
			conus[i + 1][n] = conus_disk[j + 1][n];
			conus[i + 2][n] = point[n];
		}

		j = j + 1;
		i = i + 3;

	}

}

void draw_cylinder(float cylinder[cylinder_size][3], float radius, float baseheight, float topheight) {

	int i = 0, j = 0;
	float cylinder_disk_base[disk_size][3];
	float cylinder_disk_top[disk_size][3];
	draw_disk(cylinder_disk_base, radius, baseheight);
	draw_disk(cylinder_disk_top, radius, topheight);

	while (i < cylinder_size) {
		for (int n = 0; n < 3; n++) {
			cylinder[i][n] = cylinder_disk_base[j][n];
			cylinder[i + 1][n] = cylinder_disk_base[j + 1][n];
		}
		i = i + 4;
		j++;
	}


	i = 2, j = 0;
	while (i < cylinder_size) {
		for (int n = 0; n < 3; n++) {
			cylinder[i][n] = cylinder_disk_top[j + 1][n];
			cylinder[i + 1][n] = cylinder_disk_top[j][n];
		}
		i = i + 4;
		j++;
	}

}


void init() {
	draw_disk(disk1, common_radius, 0.0);
	draw_disk(disk2, common_radius, -common_height);
	draw_disk(disk3, common_radius, common_height);
	draw_conus(conus, common_radius, -common_height, 0.0);
	draw_cylinder(cylinder, common_radius, 0.0, common_height);
}




// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){

	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	glRotatef(-70, 1.0, 0.0, 0.0);
	glRotatef(40, 0.0, 1.0, 0.0);


	// animation init:
	//lambda = lambda + lambdainc;

	// bounds:
	//if (lambda >= 1 || lambda <= 0){
	//	lambdainc = -lambdainc;
	//}




	float point[3] = { 0.0, 0.0, 0.0 };

	for (int i = 0; i < disk_size; i++){

		disk1[i][0] = (1 - lambda) * disk1[i][0] + lambda * disk2[i][0];             // 0
		disk1[i][1] = (1 - lambda) * disk1[i][1] + lambda * disk2[i][1];             // 1
		disk1[i][2] = (1 - lambda) * disk1[i][2] + lambda * disk2[i][2];             // 2


		disk3[i][0] = (1 - lambda) * disk3[i][0] + lambda * point[0];             // 0
		disk3[i][1] = (1 - lambda) * disk3[i][1] + lambda * point[1];             // 1
		disk3[i][2] = (1 - lambda) * disk3[i][2] + lambda * point[2];             // 2

	}

	int i = 0;
	int j = 0;
	while (i < cylinder_size) {

		cylinder[i][0] = (1 - lambda) * cylinder[i][0] + lambda * conus[j][0];             // 0
		cylinder[i][1] = (1 - lambda) * cylinder[i][1] + lambda * conus[j][1];             // 1
		cylinder[i][2] = (1 - lambda) * cylinder[i][2] + lambda * conus[j][2];             // 2


		cylinder[i + 1][0] = (1 - lambda) * cylinder[i + 1][0] + lambda * conus[j + 1][0];             // 0
		cylinder[i + 1][1] = (1 - lambda) * cylinder[i + 1][1] + lambda * conus[j + 1][1];             // 1
		cylinder[i + 1][2] = (1 - lambda) * cylinder[i + 1][2] + lambda * conus[j + 1][2];             // 2
		i = i + 4;
		j = j + 3;
	}


	i = 2;
	j = 2;
	while (i < cylinder_size + 2) {
		cylinder[i][0] = (1 - lambda) * cylinder[i][0] + lambda * conus[j][0];             // 0
		cylinder[i][1] = (1 - lambda) * cylinder[i][1] + lambda * conus[j][1];             // 1
		cylinder[i][2] = (1 - lambda) * cylinder[i][2] + lambda * conus[j][2];             // 2


		cylinder[i + 1][0] = (1 - lambda) * cylinder[i + 1][0] + lambda * conus[j][0];             // 0
		cylinder[i + 1][1] = (1 - lambda) * cylinder[i + 1][1] + lambda * conus[j][1];             // 1
		cylinder[i + 1][2] = (1 - lambda) * cylinder[i + 1][2] + lambda * conus[j][2];             // 2
		i = i + 4;
		j = j + 3;
	}




	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	for (int i = 0; i < disk_size; i++){
		glVertex3fv(disk1[i]);
	}
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	for (int i = 0; i < disk_size; i++){
		glVertex3fv(disk2[i]);
	}
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	for (int i = 0; i < disk_size; i++){
		glVertex3fv(disk3[i]);
	}
	glEnd();





	/*glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < conus_size; i++){
		glVertex3fv(conus[i]);
	}
	glEnd();*/

	glColor3f(1.0, 0.0, 0.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, conus);
	glDrawArrays(GL_TRIANGLES, 0, conus_size);


	/*glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < cylinder_size; i++){
		glVertex3fv(cylinder[i]);
	}
	glEnd();*/


	glColor3f(1.0, 0.0, 0.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cylinder);
	glDrawArrays(GL_QUADS, 0, cylinder_size);



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

void timer(int i){
	// keeps calling display every 30 milliseconds
	//display();
	display();
	glutTimerFunc(30, timer, 0);
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
	glutCreateWindow("Morphing");

	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	init();

	// Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	timer(0);

	// Pass control to GLUT for events
	glutMainLoop();

}