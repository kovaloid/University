#include "Room.h"
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

struct Coords{
	float x, y, z;
	float nx, ny, nz;
};


Room::Room(int listId){
	_listId = listId;

	R = SIDE_2 / cos(M_PI_4);

	_materialAmbient = new float[3] { 0.2f, 0.2f, 0.2f };
	_materialDiffuse = new float[3] { 1.0f, 1.0f, 1.0f };
	_materialSpecular = new float[3] { 0, 0, 0};
	_shininess = 0.1 * 128;

	_coords = new double[3] {0, 0, 0};

	Coords cub[8];

	float alpha = M_PI_4;
	for (int i = 0; i < 4; i++){
		cub[i].x = R * cos(alpha);
		cub[i].y = -SIDE_2;
		cub[i].z = R * sin(alpha);
		alpha -= M_PI_2;
	}

	alpha = M_PI_4;
	for (int i = 4; i < 8; i++){
		cub[i].x = R * cos(alpha);
		cub[i].y = SIDE_2;
		cub[i].z = R * sin(alpha);
		alpha -= M_PI_2;
	}

	for (int i = 0; i < 8; i++){
		int len = sqrt(cub[i].x * cub[i].x + cub[i].y * cub[i].y + cub[i].z * cub[i].z);
		cub[i].nx = cub[i].x / len;
		cub[i].ny = cub[i].y / len;
		cub[i].nz = cub[i].z / len;
	}

	
	displayArr = new float[3 * 4 * 5];
	textureArr = new float[2 * 4 * 5];
	normalsArr = new float[3 * 4 * 5];
	for (int i = 0; i < 3; i++){
		int j = 12 * i;
		int tOffset = 8 * i;

		displayArr[j] = cub[i].x;
		displayArr[j + 1] = cub[i].y;
		displayArr[j + 2] = cub[i].z;
		textureArr[tOffset] = 1;
		textureArr[tOffset + 1] = 0;

		displayArr[j + 3] = cub[i + 1].x;
		displayArr[j + 4] = cub[i + 1].y;
		displayArr[j + 5] = cub[i + 1].z;
		textureArr[tOffset + 2] = 0;
		textureArr[tOffset + 3] = 0;

		displayArr[j + 6] = cub[4 + i + 1].x;
		displayArr[j + 7] = cub[4 + i + 1].y;
		displayArr[j + 8] = cub[4 + i + 1].z;
		textureArr[tOffset + 4] = 0;
		textureArr[tOffset + 5] = 1;

		displayArr[j + 9] = cub[4 + i].x;
		displayArr[j + 10] = cub[4 + i].y;
		displayArr[j + 11] = cub[4 + i].z;
		textureArr[tOffset + 6] = 1;
		textureArr[tOffset + 7] = 1;
	}

	int off = 3 * 4 * 3;
	int tOffset = 2 * 4 * 3;

	//up
	displayArr[off] = cub[4].x;
	displayArr[off + 1] = cub[4].y;
	displayArr[off + 2] = cub[4].z;
	textureArr[tOffset] = 1;
	textureArr[tOffset + 1] = 0;
	normalsArr[off] = cub[4].nx;
	normalsArr[off + 1] = cub[4].ny;
	normalsArr[off + 2] = cub[4].nz;

	displayArr[off + 3] = cub[5].x;
	displayArr[off + 4] = cub[5].y;
	displayArr[off + 5] = cub[5].z;
	textureArr[tOffset + 2] = 0;
	textureArr[tOffset + 3] = 0;
	normalsArr[off + 3] = cub[5].nx;
	normalsArr[off + 4] = cub[5].ny;
	normalsArr[off + 5] = cub[5].nz;

	displayArr[off + 6] = cub[6].x;
	displayArr[off + 7] = cub[6].y;
	displayArr[off + 8] = cub[6].z;
	textureArr[tOffset + 4] = 0;
	textureArr[tOffset + 5] = 1;
	normalsArr[off + 6] = cub[6].nx;
	normalsArr[off + 7] = cub[6].ny;
	normalsArr[off + 8] = cub[6].nz;

	displayArr[off + 9] = cub[7].x;
	displayArr[off + 10] = cub[7].y;
	displayArr[off + 11] = cub[7].z;
	textureArr[tOffset + 6] = 1;
	textureArr[tOffset + 7] = 1;
	normalsArr[off + 9] = cub[7].nx;
	normalsArr[off + 10] = cub[7].ny;
	normalsArr[off + 11] = cub[7].nz;

	//down
	off += 12;
	tOffset += 8;
	displayArr[off] = cub[0].x;
	displayArr[off + 1] = cub[0].y;
	displayArr[off + 2] = cub[0].z;
	textureArr[tOffset] = 1;
	textureArr[tOffset + 1] = 0;
	normalsArr[off] = cub[0].nx;
	normalsArr[off + 1] = cub[0].ny;
	normalsArr[off + 2] = cub[0].nz;

	displayArr[off + 3] = cub[1].x;
	displayArr[off + 4] = cub[1].y;
	displayArr[off + 5] = cub[1].z;
	textureArr[tOffset + 2] = 0;
	textureArr[tOffset + 3] = 0;
	normalsArr[off + 3] = cub[1].nx;
	normalsArr[off + 4] = cub[1].ny;
	normalsArr[off + 5] = cub[1].nz;

	displayArr[off + 6] = cub[2].x;
	displayArr[off + 7] = cub[2].y;
	displayArr[off + 8] = cub[2].z;
	textureArr[tOffset + 4] = 0;
	textureArr[tOffset + 5] = 1;
	normalsArr[off + 6] = cub[2].nx;
	normalsArr[off + 7] = cub[2].ny;
	normalsArr[off + 8] = cub[2].nz;

	displayArr[off + 9] = cub[3].x;
	displayArr[off + 10] = cub[3].y;
	displayArr[off + 11] = cub[3].z;
	textureArr[tOffset + 6] = 1;
	textureArr[tOffset + 7] = 1;
	normalsArr[off + 9] = cub[3].nx;
	normalsArr[off + 10] = cub[3].ny;
	normalsArr[off + 11] = cub[3].nz;


	//Normals
	for (int i = 0; i < 3 * 4 * 5; i++)
	{
		normalsArr[i] = 0;
		
	}

	for (int i = 0; i < 4; i++)
	{
		int j = 3 * i;
		normalsArr[j] = -1;
		normalsArr[14 + j] = 1;
		normalsArr[24 + j] = 1;
		normalsArr[37 + j] = -1;
		normalsArr[49 + j] = 1;
	}

	glNewList(_listId, GL_COMPILE);
	justDisplay(false);
	glEndList();

}

void Room::display1(){
	glPushMatrix();
	glCallList(_listId);
	glPopMatrix();
}

void Room::display(bool textured){

	/* Определение свойств материала */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _materialAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _materialDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _materialSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shininess);

	glPushMatrix();
	glCallList(_listId);
	glPopMatrix();

	
	
}

void Room::justDisplay(bool textured){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	if (textured)
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPushMatrix();
	glTranslatef(_coords[0], _coords[1], _coords[2]);
	glVertexPointer(3, GL_FLOAT, 0, displayArr);
	glNormalPointer(GL_FLOAT, 0, normalsArr);
	if (textured)
		glTexCoordPointer(2, GL_FLOAT, 0, textureArr);
	glDrawArrays(GL_QUADS, 0, 20);
	glPopMatrix();

	if (textured)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}


float* Room::getNormal(int plane){
	int n = plane * 3 * 4;
	float* coefficients = new float[] {normalsArr[n], normalsArr[n+1], 
		normalsArr[n + 2], (float)SIDE_2 - 0.001f};
	
	return coefficients;
}