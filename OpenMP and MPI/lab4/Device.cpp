#include "Device.h"
#include <stdio.h>
#include <cstdlib>
#include <cmath>

Device::Device()
{
};

Device::Device(int type, double lambda)
{
	//Инициализация переменных
	request = NULL;
	releaseTime_ = 0;
	emptyTime_ = 0;
	type_ = type;
	lambda_=lambda;
	isEmpty_ = true;
	requestsProcessed_=0;
	occupationKoef_=0;
};

void Device::setLambda(double lam)
{
	lambda_=lam;
};

double Device::generateTime()
{
	return (-1) / lambda_ * log(((double) rand()+0.0000000000001) / RAND_MAX);
};

void Device::putIn(Request* req)
{
	isEmpty_=false;
	request=req;
	if(req->getCreateTime() > releaseTime_)
	{
		request->setIntoDeviceTime(req->getCreateTime());
		emptyTime_+= req->getCreateTime() - releaseTime_;
		releaseTime_ = req->getCreateTime() + generateTime();
	}
	else
	{
		request->setIntoDeviceTime(releaseTime_);
		releaseTime_ += generateTime(); 
	}
	request->setEndTime(releaseTime_);
};

Request* Device::releaseRequest()
{
	++requestsProcessed_;
	isEmpty_=true;
	Request* tempR = request;
	request = NULL;
	return tempR;		
};


/*********/
/*Getters*/
/*********/
double Device::getReleaseTime()
{
	return releaseTime_;
};

bool Device::getIsEmpty()
{
	return isEmpty_;
};

int Device::getRequestsProcessed()
{
	return requestsProcessed_;
};

int Device::getRequestsType()
{
	return request->getType();
};

int Device::getRequestsSerialNumber()
{
	return request->getSerialNumber();
};

double Device::getOccupationKoef()
{
	//printf("\n[relTime = %f]\n[empTime = %f]\n", releaseTime_, emptyTime_);	
	occupationKoef_ = (releaseTime_ - emptyTime_) / releaseTime_;
	return occupationKoef_;
};
