#include <stdio.h>
#include <dos.h>
#include <conio.h>

void interrupt (*old)(...);
void interrupt debugger(...)
{
  printf("ax = %x\n", _AX);
  getch();
};


void func()
{
  asm xor ax,ax
  asm mov cx,10
M1:
  asm add ax,1
  asm int 3
  asm loop M1
}


void main()
{
  clrscr();
  void* ip_func = func;
  disable();
  setvect(0x3,debugger);
  enable();

  asm pushf
  asm pop dx
  asm or dx, 100h //100000000b
  asm push dx
  asm push cs
  asm push ip_func
  asm iret
}