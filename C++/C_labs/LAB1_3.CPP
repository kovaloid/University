#include <stdio.h>
#include <conio.h>

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

void main(void)
{
 char string[100],string1[100];
 int length,begin;
 clrscr();
 printf("Enter string of symbols:\n");
 scanf("%s",string);
 printf("Enter number of first symbol:\n");
 scanf("%d",&begin);
 printf("Enter length:\n");
 scanf("%d",&length);
 printf("Enter new string:\n");
 scanf("%s",string1);
 stuff(string,begin,length,string1);
 printf("\nResult:\n%s\n",string);
 getch();
}