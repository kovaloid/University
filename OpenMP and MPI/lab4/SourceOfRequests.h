#ifndef SOURCE_H
#define SOURCE_H

#include <string>
#include "Request.h"

class SourceOfRequests
{
private:
	Request *request_;
	double nextRequestTime_;

	int requestsGenerated_;
	int requestsDenied_;
	double probabilityOfDenial_;
	double timeInServiceALL_;
	double timeInServiceAVG_;
	double timeInBufferALL_;
	double timeInBufferAVG_;
	double timeInSystemALL_;
	double timeInSystemAVG_;

	int type_;
	double lambda_;

public:

	SourceOfRequests(); //�����������
	SourceOfRequests(int type, double lambda); //�����������

	void setLambda(double lam);
	void generateNextRequest(); //��������� ������� ��������� ������
	void plusStatisticTimes(double tServ, double tBuff, double tInSys);
	void calculateStatistic();
	void setRequestsDenied(int deniedR);

	double getNextRequestTime(); //���������� ����� ��������� ������
	int getRequestsGenerated();
	Request* getRequest();		//���������� ��������� �� ������
	int getRequestsDenied();
	double getProbabilityOfDenial();
	double getTimeInServiceAVG();
	double getTimeInBufferAVG();
	double getTimeInSystemALL();

};
#endif //SOURCE_H
