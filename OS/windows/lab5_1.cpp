/*
»спользовать любые синхронизационные объекты дл€ синхронизации нескольких (например, двух) потоков в одном процессе. 
¬ качестве раздел€емого ресурса использовать стандартный ввод/вывод.  аждый из потоков должен осуществл€ть прием строк 
от пользовател€ и отвечать пользователю (общатьс€ с пользователем). ѕричем возможность общени€ должна быть предоставлена 
только одному потоку. ѕередать возможность общени€, другому потоку нужно ввод€ next, а завершать поток, ввод€ exit. 
ќсновной (базовый) поток процесса должен закончить работу только в том случае, когда пользователь завершит работу всех 
вспомогательных потоков.
*/

#define _WIN32_WINNT 0x0400
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;

SECURITY_ATTRIBUTES sa;
HANDLE hS;

DWORD WINAPI ThreadFunc1(PVOID pArg)
{
	BOOL Exit = FALSE;
	char str[80];
	printf("Thread number 1 started!\n");
	Sleep(1000);
	while (!Exit)
	{
		WaitForSingleObject(hS,INFINITE);
		printf("Enter string for thread 1: \n");
		gets(str);
		while((strcmp(str,"next"))&&(strcmp(str,"exit")))
		{
			printf("Enter string for thread 1: \n");
			gets(str);
			if(!strcmp(str,"hello"))
				printf("Hello from thread 1!\n");
		}
		if(!strcmp(str,"exit"))	Exit=TRUE;
		printf("Thread number 1 switched to next thread!\n");
		SetEvent(hS);
	}
	printf("Thread 1 finished!\n");
	return 0;
}

DWORD WINAPI ThreadFunc2(PVOID pArg)
{
	BOOL Exit = FALSE;
	char str[80];
	printf("Thread number 2 started!\n");
	Sleep(1000);
	while (!Exit)
	{
		WaitForSingleObject(hS,INFINITE);
		printf("Enter string for thread 2: \n");
		gets(str);
		while((strcmp(str,"next"))&&(strcmp(str,"exit")))
		{
			printf("Enter string for thread 2: \n");
			gets(str);
			if(!strcmp(str,"hello"))
				printf("Hello from thread 2!\n");
		}
		if(!strcmp(str,"exit"))	Exit=TRUE;
		printf("Thread number 2 switched to next thread!\n");
		SetEvent(hS);
	}
	printf("Thread 2 finished!\n");
	return 0;
}

int main()
{
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	hS = CreateEvent(&sa,FALSE,FALSE,NULL);
	HANDLE hT[2];
	hT[0] = CreateThread(NULL,0,ThreadFunc1,NULL,NULL,NULL);
	hT[1] = CreateThread(NULL,0,ThreadFunc2,NULL,NULL,NULL);
	SetEvent(hS);
	WaitForMultipleObjects(2,hT,TRUE,INFINITE);
	CloseHandle(hT[0]);
	CloseHandle(hT[1]);
	CloseHandle(hS);
	_getch();
	return 0;
}