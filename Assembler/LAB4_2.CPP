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
m1:
  asm push cx;
  asm mov cx,N;
m2:
  asm mov ax,1;
  asm mov [di],ax;
  asm add di,2;
  asm loop m2;
  asm add di,N*2;
  asm pop cx;
  asm loop m1;

	
  for (i=0; i<N*N; i++)
  {
    if (!(i % N)) cout<<endl;
    cout<<A[i]<<' ';
  };
  cout<<endl;

  getch();
};