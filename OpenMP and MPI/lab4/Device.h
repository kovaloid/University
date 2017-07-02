#ifndef DEVICE_H
#define DEVICE_H

#include "Request.h"

class Device
{
private:
	Request* request;
	long double releaseTime_;
	long double emptyTime_;
	bool isEmpty_;

	int requestsProcessed_;
	double occupationKoef_;

	int type_;
	double lambda_;

public:
	Device();
	Device(int type, double lambda);

	void setLambda(double lam);
	double generateTime();
	void putIn(Request* req);
	Request* releaseRequest();

	double getReleaseTime();
	int getRequestsProcessed();
	int getRequestsType();
	int getRequestsSerialNumber();
	double getOccupationKoef();
	bool getIsEmpty();
};

#endif