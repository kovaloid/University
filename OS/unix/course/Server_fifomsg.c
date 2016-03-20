#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define GET "get_id"
#define GET_INFO "get_info"
#define DB "DataBase"
#define FIFO1_in "/tmp/fifo.1.in"
#define FIFO1_out "/tmp/fifo.1.out"
#define FIFO2_in "/tmp/fifo.2.in"
#define FIFO2_out "/tmp/fifo.2.out"
#define FIFO3_in "/tmp/fifo.3.in"
#define FIFO3_out "/tmp/fifo.3.out"
#define MAXMESGDATA 4096
#define MESGHDRSIZE 2*sizeof(long)

struct mymesg {
	long mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
} msg;

void server(int readfd1, int writefd1, int readfd2, int writefd2, int readfd3, int writefd3);
ssize_t mesg_send(int fd, struct mymesg *mptr);
ssize_t mesg_recv(int fd, struct mymesg *mptr);

int main(int argc,char **argv)
{
        int readfd1, writefd1, readfd2, writefd2, readfd3, writefd3;

        if( mknod(FIFO1_in, S_IFIFO | 0666, 0)<0)
        {
                printf("Server: can not create FIFO1_in\n");
                exit(1);
        }
	printf("Server: FIFO1_in is created!\n");

        if( mknod(FIFO1_out, S_IFIFO | 0666, 0)<0)
        {
                unlink(FIFO1_in);
                printf("Server: can not create FIFO1_out\n");
                exit(1);
        }
	printf("Server: FIFO1_out is created!\n");

	if( mknod(FIFO2_in, S_IFIFO | 0666, 0)<0)
        {
                printf("Server: can not create FIFO2_in\n");
                exit(1);
        }
	printf("Server: FIFO2_in is created!\n");

        if( mknod(FIFO2_out, S_IFIFO | 0666, 0)<0)
        {
                unlink(FIFO2_in);
                printf("Server: can not create FIFO2_out\n");
                exit(1);
        }
	printf("Server: FIFO2_out is created!\n");

	if( mknod(FIFO3_in, S_IFIFO | 0666, 0)<0)
        {
                printf("Server: can not create FIFO3_in\n");
                exit(1);
        }
	printf("Server: FIFO3_in is created!\n");

        if( mknod(FIFO3_out, S_IFIFO | 0666, 0)<0)
        {
                unlink(FIFO3_in);
                printf("Server: can not create FIFO3_out\n");
                exit(1);
        }
	printf("Server: FIFO3_out is created!\n");

        if( (readfd1=open(FIFO1_in, O_RDONLY))<0)
        {
        	printf("Server: can not open FIFO1_in for read\n");
                exit(1);
        }
	printf("Server: FIFO1_in is opened for read and readfd1=%d\n",readfd1);

        if( (writefd1=open(FIFO1_out, O_WRONLY))<0)
        {
         	printf("Server: can not open FIFO1_out for write\n");
                exit(1);
        }
	printf("Server: FIFO1_out is opened for write and writefd1=%d\n",writefd1);

	if( (readfd2=open(FIFO2_in, O_RDONLY))<0)
        {
        	printf("Server: can not open FIFO2_in for read\n");
                exit(1);
        }
	printf("Server: FIFO2_in is opened for read and readfd2=%d\n",readfd2);

        if( (writefd2=open(FIFO2_out, O_WRONLY))<0)
        {
         	printf("Server: can not open FIFO2_out for write\n");
                exit(1);
        }
	printf("Server: FIFO2_out is opened for write and writefd2=%d\n",writefd2);

	if( (readfd3=open(FIFO3_in, O_RDONLY))<0)
        {
        	printf("Server: can not open FIFO3_in for read\n");
                exit(1);
        }
	printf("Server: FIFO3_in is opened for read and readfd3=%d\n",readfd3);

        if( (writefd3=open(FIFO3_out, O_WRONLY))<0)
        {
         	printf("Server: can not open FIFO3_out for write\n");
                exit(1);
        }
	printf("Server: FIFO3_out is opened for write and writefd3=%d\n",writefd3);

        server(readfd1,writefd1,readfd2,writefd2,readfd3,writefd3);

	printf("Server is terminated!\n");
        exit(0);
}

