#include "Request.h"
#include <cstdlib>
#include <stdio.h>
#include <cmath>

int fact(int k)
{
	int ans=1;
	for(int i=2; i<=k; i++)
		ans*=i;
	return ans;
};

Request::Request()
{
};

Request::Request(int type, double lambda, int serNum, double prevTime)
{
	//Инициализация переменных
	type_ = type;
	createTime_ = prevTime + pow(rand()/(double)RAND_MAX, lambda)*exp(-rand()/(double)RAND_MAX)/fact(lambda);
	endTime_ = 0;
	intoDeviceTime_=0;
	serialNumber_=serNum;	
};



/*********/
/*Setters*/
/*********/
void Request::setIntoDeviceTime(double t)
{
	intoDeviceTime_=t;
};

void Request::setEndTime(double t)
{
	endTime_=t;
};



/*********/
/*Getters*/
/*********/
double Request::getCreateTime()
{
	return createTime_;
};

int Request::getType()
{
	return type_;
};

int Request::getSerialNumber()
{
	return serialNumber_;
};

double Request::getIntoDeviceTime()
{
	return intoDeviceTime_;
};

double Request::getEndTime()
{
	return endTime_;
};

