#include <conio.h>
#include <iostream.h>

void main()
{
  int far *pA = (int *)0xB8000000;
  int far *pB = (int *)0xB9000000;
  int i;
 
  clrscr();
  cout<<"A: ";
  for (i=0; i<10; i++)
    cout<<pA[i]<<" ";

  cout<<endl<<"B: ";
  for (i=0; i<10; i++)
    cout<<pB[i]<<" ";

  asm push ds
  asm push es
  asm lds si,pA
  asm les di,pB
  asm mov cx,10
  asm rep movsw
  asm pop es
  asm pop ds

  cout<<endl<<endl<<"A: ";
  for (i=0; i<10; i++)
    cout<<pA[i]<<" ";

  cout<<endl<<"B: ";
  for (i=0; i<10; i++)
    cout<<pB[i]<<" ";

  getch();
}