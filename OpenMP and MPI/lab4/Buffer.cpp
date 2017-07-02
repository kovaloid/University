#include "Buffer.h"
#include <stdio.h>

Buffer::Buffer(int number, int numSoR)
{
	//Инициализация массива
	requests = new Request*[number];
	for(int i=0; i<number; i++)
		requests[i] = NULL;

	deniedRequests_= new int[numSoR];
	for(int i=0; i<numSoR; i++)
		deniedRequests_[i]=0;

	//Инициализация переменных
	isEmpty_=true;
	pointerIN_ = 0;
	pointerOUT_ = 0;
	requestsInBuffer_=0;
	number_=number;
};

void Buffer::putIn(Request* req)
{
	if(requestsInBuffer_<number_)	//В буфере есть место
	{
		int pointerEND = pointerIN_;

		do
		{
			if(requests[pointerIN_] == NULL)	
			{
				requests[pointerIN_] = req;				//нашли место и кладём заявку в буффер
				++requestsInBuffer_;
				if(++pointerIN_ == number_)				//ищем место
					pointerIN_=0;
				isEmpty_=false;
				return;
			}
			else
			{
				if(++pointerIN_ == number_)				//ищем место
					pointerIN_=0;
			}
		} while(pointerEND!=pointerIN_);				
	}
	else	//В буфере нет места
	{
		
		double minTime = requests[0]->getCreateTime();
		int num = 0;

		//Вычисляем какую заявку в отказ
		for(int i=1; i<number_; i++)
		{
			if(requests[i]->getCreateTime() < minTime)
			{
				minTime = requests[i]->getCreateTime();
				num = i;
			}
		}

		//В отказ
		++deniedRequests_[requests[num]->getType()-1];
		delete requests[num];
		requests[num]=req;
		if(++pointerIN_ >= number_)
			pointerIN_=0;
		//printf("---В отказ (из буффера %d)\n", num+1);

	}
};

Request* Buffer::takeFrom()
{
	--requestsInBuffer_;
	if(requestsInBuffer_ == 0)
		isEmpty_=true;

	int pointerEND = pointerOUT_;

	do
	{
		if(requests[pointerOUT_] != NULL)	
		{
			Request* tempReq = requests[pointerOUT_];
			requests[pointerOUT_] = NULL;
			if(++pointerOUT_ >= number_)
				pointerOUT_=0;
	
			return tempReq;
		}
		else
		{
			if(++pointerOUT_ >= number_)				
				pointerOUT_=0;
		}
	} while(pointerEND!=pointerOUT_);	
};

void Buffer::printValues()
{
	for(int i=0; i<number_; i++)
	{
		if(requests[i] != NULL)
			printf("Буффер %d\t%f\t%d:%d\n", i+1, requests[i]->getCreateTime(), requests[i]->getType(), requests[i]->getSerialNumber());
		else
			printf("Буффер %d\t--------\n", i+1);
	}
	printf("Указатель ЗАПИСИ = %d\nУказатель ВЫБОРКИ= %d\n", pointerIN_+1, pointerOUT_+1);
	printf("В отказе: %d\n", deniedRequests_);
};

bool Buffer::getIsEmpty()
{
	return isEmpty_;
};

int* Buffer::getDeniedRequests()
{
	return deniedRequests_;
};
