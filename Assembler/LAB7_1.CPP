#include <iostream.h>
#include <conio.h>
#include <float.h>

void main()
{
  float a, b, c;
  clrscr();
  cout << "enter 3 number:\n";
  cin >> a >> b >> c;

  asm finit

  asm fld a
  asm fld b
  asm fadd
  asm fstp a

  asm fld a
  asm fld c
  asm fadd 
  asm fstp a

  cout << "sum: " << a;
  getch();
}