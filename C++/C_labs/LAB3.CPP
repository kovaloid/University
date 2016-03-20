#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

char* stuff(char* string,int begin,int length,char* string1)
{
 int i,j,k,strlen;
 char buf[100];
 for (k=0;string1[k];k++);
 for (strlen=0;string[strlen];strlen++);
// for (i=begin,j=0;string1[j]&&j<length;i++,j++)
//   string[i]=*(string1+j);
 for (i=begin+length,j=0;string[i]-1;i++,j++)
   buf[j]=string[i];
 for (i=begin+k,j=0;buf[j];i++,j++)
   string[i]=buf[j];
 string[i]='\0';
 for (i=begin,j=0;string1[j];i++,j++)
   string[i]=string1[j];
 return string;
}

void main(int argc,char* argv[])
{
 char string[100],string1[100];
 int length,begin;
 clrscr();
 strcpy(string,argv[1]);
 begin=atoi(argv[2]);
 length=atoi(argv[3]);
 strcpy(string1,argv[4]);
 printf("String of symbols:\n");
 printf(" %s\n",string);
 printf("First symbol:\n");
 printf(" %d\n",begin);
 printf("Length:\n");
 printf(" %d\n",length);
 printf("New string:\n");
 printf(" %s\n",string1);
 stuff(string,begin,length,string1);
 printf("\nResult:\n%s\n",string);
 getch();
}