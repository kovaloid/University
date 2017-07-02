#include <curses.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>

#include "SourceOfRequestsController.h"
#include "SourceOfRequests.h"
#include "DeviceController.h"
#include "Device.h"
#include "Buffer.h"
#include "Request.h"

#define NUMBER_OF_SOURCES 5		// 10		// 5		// 10		// 7
#define LAMBDA_OF_SOURCES 0.5	// 0.1		// 0.1		// 0.1		// 0.1
#define NUMBER_OF_DEVICES 4		// 4		// 2		// 5		// 4
#define LAMBDA_OF_DEVICES 3.5	// 4.5		// 4.5		// 3.5		// 3.0
#define BUFFER_SIZE 5			// 10		// 10		// 10		// 10

using namespace std;


int main(void)
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	bool endCMO = false;
	bool firstTime = true;
	bool autoMod = true;		//Режим пошаговый или автоматический
	int numberOfRequests = 50000000;
	int numberOfRequestsOLD = 0;
	double probabilityOfDenialOLD=0;
	double probabilityOfDenial=0;

	SourceOfRequestsController sorController(NUMBER_OF_SOURCES, LAMBDA_OF_SOURCES);
	DeviceController dController(NUMBER_OF_DEVICES, LAMBDA_OF_DEVICES);
	Buffer buffer(BUFFER_SIZE, NUMBER_OF_SOURCES);

	while(!endCMO)
	{
		if(!autoMod)
		{
			system("cls");
			//Печатаем значение (таблица результатов)
			printf("-Событие-\t-Время-\t\t-Заявок-\n");
			sorController.printValues();
			printf("\n");
			dController.printValues();
			printf("\n");
			buffer.printValues();
			printf("\n");
		}

		//Сгенерировалась заявка 
		if(sorController.getMinTime() < dController.getMinTime() || dController.areAllEmpty())
		{
			if(!autoMod)
				printf("-Источник %d следующий\n", sorController.getSourceWithMinTime()+1);
			//Если буффер пуст и есть свободный прибор
			if(buffer.getIsEmpty() && dController.getHasIdle())
			{
				if(!autoMod)
					printf("--Буффер пуст И есть свободный прибор\n");
				dController.putIn(sorController.getRequestWithMinTime()); //заявка из источника в прибор, новая заявка на приборе
			}
			//Если прибор занят, либо буффер не пуст
			else
			{
				if(!autoMod)
					printf("--Заявка в буффер\n");
				buffer.putIn(sorController.getRequestWithMinTime());
			}
		}
		//Прибор освободился (или одновременно) ГОТОВО
		else
		{
			if(!autoMod)
				printf("-Прибор %d закончил работать\n", dController.getDevWithMinTime()+1);
			Request* tempR = dController.releaseDevice();
			sorController.giveForStatistic(tempR);
			delete tempR;
	
			if(!buffer.getIsEmpty())
			{
				if(!autoMod)
					printf("-Прибор берёт заявку и буфера\n");
				dController.putIn(buffer.takeFrom());
			}
		}

		if(!autoMod){
			printf("\n-----------------------------------------\n");
			getch();
		}

		if(sorController.getTotalRequestsGenerated() > numberOfRequests)
		{
			sorController.setRequestsDenied(buffer.getDeniedRequests());
			probabilityOfDenial = sorController.getProbabilityOfDenialAll();
			printf("Probability of denial = %f\n", probabilityOfDenial);
			numberOfRequestsOLD = numberOfRequests;
			if(firstTime)
			{
				probabilityOfDenialOLD=probabilityOfDenial;
				firstTime = false;
				numberOfRequests = pow(1.643, 2)*(1 - sorController.getProbabilityOfDenialAll()) / (sorController.getProbabilityOfDenialAll() * 0.01);
				printf("Number of requests for next cycle = %d\n", numberOfRequests);

				sorController = SourceOfRequestsController(NUMBER_OF_SOURCES, LAMBDA_OF_SOURCES);
				dController = DeviceController(NUMBER_OF_DEVICES, LAMBDA_OF_DEVICES);
				buffer = Buffer(BUFFER_SIZE, NUMBER_OF_SOURCES);
			}
			else
			{
				if(abs(probabilityOfDenial - probabilityOfDenialOLD) < 0.1)
				{
					endCMO = true;
					printf("error = %f\n\n", abs(probabilityOfDenial - probabilityOfDenialOLD));
				}
				else
				{
					probabilityOfDenialOLD=probabilityOfDenial;
					numberOfRequests = pow(1.643, 2)*(1 - sorController.getProbabilityOfDenialAll()) / (sorController.getProbabilityOfDenialAll() * 0.01);
					printf("Number of requests for next cycle = %d\n", numberOfRequests);

					sorController = SourceOfRequestsController(NUMBER_OF_SOURCES, LAMBDA_OF_SOURCES);
					dController = DeviceController(NUMBER_OF_DEVICES, LAMBDA_OF_DEVICES);
					buffer = Buffer(BUFFER_SIZE, NUMBER_OF_SOURCES);
				}
			}
		}
	}
	sorController.setRequestsDenied(buffer.getDeniedRequests());

	ofstream resFile;			// Файл для результатов.
	resFile.open("result.txt");
	resFile << "--------------------------------------------\n";

	resFile <<	"NUMBER_OF_SOURCES = " << NUMBER_OF_SOURCES << endl <<
				"LAMBDA_OF_SOURCES = " << LAMBDA_OF_SOURCES << endl <<
				"NUMBER_OF_DEVICES = " << NUMBER_OF_DEVICES << endl <<
				"LAMBDA_OF_DEVICES = " << LAMBDA_OF_DEVICES << endl <<
				"BUFFER_SIZE = " << BUFFER_SIZE << endl << endl;

	//system("cls");
	sorController.printTable(resFile);
	printf("\n\n");
	resFile << "\n\n";
	dController.printTable(resFile);

	resFile << "--------------------------------------------\n";
	resFile.close();

	getch();
}
