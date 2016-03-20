#include <stdio.h>
#include <conio.h>
#include <string.h>

char* stuff(char* uk_string,int begin,int length,char* uk_string1)
{
 int i,j;
 char kon[100],*uk_kon;
 uk_kon=kon;
 for (i=begin+length,j=0;*(uk_string+i)-1;i++,j++)
   *(kon+j)=*(uk_string+i);
 *(uk_string+begin)='\0';
 strcat(uk_string,uk_string1);
 strcat(uk_string,uk_kon);
 return uk_string;
}

void main(void)
{
 char string[100],string1[100],*uk_string,*uk_string1;
 int length,begin;
 uk_string=string;
 uk_string1=string1;
 clrscr();
 printf("Enter string of symbols:\n");
 scanf("%s",uk_string);
 printf("Enter number of first symbol:\n");
 scanf("%d",&begin);
 printf("Enter length:\n");
 scanf("%d",&length);
 printf("Enter new string:\n");
 scanf("%s",uk_string1);
 stuff(uk_string,begin,length,uk_string1);
 printf("\nResult:\n%s\n",uk_string);
 getch();
}