program lab3;
type
item=record
 name:string[15];
 price:integer;
end;
mass=array [1..10] of item;
var
 input,output:text;
 typefile:file of item;
 A:mass;
 i:integer;
procedure line (n:integer);
 var i:integer;
 begin
  for i:=1 to n do
   write('-');
  writeln;
 end;
procedure findmax (x:integer; var A:mass);
 var i,k,r,j,max:integer;
 begin
  for r:=1 to x do
   begin
    max:=A[1].price;
    for i:=1 to 10 do
     begin
      k:=A[i].price;
      if k>=max then
       begin
        max:=k;
        j:=i;
       end;
     end;
    A[j].price:=0;
    writeln(r,'. ',A[j].name,max,' руб.');
    writeln(output,r,'. ',A[j].name,max,' rub.');
   end;
 end;
begin
 assign(input,'input.txt');
 reset(input);
 for i:=1 to 10 do begin
  readln(input,A[i].name,A[i].price);
 end;
 close(input);

 assign(output,'output.txt');
 rewrite(output);
 writeln(output,'Name            Price');
 writeln(output,'---------------------');
 for i:=1 to 10 do begin
  writeln(output,A[i].name,' ',A[i].price);
 end;
 writeln(output); writeln(output);
 writeln(output,'The most expensive items:');
 writeln(output,'-------------------------');

 assign(typefile,'type.tpf');
 rewrite(typefile);
 for i:=1 to 10 do begin
  write(typefile,A[i]);
 end;
 close(typefile);

 assign(typefile,'type.tpf');
 reset(typefile);
 for i:=1 to 10 do begin
  read(typefile,A[i]);
 end;
 close(typefile);


 writeln('Товар           Цена');
 line(20);
 for i:=1 to 10 do begin
  writeln(A[i].name,' ',A[i].price,' rub.');
 end;
 writeln; writeln;
 writeln('Самые дорогие вещи:');
 line(25);
 findmax(3,A);

 close(output);
 readln;
end.