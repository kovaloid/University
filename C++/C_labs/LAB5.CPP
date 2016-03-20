#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
REGS regs;

int InitGraph(void)
{
  int gdriver=DETECT,gmode,errorcode;
  initgraph(&gdriver,&gmode,"");
  errorcode=graphresult();
  if (errorcode!=grOk)
  {
    printf("Graphics error: %s\n", grapherrormsg(errorcode));
    printf("Press any key to halt:");
    getch();
    return 0;
  }
  return 1;
}

void InitMouse(int *nbuttons,int *OK)
{
  regs.x.ax=0;
  int86(0x33,&regs,&regs);
  *OK=regs.x.ax;
  *nbuttons=regs.x.bx;
}

void ShowMouse(void)
{
  regs.x.ax=1;
  int86(0x33,&regs,&regs);
}

void HideMouse(void)
{
  regs.x.ax=2;
  int86(0x33,&regs,&regs);
}

void ReadMouse(int *x,int *y,int *buttons)
{
  regs.x.ax=3;
  int86(0x33,&regs,&regs);
  *buttons=regs.x.bx;
  *x=regs.x.cx;
  *y=regs.x.dx;
}

void SetMouse(int x,int y)
{
  regs.x.ax=4;
  regs.x.cx=x;
  regs.x.dx=y;
  int86(0x33,&regs,&regs);
}

void MoveToXY(int x,int y)
{
  regs.h.ah=2;
  regs.h.dh=y;
  regs.h.dl=x;
  regs.h.bh=0;
  int86(0x10,&regs,&regs);
}

int main(void)
{
  int x,y,but,nbuttons,OK,xold=-1,yold;
  if (!InitGraph())
    return 0;
  InitMouse(&nbuttons,&OK);
  printf(" Init mouse:\n nb=%d OK=%d\n Press left button of mouse...",nbuttons,OK);
  ShowMouse();
  SetMouse(0,0);
  do
  {
    ReadMouse(&x,&y,&but);
  }
  while(!(but&1));
  cleardevice();
  MoveToXY(30,0);
  printf("Start X-Y: %d %d",x,y);
  do
  {
    ReadMouse(&x,&y,&but);
    if (xold==-1)
    {
      xold=x;
      yold=y;
    }
    else
    {
      if (xold!=x||yold!=y)
      {
	HideMouse();
	line(xold,yold,x,y);
	xold=x;
	yold=y;
	ShowMouse();
      }
    }
  }
  while(but&1);
  HideMouse();
  MoveToXY(30,0);
  printf("Press Enter to exit...");
  getch();
  closegraph();
  return 1;
}
