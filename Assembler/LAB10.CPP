#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>

void procedure1()
{
  while(1)
  {
    printf("procedure 1\n");
    delay(500);
  }
}

void procedure2()
{
  while(1)
  {
    printf("procedure 2\n");
    delay(500);
  }
}

void procedure3()
{
  while(1)
  {
    printf("procedure 3\n");
    delay(500);
  }
}

struct context
{
  unsigned int rax, rbx, rcx, rdx;
  unsigned int rsi, rdi, rbp, rsp;
  unsigned int rcs, rds, res, rss;
  unsigned int rflags, rip, a, b;
} context_array[3];

typedef void (*ptr_func)();
ptr_func function_addr_array[3] = {procedure1, procedure2, procedure3};
int current_procedure_id = -1;
int key_state = 1;

void interrupt (*old_handler)(...);
void interrupt SwitchProcedures(...)
{
  int prev_procedure_id = current_procedure_id;

//save registers
  context_array[prev_procedure_id].rax = _AX;
  context_array[prev_procedure_id].rbx = _BX;
  context_array[prev_procedure_id].rcx = _CX;
  context_array[prev_procedure_id].rdx = _DX;
  context_array[prev_procedure_id].rsi = _SI;
  context_array[prev_procedure_id].rdi = _DI;
  context_array[prev_procedure_id].rbp = _BP;
  context_array[prev_procedure_id].rsp = _SP;
  context_array[prev_procedure_id].rcs = _CS;
  context_array[prev_procedure_id].rds = _DS;
  context_array[prev_procedure_id].res = _ES;
  context_array[prev_procedure_id].rss = _SS;
  context_array[prev_procedure_id].rflags = _FLAGS;

  old_handler();
  key_state = -key_state;
  if (key_state > 0)
  {
    current_procedure_id++;
    if (current_procedure_id > 2)
      current_procedure_id = 0;

//load registers
    int reg;
    reg = context_array[current_procedure_id].rax;
    asm mov ax, reg
    reg = context_array[current_procedure_id].rbx;
    asm mov bx, reg
    reg = context_array[current_procedure_id].rcx;
    asm mov cx, reg
    reg = context_array[current_procedure_id].rdx;
    asm mov dx, reg
    reg = context_array[current_procedure_id].rsi;
    asm mov si, reg
    reg = context_array[current_procedure_id].rdi;
    asm mov di, reg
    reg = context_array[current_procedure_id].rsp;
    asm mov sp, reg
    reg = context_array[current_procedure_id].rbp;
    asm mov bp, reg
    /*reg = context_array[current_procedure_id].rcs;
    asm mov cs, reg	
    reg = context_array[current_procedure_id].res;
    asm mov es, reg
    reg = context_array[current_procedure_id].rds;
    asm mov ds, reg
    reg = context_array[current_procedure_id].rss;
    asm mov ss, reg*/

    int tmp = current_procedure_id * 2;
    asm lea bx, function_addr_array
    asm add bx, tmp
    asm mov ax, [bx]

    asm push ax
    asm push cs
    asm push ax
    asm iret
  }
}


void main()
{
  clrscr();
  printf("press any key to change procedure\n");
  printf("CTRL + BREAK to exit programm\n");
  for (int i = 0; i < 3; i++)
    memset(&context_array, 0, sizeof(context));

  disable();
  old_handler = getvect(0x9);
  setvect(0x9, SwitchProcedures);
  enable();

  while(1);
}

