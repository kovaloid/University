#include <fstream>

#include "SourceOfRequestsController.h"

SourceOfRequestsController::SourceOfRequestsController(int number, double lambda)
{
	//Инициализация массива
	sourcesOfRequests = new SourceOfRequests[number];
	for(int i=0; i<number; i++)
		sourcesOfRequests[i] = SourceOfRequests(i+1, lambda);

	//Инициализация переменных
	number_=number;
	minTime_=0;
	sourceWithMinTime_=0;
};

void SourceOfRequestsController::giveForStatistic(Request* req)
{
	double tServ = req->getEndTime() - req->getIntoDeviceTime();
	double tBuff = req->getIntoDeviceTime() - req->getCreateTime();
	double tInSys = req->getEndTime() - req->getCreateTime();

	sourcesOfRequests[req->getType()-1].plusStatisticTimes(tServ, tBuff, tInSys);
};

void SourceOfRequestsController::setRequestsDenied(int* deniedReqs)
{
	for(int i=0; i<number_; i++)
		sourcesOfRequests[i].setRequestsDenied(deniedReqs[i]);
};


void SourceOfRequestsController::printValues()
{
	for(int i=0; i<number_; i++)
	{
		printf("Источник %d\t%f\t%d\n", i+1, sourcesOfRequests[i].getNextRequestTime(), sourcesOfRequests[i].getRequestsGenerated());
	}
};

void SourceOfRequestsController::printTable(std::ofstream& f)
{
	printf("Таблица статистики источников\n\n");
	printf(		"№   Заявок   Отказ   P(отк)   t обслуж   t буф    t общ\n");
	for(int i=0; i<number_; i++)
	{
		sourcesOfRequests[i].calculateStatistic();

		printf(	"%-2d  %-5d    %-5d   %-4.3f    %-7.3f    %-7.3f  %-7.3f\n", 
			i+1, 
			sourcesOfRequests[i].getRequestsGenerated(), 
			sourcesOfRequests[i].getRequestsDenied(),
			sourcesOfRequests[i].getProbabilityOfDenial(),
			sourcesOfRequests[i].getTimeInServiceAVG(),
			sourcesOfRequests[i].getTimeInBufferAVG(),
			sourcesOfRequests[i].getTimeInSystemALL()			
			);
	}

	double timeAll = 0;

	// Запись в файл
	f << "Таблица статистики источников\n\n";
	/*f << 		"№   Заявок   Отказ   P(отк)     t обслуж      t буф      t общ\n";
	for(int i=0; i<number_; i++)
	{
		f << i+1 << "   " <<
			sourcesOfRequests[i].getRequestsGenerated() << "      " <<
			sourcesOfRequests[i].getRequestsDenied() << "     " <<
			sourcesOfRequests[i].getProbabilityOfDenial() << "    " <<
			sourcesOfRequests[i].getTimeInServiceAVG() << "    " <<
			sourcesOfRequests[i].getTimeInBufferAVG() << "    " <<
			sourcesOfRequests[i].getTimeInSystemALL() << std::endl;
	}*/

	for(int i=0; i<number_; i++)
	{
		timeAll+=sourcesOfRequests[i].getTimeInSystemALL();
	}

	timeAll = timeAll / number_;

	f << "P    = " << getProbabilityOfDenialAll() << std::endl; 
	f << "Time = " << timeAll << std::endl;
};

double SourceOfRequestsController::getMinTime()
{
	minTime_ = sourcesOfRequests[0].getNextRequestTime();
	sourceWithMinTime_=0;
	for(int i=1; i<number_; i++)
	{
		if(sourcesOfRequests[i].getNextRequestTime() < minTime_)
		{
			sourceWithMinTime_=i;
			minTime_=sourcesOfRequests[i].getNextRequestTime();
		}
	}
	return minTime_;
}

Request* SourceOfRequestsController::getRequestWithMinTime()
{
	Request* tempR = sourcesOfRequests[sourceWithMinTime_].getRequest();
	sourcesOfRequests[sourceWithMinTime_].generateNextRequest();
	return tempR;
};

int SourceOfRequestsController::getSourceWithMinTime()
{
	return sourceWithMinTime_;
};

int SourceOfRequestsController::getTotalRequestsGenerated()
{
	int totalNum=0;
	for(int i=0; i<number_; i++)
		totalNum += sourcesOfRequests[i].getRequestsGenerated();
	return totalNum;
};

int SourceOfRequestsController::getTotalRequestsDenied()
{
	int totalNum=0;
	for(int i=0; i<number_; i++)
		totalNum += sourcesOfRequests[i].getRequestsDenied();
	return totalNum;
};

double SourceOfRequestsController::getProbabilityOfDenialAll()
{
	return (double) getTotalRequestsDenied() / (double) getTotalRequestsGenerated();
	
};
