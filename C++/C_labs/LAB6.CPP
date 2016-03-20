#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <bios.h>

class UpDown
{
  int x,y,num;
  char num_char[5];
 public:
  UpDown(int x1,int y1,int num1,char* num_char1);
  int InitGraph(void);
  void InitShowMouse(void);
  void ReadMouse(int* x,int* y,int* buttons);
  void draw(void);
  void get_mouse(int* x,int* y,int* num,char* num_char);
  void get_key(int* num,char* num_char);
};

UpDown::UpDown(int x1,int y1,int num1,char* num_char1)
{
  x=x1;
  y=y1;
  num=num1;
  *num_char=*num_char1;
}

void UpDown::draw(void)
{
  int up_button[8],down_button[8];
  setbkcolor(7);
  setfillstyle(1,8);
  setcolor(8);
  settextstyle(0,0,2);
  up_button[0]=85;up_button[1]=125;
  up_button[2]=115;up_button[3]=105;
  up_button[4]=145;up_button[5]=125;
  up_button[6]=up_button[0];up_button[7]=up_button[1];
  down_button[0]=85;down_button[1]=135;
  down_button[2]=145;down_button[3]=135;
  down_button[4]=115;down_button[5]=155;
  down_button[6]=down_button[0];down_button[7]=down_button[1];
  rectangle(60,60,300,200);
  outtextxy(90,40,"COUNTER");
  rectangle(80,100,150,160);
  line(80,130,150,130);
  fillpoly(4,up_button);
  fillpoly(4,down_button);
  rectangle(160,110,280,150);
  rectangle(340,100,450,160);
  outtextxy(360,125,"EXIT");
  outtextxy(180,120,"0");
}

void UpDown::get_mouse(int* x,int* y,int* num,char* num_char)
{
  if ((80<*x&&*x<150&&100<*y&&*y<130))
  {
    setfillstyle(1,7);
    bar(161,111,279,149);
    setfillstyle(1,8);
    *num=*num+1;
    itoa(*num,num_char,10);
    outtextxy(180,120,num_char);
  }
  else
  {
    if ((80<*x&&*x<150&&130<*y&&*y<160))
    {
      setfillstyle(1,7);
      bar(161,111,279,149);
      setfillstyle(1,8);
      *num=*num-1;
      itoa(*num,num_char,10);
      outtextxy(180,120,num_char);
    }
    else
    {
      if (340<*x&&*x<450&&100<*y&&*y<160)
      {
	closegraph();
	exit(0);
      }
    }
  }
}

void UpDown::get_key(int* num,char* num_char)
{
  int key=getch();
  key=getch();
  switch(key)
  {
    case 27 : exit(0);
    case 72 :
      setfillstyle(1,7);
      bar(161,111,279,149);
      setfillstyle(1,8);
      *num=*num+1;
      itoa(*num,num_char,10);
      outtextxy(180,120,num_char);
      break;
    case 80 :
      setfillstyle(1,7);
      bar(161,111,279,149);
      setfillstyle(1,8);
      *num=*num-1;
      itoa(*num,num_char,10);
      outtextxy(180,120,num_char);
      break;
    default: break;
  }
}

int UpDown::InitGraph(void)
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

void UpDown::InitShowMouse(void)
{
  REGS regs;
  regs.x.ax=0;
  int86(0x33,&regs,&regs);
  regs.x.ax=1;
  int86(0x33,&regs,&regs);
}

void UpDown::ReadMouse(int *x,int *y,int *buttons)
{
  REGS regs;
  regs.x.ax=3;
  int86(0x33,&regs,&regs);
  *buttons=regs.x.bx;
  *x=regs.x.cx;
  *y=regs.x.dx;
}

void main(void)
{
  UpDown UD(0,0,0,0);
  int x1,y1,but,num1=0;
  char num_char1[5];
  if (!UD.InitGraph())
    exit(0);
  UD.InitShowMouse();
  UD.draw();

  do
  {
    UD.ReadMouse(&x1,&y1,&but);
  }
  while(but&1);

  do
  {
    UD.ReadMouse(&x1,&y1,&but);
    UD.get_mouse(&x1,&y1,&num1,num_char1);
    delay(200);

    do
    {
      UD.ReadMouse(&x1,&y1,&but);
      if(bioskey(1))
	UD.get_key(&num1,num_char1);
    }
    while(!(but&1));

  }
  while(1);
}
