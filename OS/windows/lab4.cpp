/*
В этой лабораторной вы должны создать два потока, которые выполняются в одном адресном пространстве (в одном процессе):
•	поток – производитель;
•	и поток – потребитель.
Целочисленный массив buf содержит производимые и потребляемые данные (данные совместного использования). Производитель 
просто устанавливает значение buf[0]=0, buf[1]=1 и т.д.
Код должен удовлетворять трем требованиям:
•	потребитель не должен пытаться извлечь значение из буфера, если буфер пуст;
•	производитель не должен пытаться поместить значение в буфер, если буфер полон;
•	состояние буфера должно описываться общими переменными (индексами, счетчиками, указателями связанных списков и т.д.).
*/

#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <vector>
#include <conio.h>

using namespace std;

#define N 5
#define _WIN32_WINNT 0x0400

vector<int> buf(N);
int index = -1;
int count = 0;
SECURITY_ATTRIBUTES sa;

DWORD WINAPI Producer(PVOID Param)
{
	printf("Producer start working!\n");
	Sleep(1000);
	HANDLE h[2];
	h[0] = OpenMutex(NULL,FALSE,NULL);
	h[1] = OpenSemaphore(FALSE,FALSE,NULL);
	HANDLE hE = OpenEvent(FALSE,FALSE,NULL);
	while(1)
	{
		WaitForMultipleObjects(2,h,TRUE,INFINITE);
		index++;
		if (index > (N-1))
			index = 0;
		buf[index] = count;
		printf("[producer] put a number: %d to index: %d\n",count,index);
		count++;
		SetEvent(hE);		
		ReleaseMutex(h[0]);
		Sleep(500);
	}
	return 0;
}

DWORD WINAPI Consumer(PVOID Param)
{
	printf("Consumer start working!\n");
	Sleep(1000);
	HANDLE h[2];
	h[0] = OpenMutex(FALSE,FALSE,NULL);
	h[1] = OpenEvent(FALSE,FALSE,NULL);
	HANDLE hS = OpenSemaphore(FALSE,FALSE,NULL);
	while (1)
	{
		WaitForMultipleObjects(2,h,TRUE,INFINITE);
		if (index == (N-1))
			printf("[consumer] get buffer [0] = %d  [1] = %d  [2] = %d  [3] = %d  [4] = %d\n", buf[0], buf[1], buf[2], buf[3], buf[4]);
		ReleaseSemaphore(hS,1,NULL);
		ReleaseMutex(h[0]);
		Sleep(500);
	}
	return 0;
}

int main() 
{
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);

	HANDLE hMutex = CreateMutex(&sa,FALSE,NULL);
	HANDLE hEvent = CreateEvent(&sa,TRUE,FALSE,NULL);
	HANDLE hSemaphore = CreateSemaphore(&sa,N,N,NULL);

	HANDLE hProducer = CreateThread(NULL,0,Producer,NULL,0,NULL);
	printf("The producer was created!\n");
	HANDLE hConsumer = CreateThread(NULL,0,Consumer,NULL,0,NULL);
	printf("The consumer was created!\n");

	Sleep(20000);
	_getch();
	CloseHandle(hProducer);
	CloseHandle(hConsumer);

	return 0;
}