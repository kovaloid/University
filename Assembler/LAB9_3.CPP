#include <stdio.h>
#include <conio.h>
#include <dos.h>
#define Port8042 0x60

long far * pTime=(long far*)0x46C;
int far * pHeadPtr=(int far*)0x41A;
int far * pTailPtr=(int far*)0x41C;
unsigned char far * pBuf;

void main()
{
  clrscr();
  printf("CapsLock: 'q'-on, 'a'-off;\n");
  printf("NumLock: 'w'-on, 's'-off;\n");
  printf("ScrollLock: 'e'-on, 'd'-off;\n");
  printf("to exit press SPACEKEY\n");
  char cAsci;

  do
  {
    asm push ds 	
    asm push si         
    asm push di         
    asm mov ax,0x40     
    asm mov ds,ax       
    asm mov si,0x1A     
    asm mov di,0x1C     
  wait_kbd:
    asm mov ax,[si]     
    asm cmp ax,[di]     
    asm je wait_kbd
    asm mov si,[si]
    asm mov ax,[si]
    asm pop di
    asm pop si
    asm pop ds
    cAsci = _AL;

    if (cAsci==0x71) //q
    {
      asm mov al,0xED
      asm out 0x60,al
      delay(100);
      asm or al,100b
      asm out 0x60,al
      printf("CapsLock on!\n");
    }
    else if (cAsci==0x61) //a
    {
      asm mov al,0xED
      asm out 0x60,al
      delay(100);
      asm and al,011b
      asm out 0x60,al
      printf("CapsLock off!\n");
    }
    else if (cAsci==0x77) //w
    {
      asm mov al,0xED
      asm out 0x60,al
      delay(100);
      asm or al,010b
      asm out 0x60,al
      printf("NumLock on!\n");
    }
    else if (cAsci==0x73) //s
    {
      asm mov al,0xED
      asm out 0x60,al
      delay(100);
      asm and al,101b
      asm out 0x60,al
      printf("NumLock off!\n");
    }
    else if (cAsci==0x65) //e
    {
      asm mov al,0xED
      asm out 0x60,al
      delay(100);
      asm or al,001b
      asm out 0x60,al
      printf("ScrollLock on!\n");
    }
    else if (cAsci==0x64) //d
    {
      asm mov al,0xED
      asm out 0x60,al
      delay(100);
      asm and al,110b
      asm out 0x60,al
      printf("ScrollLock off!\n");
    }
    else printf("error\n");
  } 
  while(getch()!=32);
  printf("\npress any key...\n");
  getch();
}
