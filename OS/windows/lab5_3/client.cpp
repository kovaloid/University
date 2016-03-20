/*
ќрганизуйте общение между двум€ потоками в двух различных процессах. ѕусть один поток выступает инициатором 
(server) и посылает другому сообщение (client). ѕолучатель должен прин€ть посланное сообщение и ответить. 
*/

#include <winsock2.h>
#include <stdio.h>

void main(int argc, char* argv[]) {
	SOCKET clientSock;
	sockaddr_in serverAddr;
	struct hostent* pHostEnt;
	char hostName[64];
	int addrLen=sizeof(serverAddr);
	int nbytes;
	char buff[256];
	WORD versionRequested;
	WSADATA wsaData;
	WORD version = MAKEWORD(2,2);
	if(WSAStartup(version,&wsaData)) {
		printf("WSA service failed to initialize with error %d \n",WSAGetLastError());
		exit(1);
	};
	clientSock=socket(AF_INET,SOCK_STREAM,0);
	if(clientSock<0) {
		printf("Socket initialization failed \n");
		exit(1);
	};
	gethostname(hostName,64);
	printf("Client is running on %s \n",hostName);
	gethostname(hostName,64);
	printf("Connect with Server: ");
	scanf("%64s",&hostName);
	printf("\n");
	pHostEnt = gethostbyname(hostName);
	if(pHostEnt == NULL) {
		printf("Can't get host by name.");
		exit(1);
	};
	memcpy(&serverAddr.sin_addr, pHostEnt->h_addr,4);
	serverAddr.sin_port= htons(34803);
	serverAddr.sin_family=AF_INET;
	if(connect(clientSock,(sockaddr*)&serverAddr,addrLen)!=0) {
		printf("Connect error. \n");
		closesocket(clientSock);
		exit(1);
	};
	strcpy(buff,"  hello from client\n");
	send(clientSock,buff,22,0);
	recv(clientSock,buff,22,0);
	buff[22] = 0;
	printf("%s",buff);
	while (true) {
		printf("\n  ");
		scanf("%100s",&buff);
		send(clientSock,buff,100,0);
		if (!strcmp(buff,"exit")) break;
		recv(clientSock,buff,100,0);
		buff[100] = 0;
		printf("  %s",buff);
	}
	closesocket(clientSock);
	WSACleanup();
}