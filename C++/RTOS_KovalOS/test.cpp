/*******************************/
/*          test.cpp           */
/*******************************/

#include <stdio.h>
#include <stdlib.h>
#include <clocale>
#include <conio.h>
#include "sys.h"
#include "rtos_api.h"

DeclareTask(Task1,4);
DeclareTask(Task2,2);
DeclareTask(Task3,1);

DeclareTask(Task5,2);
DeclareTask(Task6,1);

DeclareTask(Task7,2);
DeclareTask(Task8,3);

DeclareTask(Task9,11);
DeclareTask(Task10,7);

DeclareSysEvent(1);
DeclareSysEvent(2);
DeclareSysEvent(3);

int main(void)
{
	setlocale(LC_CTYPE, "");

	printf("Hello!\n");

	InitRes(1,"Res1");
	InitRes(2,"Res2");

	printf("\nпереключение задач\n");
	StartOS(Task1,Task1prior,"Task1");
	ShutdownOS();
	printf("\n");

	printf("события\n");
	StartOS(Task7,Task7prior,"Task7");
	ShutdownOS();
	printf("\n");

	printf("блокировка ресурсов с повышением приоритета\n");
	StartOS(Task5,Task5prior,"Task5");
	ShutdownOS();
	printf("\n");

	printf("блокировка ресурсов deadlock\n");
	printf("для продолжения нажмите любую клавишу\n");
	getch();
	StartOS(Task9,Task9prior,"Task9");
	ShutdownOS();
	printf("\n");

	return 0;
}

//4
TASK(Task1)
{
	printf("Start Task1\n");
	ActivateTask(Task2,Task2prior,"Task2");
	printf("Task1\n");
	TerminateTask();
}

//2
TASK(Task2)
{
	printf("Start Task2\n");
	ActivateTask(Task3,Task3prior,"Task3");
	Dispatch();
	printf("Task2\n");
	TerminateTask();
}

//1
TASK(Task3)
{
	printf("Start Task3\n");
	Dispatch();
	printf("Task3\n");
	TerminateTask();
}

//-------------------------------------
// русурсы - блокировка ресурса задачей с меньшим приоритетом
//2
TASK(Task5)
{
	printf("Start Task5\n");
	InitRes(1,"Res1");
	PIP_GetRes(1);
	ActivateTask(Task6, Task6prior, "Task6");
	Dispatch();
	PIP_ReleaseRes(1);
	printf("Task5\n");
	TerminateTask();
}

//1
TASK(Task6)
{
	printf("Start Task6\n");
	PIP_GetRes(1);
	PIP_ReleaseRes(1);
	printf("Task6\n");
	TerminateTask();
}

//-------------------------------------
// ресурсы - deadlock
//11
TASK(Task9)
{
	printf("Start Task9\n");
	PIP_GetRes(1);
	ActivateTask(Task10, Task10prior, "Task10");
	Dispatch();
	PIP_GetRes(2);
	PIP_ReleaseRes(1);
	PIP_ReleaseRes(2);
	printf("Task9\n");
	TerminateTask();
}

//7
TASK(Task10)
{
	printf("Start Task10\n");
	PIP_GetRes(2);
	PIP_GetRes(1);
	PIP_ReleaseRes(1);
	PIP_ReleaseRes(2);
	printf("Task10\n");
	TerminateTask();
}

//-------------------------------------
// работа с событиями
//2
int Task7_ID;
TASK(Task7)
{
	printf("Start Task7\n");
	Task7_ID = RunningTask;
	ActivateTask(Task8,Task8prior,"Task8");
	WaitSysEvent(Event_1);
	TEventMask evnt;
	GetSysEvent(&evnt);
	printf("GetEvent=%i\n", evnt);
	printf("Task7\n");
	TerminateTask();
}

//3
TASK(Task8)
{
	printf("Start Task8\n");
	SetSysEvent(Event_1);
	printf("Task8\n");
	TerminateTask();
}