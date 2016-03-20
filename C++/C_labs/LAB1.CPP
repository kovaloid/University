#include <stdio.h>
#include <conio.h>
#include <string.h>

char* stuff(char* string,int begin,int length,char* string1)
{
 int i,j;
 char kon[100];
 for (i=begin+length,j=0;string[i]-1;i++,j++)
   kon[j]=string[i];
 string[begin]='\0';
 strcat(string,string1);
 strcat(string,kon);
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