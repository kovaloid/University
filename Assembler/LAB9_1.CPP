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
  char Scan_Code, Ascii_Code;
  int Addr;
  char stat1, stat2;

  do
  {
    asm push ds 	
    asm push si         
    asm push di         
    asm mov ax,0x40     
    asm mov ds,ax       
    asm mov si,0x1A     
    asm mov di,0x1C
  wait_met:
    asm mov ax,[si]     
    asm cmp ax,[di]     
    asm je wait_met
    asm mov bx,0x17
    asm mov bx,[bx]
    stat1 = _BX;
    asm mov bx,0x18
    asm mov bx,[bx]
    stat2 = _BX;
    asm mov si,[si]
    Addr = _SI;
    asm mov ax,[si]
    asm pop di
    asm pop si
    asm pop ds
    Scan_Code = _AH;
    Ascii_Code = _AL;
    printf("scan = %d   ascii = %d   address = %x   stat1 = %x   stat2 = %x \n",Scan_Code,Ascii_Code,Addr,stat1,stat2);
  }
  while(getch()!=27);
  getch();

met:
  delay(1000);
  asm in al,0x60
  Scan_Code = _AL;
  if (Scan_Code == 1) goto ex;
  printf("scan = %x \n",Scan_Code);
  goto met;
ex:
  getch();
}
