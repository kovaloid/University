#include <conio.h>
#include <iostream.h>

void main()
{
  int A[10] = {1,2,3,4,5,6,7,8,9,0};
  int B[10] = {0,0,0,0,0,0,0,0,0,0};
  int far *pA = A;
  int far *pB = B;

  asm push ds
  asm push es
  asm lds si,pA
  asm lds di,pB
  asm mov cx,10
  asm rep movsw
  asm pop es
  asm pop ds

  clrscr();
  for (int i=0; i<10; i++)
    cout<<B[i]<<" ";

  getch();
}