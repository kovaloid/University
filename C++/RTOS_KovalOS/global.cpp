/****************************************/
/*              global.cpp              */
/****************************************/

#include "sys.h"

TTask TaskQueue[MAX_TASK];
TResource ResourceQueue[MAX_RES];
jmp_buf InitStacks[MAX_TASK];
jmp_buf MainContext;
int RunningTask;
int TaskHead;
int TaskCount;
int FreeTask;
TEventMask WorkingEvents;