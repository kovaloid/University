#include <conio.h>
#include <iostream.h>
#define N 6

void main()
{
  int A[N*N],i;
  int far *pA = &A[0];

  for (i=0; i<N*N; i++)
    A[i]=0;

  clrscr();
  for (i=0; i<N*N; i++)
  {
    if (!(i % N)) cout<<endl;
    cout<<A[i]<<' ';
  };
  cout<<endl;
	

  asm les di,pA;
  asm add di,N*2;
  asm mov cx,N/2;
  asm mov ax,1;
met:
  asm push cx;
  asm mov cx,N;
  asm rep stosw;
  asm add di,N*2;
  asm pop cx;
  asm loop met;
	

  for (i=0; i<N*N; i++)
  {
    if (!(i % N)) cout<<endl;
    cout<<A[i]<<' ';
  };
  cout<<endl;

  getch();
};