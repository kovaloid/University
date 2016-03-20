DOSSEG
.MODEL tiny
.386
.STACK 100h
.DATA

 context_struct struc ;��������� ��� �������� ���������
   rax  DW  ?       
   rbx  DW  ?       
   rcx  DW  ?       
   rdx  DW  ?       
   rds  DW  ?       
   res  DW  ?       
 context_struct ends 
   
 context1 context_struct <> ;�������� 1-� ������
 context2 context_struct <> ;�������� 2-� ������
 context3 context_struct <> ;�������� 3-� ������
  
 p1  DW  3 ;��������� 1-� ������
 p2  DW  2 ;��������� 2-� ������
 p3  DW  1 ;��������� 3-� ������
   
 handling_number  DW  32 ;���������� ���������
 msg DB 'Press any key to change procedure',10,13,'$'
 
ORG 100h ;����������� �������� ����������� ������ �� 256

 old_handler  DD  0 ;������ ������
    
.CODE
 
proc1 proc
    ;��������� �������� �� ���������
    mov ax, context1.rax
    mov bx, context1.rbx
    mov cx, context1.rcx   
    mov dx, context1.rdx
    mov ds, context1.rds
    mov es, context1.res 
      
    mov al,'1' ;��� ������ '1' � ������� int 29h
      
    ;����� ������ ��������� �������� � ��������
    mov context1.rax, ax
    mov context1.rbx, bx
    mov context1.rcx, cx   
    mov context1.rdx, dx
    mov context1.rds, ds
    mov context1.res, es
ret
proc1 endp 

proc2 proc
    ;��������� �������� �� ���������
    mov ax, context2.rax
    mov bx, context2.rbx
    mov cx, context2.rcx   
    mov dx, context2.rdx
    mov ds, context2.rds
    mov es, context2.res 
      
    mov al,'2' ;��� ������ '2' � ������� int 29h
      
    ;����� ������ ��������� �������� � ��������
    mov context2.rax, ax
    mov context2.rbx, bx
    mov context2.rcx, cx   
    mov context2.rdx, dx
    mov context2.rds, ds
    mov context2.res, es 
ret
proc2 endp 

proc3 proc
    ;��������� �������� �� ���������
    mov ax, context3.rax
    mov bx, context3.rbx
    mov cx, context3.rcx   
    mov dx, context3.rdx
    mov ds, context3.rds
    mov es, context3.res
      
    mov al,'3' ;��� ������ '3' � ������� int 29h
      
    ;����� ������ ��������� �������� � ��������
    mov context3.rax, ax
    mov context3.rbx, bx
    mov context3.rcx, cx   
    mov context3.rdx, dx
    mov context3.rds, ds
    mov context3.res, es
ret
proc3 endp 
     
new_handler proc far
;�������� ����������� ������������
                      
;���� ��������� 1-� ������ ����� 0, �� ������������� ����������� ��������
    mov di,p1
    cmp di,0
    jne again              
    mov di,3
    mov p1,di
    mov di,2
    mov p2,di
    mov di,1
    mov p3,di              

;������� ������ � ���������� �����������
again:                                                               
    mov si,p1 
    mov di,p2 
    cmp si,di
    jb m1
      ;p1 > p2 
      mov dx,si
      jmp m2             
    m1:          
      ;p1 < p2 
      mov dx,di
    m2:                
      mov si,p3
      cmp si,dx
      jb m3
        ;p3 > (p1|p2)
        mov dx,si         
      m3:
        ;p3 < (p1|p2)
          
;����� ������ ������ ��������� �� ��������� �� 1
    cmp dx,si
      je l3
    cmp dx,di
      je l2
    mov si,p1 
    cmp dx,si
      je l1
           
    l1: mov si,1
        mov di,p1
        dec di 
        mov p1,di              
        jmp l4
    l2: mov si,2
        mov di,p2
        dec di
        mov p2,di
        jmp l4
    l3: mov si,3
        mov di,p3           
        dec di
        mov p3,di   
    l4:
              
;����� ����� handling_number ���������                
    mov cx,handling_number                          
    dec cx              
    mov handling_number,cx
    cmp cx,0
      jl exit ;<                
                 	
repeat:
;��������� ��������� � ��������� �����������
    pusha ;��������� � ���� �������� ������ ����������   
    cmp si,1
      je t1
    cmp si,2
      je t2
    cmp si,3
      je t3
      
    t1: call proc1
        jmp print_task
    t2: call proc2
   	jmp print_task
    t3: call proc3    
                  	
print_task:
;����� ����� 'task'                
    push ax          
    mov al,'t'
    int 29h
    mov al,'a'
    int 29h
    mov al,'s'
    int 29h
    mov al,'k'
    int 29h
    mov al,' '
    int 29h      
    pop ax
                
    int 29h ;����� '1', '2' ��� '3' �� �������� al   
    mov al,10 ;������� ������
    int 29h      
    popa ;��������� �� ����� �������� ������ ����������
    
;����� ����������� ����������                
    mov al,20h 
    out 20h,al
       
;�������� ������ �� �������		
    mov ah,1              
    int 16h          
    jz repeat ;���������, ���� �� ������
                
iret
new_handler endp

main:
;����� �������������� ��������       
    mov dx,offset msg
    add dx,100h
    mov ah,9
    int 21h     
    
;�������� ������� ������ ���������� � ������� int 21h 
;����: AH = 35h, AL = ����� ������� ����������
;�����: ES:BX = ����� ��������� ��������� ����������
;� BX ��������� ���������� ������ 0:(4*AL), � ES - 0:(4*AL+2) 
    mov ah,35h
    mov al,09h
    int 21h               
    mov word ptr old_handler+2,es
    mov word ptr old_handler,bx
                   
;��������� ����� ������ ���������� � ������� int 21h 
;����: AH = 25H, AL = ����� ���������� (�� ���������� 09h)
;DS:DX = ������ ����������: ����� ��������� ��������� ����������  
    push cs
    pop ds
    mov dx,offset new_handler    
    mov ah,25h
    mov al,09h
    int 21h    
 
;��������� �������� �� ��� ���������
    mov context1.rax, ax
    mov context1.rbx, bx
    mov context1.rcx, cx   
    mov context1.rdx, dx
    mov context1.rds, ds
    mov context1.res, es

    mov context2.rax, ax
    mov context2.rbx, bx
    mov context2.rcx, cx   
    mov context2.rdx, dx
    mov context2.rds, ds
    mov context2.res, es
	
    mov context3.rax, ax
    mov context3.rbx, bx
    mov context3.rcx, cx   
    mov context3.rdx, dx
    mov context3.rds, ds
    mov context3.res, es
                
    infinity: jmp infinity ;����������� ����
       
exit:
;��������� � ������� ����������� ���������� (���������� DS:DX �� old) 
    lds dx,old_handler 
    mov ah,25h ;������� ���������� �������
    mov al,09h ;����� �������
    int 21h
    
    mov	ah,4ch ;������� DOS ���������� ���������
    int	21h ;��������� ���������

END main
