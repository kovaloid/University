#ifndef REQUEST_H
#define REQUEST_H

class Request
{
private:
	int type_;
	int serialNumber_;
	double createTime_;
	double endTime_;
	double intoDeviceTime_;
	
public:
	Request();
	Request(int type, double lambda, int serNum, double prevTime);

	void setIntoDeviceTime(double t);
	void setEndTime(double t);

	double getCreateTime();
	double getIntoDeviceTime();
	double getEndTime();
	int getType();
	int getSerialNumber();
};
#endif //REQUEST_H