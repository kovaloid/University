program labEX2;
label go1,go2;
type sled=^item;
     item=record
      elem:string;
      next:sled;
      prev:sled;
     end;
var input1,output1:text;
    Start1,Last1:sled;
    NumStr,str:integer;
    NameProc,error1,error2:string;
procedure ReadData (var Start:sled; var Last:sled; var input,output:text);
 var R:sled;
 begin
  new(Start);
  R:=Start;
  Last:=nil;
  str:=0;
  while not eof(input) do
   begin
    new(R^.next);
    R^.prev:=Last;
    Last:=R;
    R:=R^.next;
    readln(input,R^.elem);
    inc(str);
   end;
  R^.next:=nil;
 end;
procedure TOP (Start:sled; N:integer; var output:text);
 var i:integer;
     F:sled;
 begin
  F:=Start;
  F:=F^.next;
  writeln(output,'------------------------');
  for i:=1 to N do
   begin
    writeln(F^.elem);
    writeln(output,F^.elem);
    F:=F^.next;
   end;
  writeln(output,'------------------------');
 end;
procedure BOT (Last:sled; N:integer; var output:text);
 var i:integer;
     F:sled;
 begin
  F:=Last;
  for i:=1 to N-1 do
   begin
    F:=F^.prev;
   end;
  writeln(output,'------------------------');
  for i:=1 to N do
   begin
    writeln(F^.next^.elem);
    writeln(output,F^.next^.elem);
    F:=F^.next;
   end;
  writeln(output,'------------------------');
 end;
begin
 assign(input1,'input.txt'); reset(input1);
 assign(output1,'output.txt'); rewrite(output1);
  readdata(Start1,Last1,input1,output1);
 go1:
  writeln('------------------------');
  writeln('Enter name of procedure:');
  readln(NameProc);
  writeln(output1,'Procedure: ',NameProc);
 go2:
  writeln('------------------------');
  writeln('Enter number of strings:');
  readln(NumStr);
  writeln(output1,'Strings: ',NumStr);
  writeln('------------------------');
 error1:='1. Uncorrect name of procedure, use /top/ or /bot/';
 error2:='2. Uncorrect number of strings, use number >=0 and <=';
 if (NameProc<>'top') and (NameProc<>'bot') and (NumStr>str) or (NumStr<0) then
  begin
   writeln(error1);
   writeln(error2,str);
   writeln(output1,error1);
   writeln(output1,error2,str);
   goto go1
  end
 else
  if (NameProc<>'top') and (NameProc<>'bot') then
   begin
    writeln(error1);
    writeln(output1,error1);
    goto go1
   end
  else
   if (NumStr>str) or (NumStr<0) then
    begin
     writeln(error2,str);
     writeln(output1,error2,str);
     goto go2
    end
   else
    if NameProc='bot' then bot(Last1,NumStr,output1)
    else
     if NameProc='top' then top(Start1,NumStr,output1);
  writeln('------------------------');
  writeln('Enter to exit...');
 close(input1); close(output1);
 readln;
end.