#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define IN_FILE L"input.txt"

int main(int argc, char* argv[]) 
{
	HANDLE hFile,hStdOut;
	DWORD bytesRead,bytesWritten;
	char buffer[100];
	
	hFile = CreateFile(IN_FILE,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	srand(time(NULL));

	for (;;)
	{
		if(!ReadFile(hFile,buffer,1,&bytesRead,NULL))
		{
			printf("Source couldn't open a file!\n");
			exit(1);
		}

		Sleep(rand()%100);

		if(!WriteFile(hStdOut,buffer,bytesRead,&bytesWritten,NULL))
		{
			printf("Source couldn't write to stdout!\n");
			exit(1);
		}
	}

	CloseHandle(hFile);
	CloseHandle(hStdOut);

	return 0;
}