/*
Написать программу, которая использует ожидаемый таймер (WaitableTimer), чтобы остановить 
себя через К секунд после старта, где К параметр командной строки.
*/

#include <windows.h>
#include <stdio.h>
#include <conio.h>

#define _SECOND 10000000

int main()
{
	int k = 0;
	HANDLE wTimer;
	__int64 endTime;
	LARGE_INTEGER quitTime;
	SYSTEMTIME now;

	printf("Enter number of seconds: ");
	scanf("%d", &k);
	wTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	endTime = -1 * k * _SECOND;
	quitTime.LowPart = (DWORD)(endTime & 0xFFFFFFFF);
	quitTime.HighPart = (LONG)(endTime >> 32);
	SetWaitableTimer(wTimer, &quitTime, 0, NULL, NULL, FALSE);
	GetSystemTime(&now);
	printf("System Time %d:%d:%d\n", now.wHour, now.wMinute, now.wSecond);
	printf(" - Start waiting\n");
	WaitForSingleObject(wTimer, INFINITE);
	printf(" - Stop waiting\n");
	GetSystemTime(&now);
	printf("System Time %d:%d:%d\n", now.wHour, now.wMinute, now.wSecond);
	printf("Press enter to exit...\n");

	CloseHandle(wTimer);
	_getch();

	return 0;
}