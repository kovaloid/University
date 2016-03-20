#include <conio.h>
#include <iostream.h>
#include <dos.h>
#define INT_NUM 0x75

void interrupt (*old)(...);
void interrupt int_func(...)
{
  cout<<"FPU error\n";
  old();
  asm mov ax,[bp+18];
  asm add ax,20;
  asm mov [bp+18],ax;
}


void main()
{
  clrscr();

  old=getvect(INT_NUM);
  disable();
  setvect(INT_NUM,int_func);
  enable();

  float a;
  clrscr();
  cout << "enter number:\n";
  cin >> a;

  asm finit
  asm fld a
  int flags=894; // 11_0111_1110
  asm fldcw flags
  asm fsqrt
  asm fstp a

  cout << "sqrt: " << a;
  getch();
  setvect(INT_NUM,old);
}


