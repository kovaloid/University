/******************************/
/*           os.cpp           */
/******************************/

#include <stdio.h>
#include "sys.h"
#include "rtos_api.h"

void InitializeStacks(int numStack)
{
	char cushionSpace[10000];
	cushionSpace[9999] = 1; // отключаем оптимизацию массивов
	if(!setjmp(InitStacks[numStack]))
	{ // инициализация
		if(numStack <= MAX_TASK)
		InitializeStacks(numStack+1);
	}
	else
	{ // выполнение
		TaskQueue[RunningTask].entry();
	}
}

int StartOS(TTaskCall entry,int priority,char* name)
{
	int i;
	InitializeStacks(0);
	RunningTask = TaskHead = -1;
	TaskCount = 0;
	FreeTask=0;
	WorkingEvents=0;
	printf("StartOS!\n");
	for(i=0;i<MAX_TASK;i++)
	{
		TaskQueue[i].next=i+1;
		TaskQueue[i].prev = i - 1;
		TaskQueue[i].task_state = TASK_SUSPENDED;
		TaskQueue[i].switch_count = 0;
		TaskQueue[i].waiting_events = 0;
	}
	TaskQueue[MAX_TASK-1].next=0;
	TaskQueue[0].prev=MAX_TASK-1;
	if(!setjmp(MainContext))
	{
		ActivateTask(entry,priority,name);
		Dispatch();
	}
	return 0;
}

void ShutdownOS()
{
	printf("ShutdownOS!\n");
}