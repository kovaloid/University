#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define IN_FILE L"output.txt"

int main(int argc, char* argv[])
{
	HANDLE hStdIn,hStdOut;
	DWORD bytesRead,bytesWritten;
	char buffer[100];

	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = CreateFile(IN_FILE,GENERIC_WRITE,0,NULL,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL,NULL);

	srand(time(NULL));

	for (;;)
	{
		if (!ReadFile(hStdIn,buffer,50,&bytesRead,NULL))
		{
			printf("Dest couldn't read from stdin!\n");
			exit(1);
		}

		Sleep(rand()%100);
		
		if (!WriteFile(hStdOut,buffer,bytesRead,&bytesWritten,NULL))
		{
			printf("Dest couldn't write to stdout!\n");
			exit(1);
		}
	}

	CloseHandle(hStdIn);
	CloseHandle(hStdOut);

	return 0;
}