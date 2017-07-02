#ifndef BUFFER_H
#define BUFFER_H

#include "Request.h"

class Buffer
{
private:
	Request** requests;		//массив заявок
	int number_;
	int pointerIN_;			//указатель В (по кольцу)
	int pointerOUT_;		//указатель ИЗ (по кольцу)
	bool isEmpty_;			//буффер пуст
	int requestsInBuffer_;	//количество заявок в буффере
	int* deniedRequests_;	//количество заявок, ушедших в отказ

public:
	Buffer(int number, int numSoR);	//коструктор
	void putIn(Request* req);		//положить в буффер
	Request* takeFrom();			//достать из буфера
	bool getIsEmpty();
	int* getDeniedRequests();
	void printValues();				//напечатать значения переменных
};

#endif //BUFFER_H