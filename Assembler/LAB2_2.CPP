#include <conio.h>
#include <iostream.h>

void main()
{
 int a[10]={2,1,2,3,4,5,6,7,8,9};
 int b[10];

 asm cld //skip flag of move <df>, it will be forward
 asm lea si,a
 asm lea di,b
 asm mov cx,10
 asm rep movsw

 clrscr();
 for (int i=0; i<10; i++)
   cout<<b[i]<<" ";

 getch();
}