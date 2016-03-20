#include <iostream.h>
#include <conio.h>
#include <dos.h>

void main()
{
  clrscr();
  cout<<"standart settings:\n";
  cout<<"Typematic Rate Delay - 500 msec\n";
  cout<<"Typematic Rate - 10 chars/sec\n";
  cout<<"change settings:\n";
  cout<<"Typematic Rate Delay - 250 msec\n";
  cout<<"Typematic Rate - 30 chars/sec\n";

  asm mov al,0xF3
  asm out 0x60,al
  delay(100);
  asm mov al,0x00
  asm out 0x60,al

  cout<<"try to type:\n";
  char tmp;
  cin>>tmp;
  getch();
}
