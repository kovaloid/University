#include "DeviceController.h"
#include <cstdio>


DeviceController::DeviceController(int number, double lambda)
{
	//Инициализация массива
	devices = new Device[number]; 
	//for(int i=0; i<number; i++)
	//	devices[i] = Device(i+1, lambda);

	devices[0] = Device(1, 3.0);
	devices[1] = Device(2, 3.0);
	devices[2] = Device(3, 3.0);
	devices[3] = Device(4, 2.0);

	//Инициализация переменных
	number_=number;
	minTime_=0;
	devWithMinTime_=0;
	hasIdle_=true;
	numOfIdleDevs_=number;
};

void DeviceController::putIn(Request* req)
{
	for(int i=0; i<number_; i++)
	{
		if(devices[i].getIsEmpty())
		{
			devices[i].putIn(req);
			break;
		}
	}
	--numOfIdleDevs_;
};

Request* DeviceController::releaseDevice()
{
	++numOfIdleDevs_;
	return devices[devWithMinTime_].releaseRequest();
};

void DeviceController::printValues()
{
	for(int i=0; i<number_; i++)
	{
		if(!devices[i].getIsEmpty())
			printf("Прибор %d\t%f\t%d:%d\n", i+1, devices[i].getReleaseTime(), devices[i].getRequestsType(), devices[i].getRequestsSerialNumber());
		else
			printf("Прибор %d\t--------\n", i+1);
	}
};

void DeviceController::printTable(std::ofstream& f)
{
	printf("Таблица статистики приборов\n\n");
	printf(		"№   K занятости\n");
	for(int i=0; i<number_; i++)
	{
		printf(	"%-2d  %5.4f\n", i+1, devices[i].getOccupationKoef());
	}

	//Запись в файл
	f << "Таблица статистики приборов\n\n";
	f << "№   K занятости\n";
	for(int i=0; i<number_; i++)
	{
		f <<  i+1 << "    " << devices[i].getOccupationKoef() << std::endl;
	}
};


double DeviceController::getMinTime()
{
	minTime_ = 0;
	devWithMinTime_=0;

	for(int i=0; i<number_; i++)
	{
		if(!devices[i].getIsEmpty())
		{
			minTime_ = devices[i].getReleaseTime();
			devWithMinTime_=i;
			break;
		}
	}
	
	for(int i=0; i<number_; i++)
	{
		if(devices[i].getReleaseTime() < minTime_ && !devices[i].getIsEmpty())
		{
			devWithMinTime_=i;
			minTime_=devices[i].getReleaseTime();
		}
	}

	return minTime_;
};

bool DeviceController::getHasIdle()
{
	if(numOfIdleDevs_>0)
		return true;
	else
		return false;
}

bool DeviceController::areAllEmpty()
{
	for(int i=0; i<number_; i++)
	{
		if(devices[i].getIsEmpty() == false)
			return false;
	}
	return true;
};

int DeviceController::getDevWithMinTime()
{
	return devWithMinTime_;
};