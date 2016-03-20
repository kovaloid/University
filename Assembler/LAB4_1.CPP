#include <conio.h>
#include <iostream.h>
#include <time.h>
#define N 100000

void main(void)
{
  long int i;
  int j;
  clrscr();

  cout<<"--- add ax,bx ---"<<endl;
  float t1=clock();
  for (i=0; i<N; i++)
    for (j=0; j<N/10; j++)
      asm add ax,bx;
  float t2=clock();
  float t=((t2-t1)/CLK_TCK);
  cout<<"Clock rate: "<<10/t<<endl;
  cout<<"Time: "<<t<<endl<<endl;

  cout<<"--- add ax,[bx+si+5] ---"<<endl;
  t1=clock();
  for (i=0; i<N; i++)
    for (j=0; j<N/10; j++)
      asm add ax,[bx+si+5];
  t2=clock();
  t=((t2-t1)/CLK_TCK);
  cout<<"Clock rate: "<<10/t<<endl;
  cout<<"Time: "<<t<<endl<<endl;

  cout<<"--- add ax,[bx] ---"<<endl;
  t1=clock();
  for (i=0; i<N; i++)
    for (j=0; j<N/10; j++)
      asm add ax,[bx];
  t2=clock();
  t=((t2-t1)/CLK_TCK);
  cout<<"Clock rate: "<<10/t<<endl;
  cout<<"Time: "<<t<<endl<<endl;

  cout<<"--- add [bx],ax ---"<<endl;
  t1=clock();
  for (i=0; i<N; i++)
    for (j=0; j<N/10; j++)
      asm add [bx],ax;
  t2=clock();
  t=((t2-t1)/CLK_TCK);
  cout<<"Clock rate: "<<10/t<<endl;
  cout<<"Time: "<<t<<endl<<endl;

  getch();
}
