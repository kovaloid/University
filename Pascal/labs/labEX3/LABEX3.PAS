program labEX3;
type sled=^S1;
     S1=record
      number:integer;
      name:array[1..15] of char;
      next,prev:sled;
     end;
var input1,output1:text;
    Start1,Last1:sled;
    str1:integer;
procedure P1 (var input:text; var Start:sled);
 var i,code:integer;
     NumStr:string[2];
     R,Last:sled;
 begin
  new(Start);
  R:=Start;
  Last:=nil;
  while not eof(input) do
   begin
    new(R^.next);
    R^.prev:=Last;
    Last:=R;
    R:=R^.next;
    read(input,NumStr);
    val(NumStr,R^.number,code);
    for i:=1 to 15 do
     read(input,R^.name[i]);
   end;
  R^.next:=nil;
  R^.prev:=Last;
 end;
procedure P2 (Start:sled);
 var n,temp:integer;
     k:char;
     S,R:sled;
 begin
   R:=Start;
   S:=Start;
   S:=S^.next^.next;
   R:=R^.next;
   while R^.next<>nil do
    begin
     R:=R^.next;
     S:=R;
     temp:=S^.number;
     while (S^.prev^.prev<>nil) and (S^.prev^.number<temp) do
      begin
       S^.number:=S^.prev^.number;
       for n:=1 to 15 do
        begin
         k:=S^.name[n];
         S^.name[n]:=S^.prev^.name[n];
         S^.prev^.name[n]:=k;
        end;
       S:=S^.prev;
      end;
     S^.number:=temp;
    end;
 end;
procedure P3 (var output:text; Start:sled);
 var i:integer;
     R:sled;
 begin
  R:=Start;
  R:=R^.next;
  while R<>nil do
   begin
    write(output,R^.number);
    for i:=1 to 15 do
     write(output,R^.name[i]);
    R:=R^.next;
   end;
  writeln(output);
  writeln(output);
  writeln(output);
 end;
begin
 assign(input1,'F1.txt'); reset(input1);
 assign(output1,'output.txt'); rewrite(output1);
  P1(input1,Start1);
  P3(output1,Start1);
  P2(Start1);
  P3(output1,Start1);
 close(input1); close(output1);
 readln;
end.