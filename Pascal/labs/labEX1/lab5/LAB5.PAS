program lab5;
type sled=^item;
     item=record
      name:string[15];
      price:integer;
      next:sled;
     end;
var input1,output1:text;
    k:sled;
procedure ReadData (var Start:sled; var input,output:text);
 var R:sled;
 begin
  writeln(output,'Name           Price');
  writeln(output,'----------------------');
  new(Start);
  readln(input,Start^.name,Start^.price);
  writeln(output,Start^.name,Start^.price,' rub.');
  R:=Start;
  while not eof(input) do
   begin
    new(R^.next);
    R:=R^.next;
    readln(input,R^.name,R^.price);
    writeln(output,R^.name,R^.price,' rub.');
   end;
  R^.next:=nil;
  writeln(output); writeln(output);
  writeln(output,'The most expensive items:');
  writeln(output,'-------------------------');
 end;
procedure findmax (Start:sled; var output:text);
 var i:integer;
     F,L,Max:sled;
 begin
 for i:=1 to 3 do
  begin
   F:=Start;
   Max:=F;
    while F<>nil do
     begin
      if Max^.price < F^.price then Max:=F;
      F:=F^.next;
     end;
    writeln(output,i,'. ',Max^.name,Max^.price,' rub.');
    F:=Max;
    F^.price:=0;
  end;
 end;
begin
 assign(input1,'input.txt'); reset(input1);
 assign(output1,'output.txt'); rewrite(output1);
  readdata(k,input1,output1);
  findmax(k,output1);
 close(input1); close(output1);
 readln;
end.