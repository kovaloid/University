#pragma once
class Molecula
{
	float radius = 0.3;

	float ALPHA = 0.4f;

	float* _materialAmbient;
	float* _materialDiffuse;
	float* _materialSpecular;
	float _shininess;

	float* _coords;

	int _listId;
	int _textureId;

	float _x_old1 = 0, _y_old1 = 0, _z_old1 = 0;
	float _x_old2 = 0, _y_old2 = 0, _z_old2 = 0;
	float _x_old3 = 0, _y_old3 = 0, _z_old3 = 0;
	float _x_old4 = 0, _y_old4 = 0, _z_old4 = 0;
	float _x_old5 = 0, _y_old5 = 0, _z_old5 = 0;

	float _x_start, _y_start, _z_start;
	float _x_dest, _y_dest, _z_dest;
	float _x_current, _y_current, _z_current;
	float _accel;
	float _speed;
	float _dtime = 1000000;

	bool flag = false;

	bool texFlag = false;

public:
	Molecula(int listId, int textureId);

	void display();
	void moveMolecula();
	void turnTextFlag();

};

