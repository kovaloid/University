#include <iostream.h>
#include <conio.h>
#include <dos.h>

void main()
{
  clrscr();

  //asm in al,0x61
  //asm or al,0x80
  //asm out 0x61,al

  cout<<"press any key to block keyboard\n";
  getch();
  asm mov al,0xAD
  asm out 0x64,al
  cout<<"wait 3 seconds...\n";
  delay(3000);
  asm mov al,0xAE
  asm out 0x64,al
  char tmp;
  cin>>tmp;
  cout<<"your keyboard is unblocked\n";
  getch();
}
