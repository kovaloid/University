DOSSEG
.MODEL TINY
.STACK 100h
.DATA
A DB 0,1,2,3,4,5,6,7,8,9
B DB 10 DUP(0)
n DB 10,13,'$'
.CODE

mov ax,@Data ;���������� �������� DS � ES ����� �������, ����� �� �������� �� ������� ������
mov ds,ax
mov es,ax

cld
lea si,A
lea di,B
mov cx,10
rep movsb

lea di,B

mov cx,10
metka:
  mov dx,[di]
  mov ah,2 ;������� ����������� ������� �� ������
  add dl,30h ;������ �� ������
  int 21h ;������� ������ �� �����
  inc di
loop metka

mov dx,OFFSET n
mov ah,9
int 21h

mov ah,4ch ;������� DOS ���������� ���������
int 21h ;��������� ���������

END