/*
»спользу€ функцию CreateProcess, создайте процесс дл€ запуска notepad.exe.
*/

#include <windows.h>
#include <stdio.h>
#include <string>

STARTUPINFO startinfo;
PROCESS_INFORMATION processInfo;

int main()
{
	char * lpCommandLine = "C:\\WINDOWS\\SYSTEM32\\NOTEPAD.EXE";
	ZeroMemory (&startinfo,sizeof(STARTUPINFO));
	startinfo.cb = sizeof(startinfo);

	if(!CreateProcess(NULL, LPTSTR(lpCommandLine), NULL, NULL, FALSE, 
	HIGH_PRIORITY_CLASS | CREATE_NEW_CONSOLE, NULL, NULL, &startinfo, &processInfo))
	{
		fprintf(stderr,"CreateProcess failed on error %d\n",GetLastError());
		ExitProcess(1);
	}

	CloseHandle(processInfo.hThread);
	CloseHandle(processInfo.hProcess);

	return 0;
}