#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MQ_KEY1 1234L
#define MQ_KEY2 2345L
#define MAXMESGDATA 4096

struct mymesg {
	long mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
	};

void server(int readid, int writeid);
ssize_t mesg_send(int id, struct mymesg *mptr);
ssize_t mesg_recv(int id, struct mymesg *mptr);

int main(int argc,char **argv)
{
	int readid, writeid;
	key_t key1, key2;

	printf("Server: HELLO!\n");

/*
	if((key1=ftok("/home/tvk/IPC/input.txt",'A'))<0)
	{
		printf("Server: can not get key!\n"); exit(1);
	}
	printf("key1=%x\n",key1);
*/
	if((readid=msgget(MQ_KEY1, 0666|IPC_CREAT))<0)
	{
		printf("Server: can not get readid!\n"); exit(1);
	}
	printf("Server: readid=%d\n",readid);
/*	
	if((key2=ftok("/home/tvk/IPC/server_msg.c",'B'))<0)
	{
		printf("Server: can not get key!\n"); exit(1);
	}
	printf("key2=%x\n",key2);
*/
	if((writeid=msgget(MQ_KEY2, 0666|IPC_CREAT))<0)
	{
		printf("Server: can not get readid!\n"); exit(1);
	}
	printf("Server: writeid=%d\n",writeid);

	server(readid,writeid);

	exit(0);
}

void server(int readid, int writeid)
{
	FILE *fp;
	ssize_t n;
	struct mymesg ourmesg;
	
	printf("Server: readid=%d writeid=%d\n",readid,writeid);

	ourmesg.mesg_type=0L;

	if((n=mesg_recv(readid, &ourmesg)) == 0)
		printf("Server: can not read file name\n");
	ourmesg.mesg_data[n]='\0';

	printf("Server: file name %s\n",ourmesg.mesg_data);

	if( (fp=fopen(ourmesg.mesg_data,"r"))==NULL)
	{ printf("Server: can not open file name\n"); }
	else
	{
		printf("Server: %s is opened\n",ourmesg.mesg_data);

	while(fgets(ourmesg.mesg_data, MAXMESGDATA,fp) != NULL)
		{ 
			ourmesg.mesg_len=strlen(ourmesg.mesg_data);
			printf("Server: %s",ourmesg.mesg_data);
		}
	}
	fclose(fp);
	ourmesg.mesg_data[--ourmesg.mesg_len]='\0';
	mesg_send(writeid,&ourmesg);
}

ssize_t mesg_send(int id, struct mymesg *mptr)
{
	if(msgsnd(id,mptr,mptr->mesg_len+8,0) != 0)
		printf("Ошибка записи сообщения в очередь\n");
}

ssize_t mesg_recv(int id, struct mymesg *mptr)
{
	ssize_t n;
	size_t len;
	
	if((n=msgrcv(id,mptr,MAXMESGDATA,mptr->mesg_type,0))==0)
	{
		printf("Server: can not read file name\n");
   	        return(0);		
	}

	if((len=mptr->mesg_len)>0) return(len);
	else return(0);
}
