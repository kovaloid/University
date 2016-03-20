/*********************************/
/*           task.cpp            */
/*********************************/

#include <stdio.h>
#include <string.h>
#include "sys.h"
#include "rtos_api.h"

// добавить задачу перед item, head указывает на голову списка
void InsertTaskBefore(int task, int item, int *head)
{
	if(TaskQueue[task].next != -1)
		return;
	if(item == *head)
		*head = task;
	TaskQueue[task].next = item;
	TaskQueue[task].prev = TaskQueue[item].prev;
	TaskQueue[TaskQueue[item].prev].next = task;
	TaskQueue[item].prev = task;
}

void InsertTaskAfter(int task, int item)
{
	if(TaskQueue[task].next != -1)
		return;
	TaskQueue[task].next = TaskQueue[item].next;
	TaskQueue[task].prev = item;
	TaskQueue[TaskQueue[item].next].prev = task;
	TaskQueue[item].next = task;
}

void RemoveTask(int task, int *head)
{
	if(TaskQueue[task].next == -1)
		return;
	if(*head == task)
	{
		if(TaskQueue[task].next == task)
			*head = -1;
		else
			*head = TaskQueue[task].next;
	}
	TaskQueue[TaskQueue[task].prev].next = TaskQueue[task].next;
	TaskQueue[TaskQueue[task].next].prev = TaskQueue[task].prev;
	TaskQueue[task].next = -1;
	TaskQueue[task].prev = -1;
}

void ActivateTask(TTaskCall entry,int priority,char* name)
{
	int task,occupy;
	printf("ActivateTask %s\n",name);
	task=TaskHead;
	occupy=FreeTask;
	// изменяем список свободных задач
	RemoveTask(occupy, &FreeTask);
	TaskQueue[occupy].priority=priority;
	TaskQueue[occupy].ceiling_priority=priority;
	TaskQueue[occupy].name=name;
	TaskQueue[occupy].entry=entry;
	TaskQueue[occupy].switch_count = 0;
	TaskQueue[occupy].task_state = TASK_READY;
	TaskCount++;
	printf("End of ActivateTask %s\n",name);
	Schedule(occupy);
}

void TerminateTask(void)
{
	int task;
	TaskCount--;
	task=RunningTask;
	printf("TerminateTask %s\n",TaskQueue[task].name);
	TaskQueue[task].task_state = TASK_SUSPENDED;
	RemoveTask(task, &TaskHead);
	// добавляем задачу в список свободных
	InsertTaskBefore(task, FreeTask, &FreeTask);
	printf("End of TerminateTask %s\n",TaskQueue[task].name);
	if(TaskCount == 0)
		longjmp(MainContext, 1);
	Dispatch();
}

void Schedule(int task, int dont_show)
{
	int cur;
	int priority;
	if(TaskQueue[task].task_state == TASK_SUSPENDED)
		return;
	if(!dont_show)
		printf("Schedule %s\n",TaskQueue[task].name);
	if(TaskHead == -1)
	{
		TaskHead = task;
		TaskQueue[task].next = task;
		TaskQueue[task].prev = task;
	}
	else if(TaskCount > 1)
	{
		cur = TaskHead;
		if(cur == task)
		// защита от ниже лежащего RemoveTask
			cur = TaskQueue[cur].next;
		priority=TaskQueue[task].ceiling_priority;
		RemoveTask(task, &TaskHead);
		while (TaskQueue[cur].ceiling_priority <= priority)
		{
			cur=TaskQueue[cur].next;
			if(cur == TaskHead)
			// нет задачи с таким низким приоритетом - поставим ее в конец списка
				break;
		}
		if(priority >= TaskQueue[TaskHead].ceiling_priority && cur == TaskHead)
			// вставляем в конец списка
			InsertTaskAfter(task, TaskQueue[TaskHead].prev);
		else
			InsertTaskBefore(task, cur, &TaskHead);
	}
	if(!dont_show)
		printf("End of Schedule %s\n",TaskQueue[task].name);
}

void TaskSwitch(int nextTask)
{
	if(nextTask == -1)
		return;
	TaskQueue[nextTask].task_state = TASK_RUNNING;
	RunningTask = nextTask;
	TaskQueue[nextTask].switch_count++;
	if(TaskQueue[nextTask].switch_count == 1)
		longjmp(InitStacks[nextTask], 1);
	else
		longjmp(TaskQueue[nextTask].context, 1);
}

void Dispatch()
{
	if(RunningTask != -1)
		printf("Dispatch - %s\n", TaskQueue[RunningTask].name);
	else
		printf("Dispatch\n");
	if(RunningTask != -1 && TaskQueue[RunningTask].task_state == TASK_RUNNING)
		TaskQueue[RunningTask].task_state = TASK_READY;
	int cur = TaskHead;
	while(TaskCount)
	{ // переключение задач проще не сделать, т.к. работаем через setjmp и longjmp
		if(TaskQueue[cur].task_state == TASK_READY)
		{ // переключаемся на следующую задачу
			printf("End of Dispatch - %s\n", TaskQueue[cur].name);
			if(RunningTask == -1 || TaskQueue[RunningTask].task_state == TASK_SUSPENDED)
				TaskSwitch(cur);
			else if(!setjmp(TaskQueue[RunningTask].context))
				TaskSwitch(cur);
			break;
		}
		cur = TaskQueue[cur].next;
		if(cur == TaskHead)
		{
			printf("Dont have ready tasks\n");
			longjmp(MainContext,1);
		}
	}
	Schedule(cur, 1);
}