#include "SourceOfRequests.h"
#include "Request.h"
#include <cmath>

SourceOfRequests::SourceOfRequests()
{
};

SourceOfRequests::SourceOfRequests(int type, double lambda)
{
	nextRequestTime_ = 0;

	requestsGenerated_=0;
	requestsDenied_=0;
	probabilityOfDenial_=0;
	timeInServiceALL_=0;
	timeInServiceAVG_=0;
	timeInBufferALL_=0;
	timeInBufferAVG_=0;
	timeInSystemALL_=0;

	lambda_ = lambda;
	type_ = type;

	generateNextRequest();
};

void SourceOfRequests::setLambda(double lam)
{
	lambda_=lam;
};

void SourceOfRequests::generateNextRequest()
{
	++requestsGenerated_;
	request_ = new Request(type_, lambda_, requestsGenerated_, nextRequestTime_);
	nextRequestTime_ = request_->getCreateTime();
};

void SourceOfRequests::plusStatisticTimes(double tServ, double tBuff, double tInSys)
{
	timeInServiceALL_ += tServ;
	timeInBufferALL_ += tBuff;
	timeInSystemALL_ += tInSys;
};

void SourceOfRequests::calculateStatistic()
{
	probabilityOfDenial_ = (double) requestsDenied_ / (double) requestsGenerated_;
	timeInServiceAVG_ = timeInServiceALL_ / (double) (requestsGenerated_-requestsDenied_);
	timeInBufferAVG_ = timeInBufferALL_ / (double) requestsGenerated_;
	timeInSystemAVG_ = timeInSystemALL_ / (double) requestsGenerated_;
};

void SourceOfRequests::setRequestsDenied(int deniedR)
{
	requestsDenied_=deniedR;
};


/*********/
/*Getters*/
/*********/
double SourceOfRequests::getNextRequestTime()
{
	return nextRequestTime_;
}

Request* SourceOfRequests::getRequest()
{
	return request_;
};

int SourceOfRequests::getRequestsGenerated()
{
	return requestsGenerated_;
};

int SourceOfRequests::getRequestsDenied()
{
	return requestsDenied_;
};

double SourceOfRequests::getProbabilityOfDenial()
{
	return probabilityOfDenial_;
};

double SourceOfRequests::getTimeInServiceAVG()
{
	return timeInServiceAVG_;
};

double SourceOfRequests::getTimeInBufferAVG()
{
	return timeInBufferAVG_;
};

double SourceOfRequests::getTimeInSystemALL()
{
	return timeInSystemAVG_;
};