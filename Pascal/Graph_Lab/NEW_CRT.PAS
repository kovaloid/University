unit New_Crt;

	INTERFACE

const
  BW40		= 0;
  CO40		= 1;
  BW80		= 2;
  CO80		= 3;
  C40		= CO40;
  C80		= CO80;

  Black		= 0;
  Blue		= 1;
  Green		= 2;
  Cyan		= 3;
  Red		= 4;
  Magenta	= 5;
  Brown		= 6;
  LightGray	= 7;
  DarkGray	= 8;
  LightBlue	= 9;
  LightGreen	= 10;
  LightCyan	= 11;
  LightRed	= 12;
  LightMagenta	= 13;
  Yellow	= 14;
  White		= 15;
  Blink		= 128;

  TextAttr : Byte = 7;
  LastMode : Word = C80;

procedure Crt_Init;
function KeyPressed: Boolean;
function ReadKey: Char;
procedure TextMode(Mode: Integer);
procedure GotoXY(X,Y: Byte);
function WhereX: Byte;
function WhereY: Byte;
procedure ClrScr;
procedure ClrEol;
procedure InsLine;
procedure DelLine;
procedure TextColor(Color: Byte);
procedure TextBackground(Color: Byte);
procedure LowVideo;
procedure HighVideo;
procedure NormVideo;
procedure Delay(MS: Word);
procedure Sound(Hz: Word);
procedure NoSound;

	IMPLEMENTATION

uses Dos;

const
  DelayCnt : LongInt = 0;
  ScanCode : Byte = 0;

procedure WriteChar(Cr : string); assembler;
asm
	push	bp
	mov	ah,3
	xor	bh,bh
	int	10h
	mov	ax,1301h
	xor	bh,bh
	les	bp,Cr
	mov	bl,TextAttr
	mov	cx,1
	inc	bp
	int	10h
	pop	bp
end;

function Zero(var F : TextRec) : Integer; far; assembler;
asm
	xor	ax,ax
end;

function PageWrite(var F : TextRec) : Integer; far;
var k : Integer;
begin
  with F do if (Mode=fmOutput) and (BufPos>0) then
  begin
    for k:=0 to BufPos-1 do WriteChar(BufPtr^[k]);
    BufPos:=0
  end;
  PageWrite:=0
end;

procedure DelayLoop; near; assembler;
asm
@1:	sub	ax,1
	sbb	dx,0
	jc	@2
	cmp	bl,es:[di]
	je	@1
@2:
end;

procedure Delay(MS: Word); assembler;
type
  LongRec = record
    Lo, Hi : Word
  end;
asm
	mov	es,Seg0040
	mov	ax,DelayCnt.LongRec.Lo
	add	ax,DelayCnt.LongRec.Hi
	or	ax,ax
	jne	@2
	mov	di,$6c
	mov	bl,es:[di]
@1:	cmp	bl,es:[di]
	je	@1
	mov	bl,es:[di]
	mov	ax,-28
	cwd
	call	DelayLoop
	not	ax
	not	dx
	mov	bx,ax
	mov	ax,dx
	xor	dx,dx
	mov	cx,55
	div	cx
	mov	DelayCnt.LongRec.Hi,ax
	mov	ax,bx
	div	cx
	mov	DelayCnt.LongRec.Lo,ax
@2:	mov	cx,MS
	jcxz	@3
	xor	di,di
	mov	bl,es:[di]
@4:	mov	ax,DelayCnt.LongRec.Lo
	mov	dx,DelayCnt.LongRec.Hi
	call	DelayLoop
	loop	@4
@3:
end;

procedure Sound(Hz: Word); assembler;
asm
	mov	bx,Hz
	mov	ax,34ddh
	mov	dx,0012h
	cmp	dx,bx
	jnc	@@2
	div	bx
	mov	bx,ax
	in	al,61h
	test	al,3
	jnz	@@1
	or	al,3
	out	61h,al
	mov	al,0b6h
	out	43h,al
