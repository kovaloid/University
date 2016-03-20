/****************************************/
/*                sys.h                 */
/****************************************/

#include <csetjmp>
#include "defs.h"

enum TTaskState { TASK_RUNNING = 0, TASK_READY = 1, TASK_SUSPENDED = 2, TASK_WAITING = 3 };

typedef unsigned int TEventMask;

typedef struct Type_Task
{
	int next, prev;
	int priority; // ��� ������ �����, ��� ������ ���������
	int ceiling_priority;
	void (*entry)(void);
	char* name;
	TTaskState task_state;
	int switch_count;
	jmp_buf context;
	TEventMask waiting_events;
} TTask;

typedef struct Type_resource
{
	int task;
	char* name;
} TResource;

extern jmp_buf InitStacks[MAX_TASK];
extern TTask TaskQueue[MAX_TASK];
extern TResource ResourceQueue[MAX_RES];
extern int RunningTask; // ������� ������������� ������, �������� ������ � ������� TaskSwitch
extern int TaskHead; // ������ ������ � ������, ����������� ��������� �� ����������
extern int TaskCount;
extern int FreeTask;
extern TEventMask WorkingEvents;// ����������� �������
extern jmp_buf MainContext; // ������� ��������

void Schedule(int task, int dont_show = 0);
void Dispatch();