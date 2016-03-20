/*
Подготовить исходный файл с содержимом (например, abcdefghij…). Используя отображаемый в память файл, 
поработать с исходным файлом, читая и записывая в память. Убедится в том, что исходное содержимое файла изменилось.
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <iostream>

#define IN_FILE "work.txt"

int main()
{
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(sa);

	HANDLE hFile = CreateFile(L"work.txt", GENERIC_READ | GENERIC_WRITE,
					FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("File can't be open! Error: %d\n",GetLastError());
	}
	else
	{
		printf("File has been opened...\n");
	}
	HANDLE hFileMap = CreateFileMapping(hFile, &sa, PAGE_READWRITE, 0, 0, L"file_mapping");
	if (hFileMap == NULL)
	{
		printf("Error creating file mapping! Code: %d\n",GetLastError());
		exit(1);
	}
	else
	{
		printf("File mapping created successfully!\n");
	}
	PVOID MapView = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (MapView == NULL)
	{
		printf("Error creating map view of file! Code: %d\n",GetLastError());
		exit(1);
	}
	else
	{
		printf("Map view of file created successfully!\n");
	}

	DWORD filesize = GetFileSize(hFile,NULL);
	PSTR pchANSI=(PSTR)MapView;
	printf("\nContent of the file %s :\n",IN_FILE);
	for(int i=0; i<filesize; i++)
	{
		printf("%c",pchANSI[i]);
	}
	printf("\n\nEnter new string (%d symbols): \n", filesize);
	for(int i=0;i < filesize;i++)
	{
		scanf("%c",&pchANSI[i]);
	}	
	printf("\nNew content of the file %s :\n",IN_FILE);
	for(int i=0;i < filesize;i++)
	{
		printf("%c",pchANSI[i]);
	}

	if (!UnmapViewOfFile(MapView))
	{
		printf("Error unmapping file! Code: %d\n",GetLastError());
	}
	if (!CloseHandle(hFile))
	{
		printf("Error closing file handler! Code: %d\n",GetLastError());
	}
	if (!CloseHandle(hFileMap))
	{
		printf("Error closing file mapping handler! Code: %d\n",GetLastError());
	}

	_getch();
	return 0;
}