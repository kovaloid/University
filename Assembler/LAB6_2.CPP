#include <conio.h>
#include <stdio.h>
#include <iostream.h>
#include <dos.h>
#define INT_NUM 0x00

long a, b;
int c;

void interrupt (*old)(...);
void interrupt int_func(...)
{
  asm mov ax,[di];
  asm mov dx,[si];

//-------- cmp high digits ---------

  asm cmp ax,dx;
  asm jz cmp_low_digits;
  asm ja high_upper;
                   //------ < ------
  asm mov cx,1;
  asm mov [si],cx;
  asm jmp endpr;

high_upper:        //------ > ------
  asm mov cx,3;
  asm mov [si],cx;
  asm jmp endpr;

//--------- cmp low digits ----------

cmp_low_digits: 
  asm mov ax,[di+2];
  asm mov dx,[si+2];
  asm cmp ax,dx;
  asm jz low_eq;
  asm ja low_upper;
                   //------ < ------
  asm mov cx,1;
  asm mov [si],cx;
  asm jmp endpr;

low_eq:            //------ = ------
  asm mov cx,2;
  asm mov [si],cx;
  asm jmp endpr;

low_upper:         //------ > ------
  asm mov cx,3;
  asm mov [si],cx;

endpr:

  asm mov ax,[bp+18];
  asm add ax,2;
  asm mov [bp+18],ax;
}


void main()
{
  clrscr();
  int i=1;

  cout << "enter first number:\n";
  cin >> a;
  cout << "enter second number:\n";
  cin >> b;
  clrscr();
  cout << "source:\n";
  cout << "a: " << a << "\nb: " << b;

    asm lea di, a;
    asm lea si, b;

  old=getvect(INT_NUM);
  disable();
  setvect(INT_NUM,int_func);
  enable();
  i=i/0;

  cout << "\nresult:\n";
  if (b == 1) cout << " a < b";
  else if (b == 2) cout << " a = b";
  else if (b == 3) cout << " a > b";
  else cout << "error";
  getch();


  setvect(INT_NUM,old);
}


