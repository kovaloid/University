/*
” вас должно быть два процесса:
Х	ѕервый процесс источник (source) Ц он должен читать информацию из файла и записывать ее в канал;
Х	¬торой процесс приемник (sink) Ц получает информацию из канала и записывает ее во второй файл.
ѕроцессы должны работать с разными скорост€ми, чтобы протестировать работу.
*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main()
{
	HANDLE readSource, writeDest;
	SECURITY_ATTRIBUTES pipeSA;
	STARTUPINFO sourceStartInfo, destStartInfo;
	PROCESS_INFORMATION sourceProcessInfo, destProcessInfo;
	
	pipeSA.lpSecurityDescriptor = NULL;
	pipeSA.bInheritHandle=TRUE;
	pipeSA.nLength = sizeof(pipeSA);

	if(!CreatePipe(&readSource,&writeDest,&pipeSA,1024))
	{
		printf("Failed to create pipe!\n");
		ExitProcess(1);
	}
	else
		printf("Pipe was created!\n");

	memset(&sourceStartInfo,0,sizeof(STARTUPINFO));
	sourceStartInfo.cb=sizeof(STARTUPINFO);
	sourceStartInfo.hStdInput=GetStdHandle(STD_INPUT_HANDLE);
	sourceStartInfo.hStdOutput=writeDest;
	sourceStartInfo.hStdError=GetStdHandle(STD_ERROR_HANDLE);
	sourceStartInfo.dwFlags=STARTF_USESTDHANDLES;

	if(!CreateProcess(NULL,"source.exe",NULL,NULL,TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &sourceStartInfo,&sourceProcessInfo))
	{
		printf("Failed to create source process!\n ");
		ExitProcess(1);
	}
	else
		printf("Source process was created!\n");

	memset(&destStartInfo,0,sizeof(STARTUPINFO));
	destStartInfo.cb=sizeof(STARTUPINFO);
	destStartInfo.hStdInput=readSource;
	destStartInfo.hStdOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	destStartInfo.hStdError=GetStdHandle(STD_ERROR_HANDLE);
	destStartInfo.dwFlags=STARTF_USESTDHANDLES;
	
	if(!CreateProcess(NULL,"dest.exe",NULL,NULL,TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &destStartInfo,&destProcessInfo))
	{
		printf("Failed to create dest process!\n ");
		ExitProcess(1);
	}
	else
		printf("Dest process was created!\n");
		
	printf("Press enter to exit...\n");
	_getch();

	CloseHandle(readSource);
	CloseHandle(writeDest);
	CloseHandle(sourceProcessInfo.hProcess);
	CloseHandle(destProcessInfo.hProcess);

	return 0;
}