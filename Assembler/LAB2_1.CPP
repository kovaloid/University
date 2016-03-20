#include <conio.h>
#include <iostream.h>

void main()
{
 int a[10]={0,1,2,3,4,5,6,7,8,9};
 int b[10];

 asm lea si,a
 asm lea di,b
 asm mov cx,10
 met:
 asm mov ax,[si]
 asm mov [di],ax
 asm add si,2
 asm add di,2
 asm loop met

 clrscr();
 for (int i=0; i<10; i++)
   cout<<b[i]<<" ";
 getch();
}