@@1:	mov	al,bl
	out	42h,al
	mov	al,bh
	out	42h,al
@@2:
end;

procedure NoSound; assembler;
asm
	in	al,61h
	and	al,0fch
	out	61h,al
end;

function KeyPressed: Boolean; assembler;
asm
	cmp	ScanCode,0
	jne	@@1
	mov	ah,1
	int	16h
	mov	al,0
	je	@@2
@@1:	mov	al,1
@@2:
end;

function ReadKey: Char; assembler;
asm
	mov	al,ScanCode
	mov	ScanCode,0
	or	al,al
	jne	@@1
	xor	ah,ah
	int	16h
	or	al,al
	jne	@@1
	mov	ScanCode,ah
	or	ah,ah
	jne	@@1
	mov	al,3
@@1:
end;

procedure TextColor(Color: Byte); assembler;
asm
	mov	al,Color
	test	al,0f0h
	je	@@1
	and	al,0fh
	or	al,80h
@@1:	and	TextAttr,70h
	or	TextAttr,al
end;

procedure TextMode(Mode: Integer); assembler;
asm
	xor	ah,ah
	mov	al,byte ptr Mode
	mov	LastMode,ax
	int	10h
end;

procedure TextBackground(Color: Byte); assembler;
asm
	mov	al,Color
	and	al,7
	mov	cl,4
	shl	al,cl
	and	TextAttr,8fh
	or	TextAttr,al
end;

procedure GotoXY(X,Y: Byte); assembler;
asm
	mov	ah,2
	xor	bh,bh
	mov	dl,x
	mov	dh,y
	dec	dl
	dec	dh
	int	10h
end;

procedure ClrEol; assembler;
asm
	mov	ah,3
	xor	bh,bh
	int	10h
	mov	ax,600h
	mov	cx,dx
	mov	es,Seg0040
	mov	dl,es:[$4a]
	dec	dl
	mov	bh,TextAttr
	int	10h
end;

function WhereX: Byte; assembler;
asm
	mov	ah,3
	xor	bh,bh
	int	10h
	mov	al,dl
	inc	al
end;

function WhereY: Byte;  assembler;
asm
	mov	ah,3
	xor	bh,bh
	int	10h
	mov	al,dh
	inc	al
end;

procedure ClrScr; assembler;
asm
	mov	ax,600h
	mov	bh,TextAttr
	xor	cx,cx
	mov	dx,184fh
	int	10h
	mov	ah,2
	xor	bh,bh
	xor	dx,dx
	int	10h
end;

procedure InsLine; assembler;
asm
	mov	ah,3
	xor	bh,bh
	int	10h
	mov	bh,TextAttr
	mov	ch,dh
	xor	cl,cl
	mov	es,Seg0040
	mov	al,es:[$4a]
	xor	ah,ah
	mov	dx,24*256-1
	add	dx,ax
	mov	ax,7*256+1
	cmp	ch,dh
	jne	@@1
	xor	al,al
@@1:	int	10h
end;

procedure DelLine; assembler;
asm
	mov	ah,3
	xor	bh,bh
	int	10h
	mov	bh,TextAttr
	mov	ch,dh
	xor	cl,cl
	mov	es,Seg0040
	mov	al,es:[$4a]
	xor	ah,ah
	mov	dx,24*256-1
	add	dx,ax
	mov	ax,6*256+1
	cmp	ch,dh
	jne	@@1
	xor	al,al
@@1:	int	10h
end;

procedure LowVideo; assembler;
asm
	and	TextAttr,0f7h
end;

procedure HighVideo; assembler;
asm
	or	TextAttr,8
end;

procedure NormVideo; assembler;
asm
	mov	TextAttr,7
end;

procedure Crt_Init;
begin
  with TextRec(Output) do
  begin
    OpenFunc:=@Zero; CloseFunc:=@Zero;
    InOutFunc:=@PageWrite; FlushFunc:=@PageWrite
  end
end;

end { New_Crt }.