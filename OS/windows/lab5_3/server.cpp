#include <winsock2.h>
#include <stdio.h>
#define INSTANCE 3

SOCKET serverSock;
sockaddr_in ServerAddr;

DWORD WINAPI ServerFunct(PVOID pvParam) {
	int nThreadNum = PtrToUlong(pvParam);
	SOCKET serverSocket;
	sockaddr_in ClientAddr;
	int ClientAddrLen = sizeof(ClientAddr);
	char buff[256];
	while (true) {
		serverSocket = accept(serverSock,(sockaddr*)&ClientAddr,&ClientAddrLen);
		if(serverSocket == INVALID_SOCKET) {
			printf("Accept failed with error %d \n",WSAGetLastError());
			return 0;
		}
		printf("Server: thread %d is running...\n\n",nThreadNum);
		recv(serverSocket,buff,22,0);
		buff[22] = 0;
		printf("%s",buff);
		strcpy(buff,"  hello from server\n");
		send(serverSocket,buff,22,0);
		while (true) {
			recv(serverSocket,buff,100,0);
			if (!strcmp(buff,"exit")) break;
			buff[100] = 0;
			printf("  %s\n",buff);	
			strcpy(buff,"Server: message sent with no problems\n");
			send(serverSocket,buff,100,0);
		}
		printf("\nServer: thread %d is stopped\n",nThreadNum);
		closesocket(serverSocket);
	}
	return 0;
}

void main() {
	struct hostent *pHostEnt;
	char HostName[64];
	int ServerAddrLen = sizeof(ServerAddr);
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)) {
		printf("WSA service failed to initialize with error %d \n",WSAGetLastError());
		return;
	}
	serverSock = socket(AF_INET,SOCK_STREAM,0);
	if(serverSock == INVALID_SOCKET) {
		printf("Socket initialization failed with error %d \n",WSAGetLastError());
		return;
	}
	gethostname(HostName,64);
	pHostEnt = gethostbyname(HostName);
	if(pHostEnt == NULL) {
		printf("Can't get host by name.");
		return;
	}
	printf("Server is running on %s \n",HostName);
	memcpy(&ServerAddr.sin_addr,pHostEnt->h_addr,4);
	ServerAddr.sin_port = htons(34803);
	ServerAddr.sin_family = AF_INET;
	if(bind(serverSock,(sockaddr*)&ServerAddr,ServerAddrLen)!=0) {
		printf("Bind failed with error %d \n",WSAGetLastError());
		closesocket(serverSock);
		return;
	}
	printf("\nServer: listening...\n");
	if(listen(serverSock,INSTANCE)) {
		printf("Listen failed with error %d \n",WSAGetLastError());
		closesocket(serverSock);
		return;
	}
	printf("Server: ready!\n");
	HANDLE hThreads[INSTANCE];
	for (int i = 0;i < INSTANCE;i++) {
		hThreads[i] = CreateThread(NULL,0,ServerFunct,(PVOID)(INT_PTR)i,0,NULL);
		if (hThreads[i] == NULL)
			printf("Can't create thread !");
	}
	WaitForMultipleObjects(INSTANCE,hThreads,TRUE,INFINITE);
	for (int i=0;i <INSTANCE;i++)	
		CloseHandle(hThreads[i]);
	WSACleanup();
}