program lab6;
type mas=array[1..10] of string[25];
var A:mas;
    input,output:text;
    i:integer;
procedure findmax (x:integer; r1:integer; var A1:mas; var output1:text);
 var i,k,j,code,max:integer;
     p:string;
 begin
 p:=copy(A1[1],17,4);
 val(p,max,code);
 for i:=1 to 10 do
  begin
   p:=copy(A1[i],17,4);
   val(p,k,code);
   if k>=max then
    begin
     max:=k;
     j:=i;
    end;
  end;
 delete(A1[j],17,4);
 insert('0000',A1[j],17);
 writeln(output1,r1,'. ',copy(A1[j],1,16),max,' rub.');
 if r1<>3 then
  begin
   r1:=r1+1;
   findmax(x,r1,A1,output1);
  end;
 end;
begin
 assign(input,'input.txt'); reset(input);
 assign(output,'output.txt'); rewrite(output);
 writeln(output,'Name            Price');
 writeln(output,'----------------------');
 for i:=1 to 10 do
  begin
   readln(input,A[i]);
   writeln(output,A[i]);
  end;
 close(input);
 writeln(output); writeln(output);
 writeln(output,'The most expensive items:');
 writeln(output,'-------------------------');
 findmax(3,1,A,output);
 close(output);
 readln;
end.