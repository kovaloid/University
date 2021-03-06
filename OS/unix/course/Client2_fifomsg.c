#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define ID "id_2"
#define GET "get_id"
#define FIFO2_in "/tmp/fifo.2.in"
#define FIFO2_out "/tmp/fifo.2.out"
#define MAXMESGDATA 4096
#define MESGHDRSIZE 2*sizeof(long)

struct mymesg {
	long mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
} msg;

void client(int readfd, int writefd);
ssize_t mesg_send(int fd, struct mymesg *mptr);
ssize_t mesg_recv(int fd, struct mymesg *mptr);

int main(int argc,char **argv)
{
        int readfd, writefd;

        if( (writefd=open(FIFO2_in, O_WRONLY))<0)
        {
        	printf("Client_2: can not open FIFO2_in for write\n");
                exit(1);
        }
	printf("Client_2: FIFO2_in is opened for write writefd=%d\n",writefd);

        if( (readfd=open(FIFO2_out, O_RDONLY))<0)
        {
        	printf("Client_2: can not open FIFO2_out for read\n");
                exit(1);
        }
	printf("Client_2: FIFO2_out is opened for read readfd=%d\n",readfd);

        client(readfd,writefd);

        close(readfd);
        close(writefd);

        if (unlink(FIFO2_in) < 0)
        {
        	printf("Client_2: can not delete FIFO2_in\n");
        	exit(1);
        }
	printf("Client_2: FIFO2_in is deleted!\n");

        if (unlink(FIFO2_out) < 0)
        {
        	printf("Client_2: can not delete FIFO2_out\n");
        	exit(1);
        }
	printf("Client_2: FIFO2_out is deleted!\n");

	printf("Client_2 is terminated!\n");
        exit(0);
}

void client(int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	char buff[MAXMESGDATA];
	sleep(1);

	printf("=== Нажмите enter или введите get_info:\n");
	fgets(buff,MAXMESGDATA,stdin);
	len=strlen(buff);
	if(buff[len-1]=='\n')
	len--;

	msg.mesg_len = len;
	msg.mesg_type = 1;
	sprintf(msg.mesg_data,"%s",buff);
	mesg_send(writefd, &msg);

	n = mesg_recv(readfd, &msg);

	if(!strcmp(msg.mesg_data,GET) && 
	((msg.mesg_type==010) || (msg.mesg_type==110) || (msg.mesg_type==011)))
	{
		printf("=== Сервер запрашивает id клиента 2...\n");
		msg.mesg_len = strlen(ID);
		msg.mesg_type = 1;
		sprintf(msg.mesg_data,"%s",ID);
		mesg_send(writefd, &msg);
	}
	else 
	{
		if(msg.mesg_type==000)
		{
			printf("=== Ни один клиент не запросил данные! Выход...\n");
			if (unlink(FIFO2_in) < 0) printf("Client_2: can not delete FIFO2_in\n");
			else printf("Client_2: FIFO2_in is deleted!\n");
			if (unlink(FIFO2_out) < 0) printf("Client_2: can not delete FIFO2_out\n");
			else printf("Client_2: FIFO2_out is deleted!\n");
			exit(0);
		}
		else if(msg.mesg_type==111)
		{
			printf("=== Все клиенты запросили данные! Выход...\n");
			if (unlink(FIFO2_in) < 0) printf("Client_2: can not delete FIFO2_in\n");
			else printf("Client_2: FIFO2_in is deleted!\n");
			if (unlink(FIFO2_out) < 0) printf("Client_2: can not delete FIFO2_out\n");
			else printf("Client_2: FIFO2_out is deleted!\n");
			exit(0);
		}
		else printf("=== Сервер скоро пришлет информацию из БД...\n");

		msg.mesg_len = 0;
		msg.mesg_type = 0;
		sprintf(msg.mesg_data,"%s","");
		mesg_send(writefd, &msg);
		if((n=mesg_recv(readfd, &msg))>0)
			printf("=== Информация о других клиентах:\n%s\n",msg.mesg_data);
	}
}

ssize_t mesg_send(int fd, struct mymesg *mptr)
{
	return(write(fd,mptr,MESGHDRSIZE+mptr->mesg_len));	
}

ssize_t mesg_recv(int fd, struct mymesg *mptr)
{
	ssize_t n;
	size_t len;

	if((n=read(fd,mptr,MESGHDRSIZE))==0)
		return(0);
	else if(n!=MESGHDRSIZE)
	{
		printf("Client_2: error MESGHDRSIZE\n");
		return(0);
	}

	if((len=mptr->mesg_len)>0)
		if((n=read(fd,mptr->mesg_data,len))!=len)
		{
			printf("Client_2: message data expected len=%d, got n=%d\n",(int)len,(int)n);
   	        	exit(1);		
		}

	return(len);	
}
