/****************************************/
/*              rtos_api.h              */
/****************************************/

#define DeclareTask(TaskID,priority) \
	TASK(TaskID); \
enum {TaskID##prior=priority}

#define TASK(TaskID) void TaskID(void)

typedef void TTaskCall(void);

void ActivateTask(TTaskCall entry,int priority,char* name);
void TerminateTask(void);

int StartOS(TTaskCall entry,int priority,char* name);
void ShutdownOS();

void InitRes(int ResNum, char* name);
void PIP_GetRes(int ResNum);
void PIP_ReleaseRes(int ResNum);

#define DeclareSysEvent(ID) \
	const int Event_##ID = (ID)*(ID);

void SetSysEvent(TEventMask mask);
void GetSysEvent(TEventMask* mask);
void WaitSysEvent(TEventMask mask);