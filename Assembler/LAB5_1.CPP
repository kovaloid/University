#include <iostream.h>
#include <conio.h>

void comparator(long a, long b, int &c)
{
  asm mov ax,[bp+4];
  asm mov dx,[bp+8];
  asm mov si,[bp+12];

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
  asm mov ax,[bp+6];
  asm mov dx,[bp+10];
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
  asm jmp endpr

low_upper:         //------ > ------
  asm mov cx,3;
  asm mov [si],cx;

endpr:
}


void main()
{
  clrscr();
  long a, b;
  int c;

  cout << "enter first number:\n";
  cin >> a;
  cout << "enter second number:\n";
  cin >> b;
  clrscr();
  cout << "source:\n";
  cout << "a: " << a << "\nb: " << b;
  comparator(a, b, c);
  cout << "\nresult:\n";

  if (c == 1) cout << " a < b";
  else if (c == 2) cout << " a = b";
  else if (c == 3) cout << " a > b";
  else cout << "error";

  getch();
}