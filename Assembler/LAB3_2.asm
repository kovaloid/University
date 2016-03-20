DOSSEG
.MODEL TINY
.STACK 100h
.DATA
A DW 0,1,22,333,44,5,66,777,88,9
B DW 10 DUP(0)
n DB 10,13,'$'
.CODE

mov ax,@Data
mov ds,ax 
mov es,ax

cld
lea si,A
lea di,B
mov cx,10
rep movsw                         
           
mov si,0           
mov cx,10              
                     
out_put:
    mov ax,B[si]     	
    push 'Q' 
    mov	bx,10      	
  met1: 
    mov	dx,0       
    div	bx ;в ah записывается остаток от деления ax на bx, в al записывается частное от деления ax на bx 
    push dx         	
    cmp	ax,0       
    jne	met1         	   
  met2: 
    pop	dx	
    cmp	dx,'Q'     
    je next_sym  
    mov	ah,2h          
    add	dl,30h ;вместо 30h можно 48 или код символа '0'	
    int	21h       	
    jmp	met2
  next_sym:		
    mov dx,' '    
    int 21h
    add si,2
loop out_put
 
mov dx,OFFSET n
mov ah,9
int 21h
               
mov ah,4ch  
int 21h
    
END