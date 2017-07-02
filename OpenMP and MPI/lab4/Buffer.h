#ifndef BUFFER_H
#define BUFFER_H

#include "Request.h"

class Buffer
{
private:
	Request** requests;		//������ ������
	int number_;
	int pointerIN_;			//��������� � (�� ������)
	int pointerOUT_;		//��������� �� (�� ������)
	bool isEmpty_;			//������ ����
	int requestsInBuffer_;	//���������� ������ � �������
	int* deniedRequests_;	//���������� ������, ������� � �����

public:
	Buffer(int number, int numSoR);	//����������
	void putIn(Request* req);		//�������� � ������
	Request* takeFrom();			//������� �� ������
	bool getIsEmpty();
	int* getDeniedRequests();
	void printValues();				//���������� �������� ����������
};

#endif //BUFFER_H