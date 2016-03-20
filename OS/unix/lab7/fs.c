#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#define SIZE 100

int main(int argc,char **argv)
{
	int fd,i,nloop = 10;
	char buf[SIZE];

	if((fd=open("text", O_WRONLY | O_APPEND))<0)
	{
		printf("Can not open file\n");
		exit(1);
	}
	printf("File is opened!\n");

	if(fork()==0) {
		int count2 = 1;
		for(i=0;i<nloop;i++)
		{
			printf("child   %d\n",count2);
			sprintf(buf,"child   %d\n",count2);
			count2++;count2++;
			write(fd,buf,strlen(buf));
			usleep(400000);
		}
		close(fd);
		exit(0);
	}
	int count1 = 0;
	for(i=0;i<nloop;i++)
	{
		printf("parent  %d\n",count1);
		sprintf(buf,"parent  %d\n",count1);
		count1++;count1++;
		write(fd,buf,strlen(buf));
		usleep(400000);
	}
	close(fd);
	exit(0);
}