void server(int readfd1, int writefd1, int readfd2, int writefd2, int readfd3, int writefd3)
{
	ssize_t n;
	int fd, flag1 = 0, flag2 = 0, flag3 = 0;
	char id_1[MAXMESGDATA], id_2[MAXMESGDATA], id_3[MAXMESGDATA];
        char err[MAXMESGDATA] = "=== Ошибка открытия БД!\n";

	if((n=mesg_recv(readfd1, &msg))==0)
		printf("=== Сlient_1 не передал серверу команду!\n");
	else if(!strcmp(msg.mesg_data,GET_INFO)) 
		flag1 = 1;

	if((n=mesg_recv(readfd2, &msg))==0)
		printf("=== Сlient_2 не передал серверу команду!\n");
	else if(!strcmp(msg.mesg_data,GET_INFO)) 
		flag2 = 1;

	if((n=mesg_recv(readfd3, &msg))==0)
		printf("=== Сlient_3 не передал серверу команду!\n");
	else if(!strcmp(msg.mesg_data,GET_INFO))
		flag3 = 1;

	msg.mesg_len = strlen(GET);
	sprintf(msg.mesg_data,"%s",GET);

	if((flag1==0) && (flag2==0) && (flag3==0))
	{
		printf("=== Ни один клиент не запросил данные! Выход...\n");
		msg.mesg_type = 000;
		mesg_send(writefd1, &msg);
		mesg_send(writefd2, &msg);
		mesg_send(writefd3, &msg);
		exit(0);
	}
	else if((flag1==1) && (flag2==1) && (flag3==1))
	{
		printf("=== Все клиенты запросили данные! Выход...\n");
		msg.mesg_type = 111;
		mesg_send(writefd1, &msg);
		mesg_send(writefd2, &msg);
		mesg_send(writefd3, &msg);
		exit(0);
	}
	else if((flag1==1) && (flag2==0) && (flag3==0))
	{
		printf("=== Сlient_1 скоро получит информацию о клиентах...\n");
		printf("=== Сlient_2 скоро передаст свой id...\n");
		printf("=== Сlient_3 скоро передаст свой id...\n");
		msg.mesg_type = 011;
	}
	else if((flag1==0) && (flag2==1) && (flag3==0))
	{
		printf("=== Сlient_1 скоро передаст свой id...\n");
		printf("=== Сlient_2 скоро получит информацию о клиентах...\n");
		printf("=== Сlient_3 скоро передаст свой id...\n");
		msg.mesg_type = 101;
	}
	else if((flag1==0) && (flag2==0) && (flag3==1))
	{
		printf("=== Сlient_1 скоро передаст свой id...\n");
		printf("=== Сlient_2 скоро передаст свой id...\n");
		printf("=== Сlient_3 скоро получит информацию о клиентах...\n");
		msg.mesg_type = 110;
	}
	else if(flag1==0)
	{
		printf("=== Сlient_1 скоро передаст свой id...\n");
		printf("=== Сlient_2 скоро получит информацию о клиентах...\n");
		printf("=== Сlient_3 скоро получит информацию о клиентах...\n");
		msg.mesg_type = 100;		
	}
	else if(flag2==0)
	{
		printf("=== Сlient_1 скоро получит информацию о клиентах...\n");
		printf("=== Сlient_2 скоро передаст свой id...\n");
		printf("=== Сlient_3 скоро получит информацию о клиентах...\n");
		msg.mesg_type = 010;
		
	}
	else if(flag3==0)
	{
		printf("=== Сlient_1 скоро получит информацию о клиентах...\n");
		printf("=== Сlient_2 скоро получит информацию о клиентах...\n");
		printf("=== Сlient_3 скоро передаст свой id...\n");
		msg.mesg_type = 001;
	}

	mesg_send(writefd1, &msg);
	mesg_send(writefd2, &msg);
	mesg_send(writefd3, &msg);

	if((n=mesg_recv(readfd1, &msg))==0)
		printf("=== Сlient_1 не передал серверу свой id!\n");
	else
	{
		printf("=== Сlient_1 передал серверу свой id!\n");
		msg.mesg_data[n]='\0';
		sprintf(id_1,"%s",msg.mesg_data);
		printf("Client_1 ID = %s\n",id_1);
	}

	if((n=mesg_recv(readfd2, &msg))==0)
		printf("=== Сlient_2 не передал серверу свой id!\n");
	else
	{
		printf("=== Сlient_2 передал серверу свой id!\n");
		msg.mesg_data[n]='\0';
		sprintf(id_2,"%s",msg.mesg_data);
		printf("Client_2 ID = %s\n",id_2);
	}

	if((n=mesg_recv(readfd3, &msg))==0)
		printf("=== Сlient_3 не передал серверу свой id!\n");
	else
	{
		printf("=== Сlient_3 передал серверу свой id!\n");
		msg.mesg_data[n]='\0';
		sprintf(id_3,"%s",msg.mesg_data);
		printf("Client_3 ID = %s\n",id_3);
	}

	if((fd=open(DB,O_RDONLY))<0)
	{
                n=strlen(err);
		msg.mesg_len = n;
		msg.mesg_type = 0;
		sprintf(msg.mesg_data,"%s",err);
		mesg_send(writefd1, &msg);
	}
	else
	{
		while((n=read(fd,msg.mesg_data,MAXMESGDATA))>0)
		{
			int i;
			char tmp[100];
			char name[8], phone[10];
			char client_1[50], client_2[50], client_3[50];
			char *ptr_tmp;

			printf("=== Server: начинаем поиск по БД!\n");
			if(flag1==0)
			{
				ptr_tmp = strstr(msg.mesg_data,id_1);

				for(i=0; i<8; i++)
					name[i] = ptr_tmp[i+14];
				for(i=0; i<10; i++)
					phone[i] = ptr_tmp[i+29];
				name[7] = '\0';
				phone[10] = '\0';
				
				sprintf(client_1,"%s","\n-Client_1\n-Name: ");
				strcat(client_1,name);
				strcat(client_1,"\n-Phone: ");
				strcat(client_1,phone);
				strcat(client_1,"\n\0");
			}
			if(flag2==0)
			{
				ptr_tmp = strstr(msg.mesg_data,id_2);

				for(i=0; i<8; i++)
					name[i] = ptr_tmp[i+14];
				for(i=0; i<10; i++)
					phone[i] = ptr_tmp[i+29];
				name[7] = '\0';
				phone[10] = '\0';

				sprintf(client_2,"%s","\n-Client_2\n-Name: ");
				strcat(client_2,name);
				strcat(client_2,"\n-Phone: ");
				strcat(client_2,phone);
				strcat(client_2,"\n\0");
			}
			if(flag3==0)
			{
				ptr_tmp = strstr(msg.mesg_data,id_3);

				for(i=0; i<8; i++)
					name[i] = ptr_tmp[i+14];
				for(i=0; i<10; i++)
					phone[i] = ptr_tmp[i+29];
				name[7] = '\0';
				phone[10] = '\0';

				sprintf(client_3,"%s","\n-Client_3\n-Name: ");
				strcat(client_3,name);
				strcat(client_3,"\n-Phone: ");
				strcat(client_3,phone);
				strcat(client_3,"\n\0");
			}

			if((flag1==1) && (flag2==0) && (flag3==0))
			{
				sprintf(tmp,"%s",client_2);	
				strcat(tmp,client_3);
			}
			else if((flag1==0) && (flag2==1) && (flag3==0))
			{
				sprintf(tmp,"%s",client_1);
				strcat(tmp,client_3);
			}
			else if((flag1==0) && (flag2==0) && (flag3==1))
			{
				sprintf(tmp,"%s",client_1);
				strcat(tmp,client_2);
			}
			else if(flag1==0)
				sprintf(tmp,"%s",client_1);
			else if(flag2==0)
				sprintf(tmp,"%s",client_2);	
			else if(flag3==0)
				sprintf(tmp,"%s",client_3);
	
			msg.mesg_len = strlen(tmp);
			msg.mesg_type = 1;
			sprintf(msg.mesg_data,"%s",tmp);

			printf("=== Server: начинаем передачу информации!\n");
			if(flag1==1)
			{
				printf("=== Server: информация передается на Client_1!\n");
				mesg_send(writefd1, &msg);
			}
			if(flag2==1)
			{
				printf("=== Server: информация передается на Client_2!\n");
				mesg_send(writefd2, &msg);
			}
			if(flag3==1)
			{
				printf("=== Server: информация передается на Client_3!\n");
				mesg_send(writefd3, &msg);
			}
		}
		close(fd);
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
	{
		printf("Server: end of file\n");
   	        return(0);		
	}
	else if(n!=MESGHDRSIZE) 
	{ 
		printf("Server: error MESGHDRSIZE\n"); 
		return(0); 
	}

	if((len=mptr->mesg_len)>0)
		if((n=read(fd,mptr->mesg_data,len))!=len)
		{
			printf("Server: %s\n",mptr->mesg_data);
			printf("Server: can not read msg\n");
			exit(1);
		}

	return(len);
}
