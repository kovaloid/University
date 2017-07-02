#ifndef SOURCECONTROLLER_H
#define SOURCECONTROLLER_H

#include <fstream>

#include "SourceOfRequests.h"

class SourceOfRequestsController
{
private:
	SourceOfRequests* sourcesOfRequests;
	int number_;

	double minTime_;
	int sourceWithMinTime_;

public:
	SourceOfRequestsController(int number, double lambda);

	void giveForStatistic(Request* req);
	void setRequestsDenied(int* deniedReqs);

	void printValues();
	void printTable(std::ofstream& f);

	double getMinTime();
	Request* getRequestWithMinTime(); //возвращает заявку, создаёт новую
	int getSourceWithMinTime();
	int getTotalRequestsGenerated();
	int getTotalRequestsDenied();
	double getProbabilityOfDenialAll();
};

#endif