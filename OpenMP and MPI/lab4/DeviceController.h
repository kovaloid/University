#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <fstream>

#include "Device.h"
#include "Request.h"

class DeviceController
{
private:
	Device* devices;
	int number_;

	double minTime_;
	int devWithMinTime_;
	bool hasIdle_;
	int numOfIdleDevs_;

public:
	DeviceController();
	DeviceController(int number, double lambda);
	
	void printValues();
	void printTable(std::ofstream& f);

	double getMinTime();
	bool getHasIdle();
	int getDevWithMinTime();

	bool areAllEmpty();
	void putIn(Request* req);
	Request* releaseDevice();
};

#endif //DEVICECONTROLLER_H