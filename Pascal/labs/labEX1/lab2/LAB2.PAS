program lab2;
uses crt;
type mas=array[1..10] of string[25];
var a:mas;
    f,s:text;
    i,num:integer;
procedure line (n:integer);
 var i:integer;
 begin
  for i:=1 to n do
   write('-');
  writeln;
 end;
procedure findmax (x:integer; var a:mas);
 var i,k,r,j,code,max:integer;
     p:string;
 begin
  for r:=1 to x do
   begin
    p:=copy(a[1],17,4);
    val(p,max,code);
    for i:=1 to 10 do
     begin
      p:=copy(a[i],17,4);
      val(p,k,code);
      if k>=max then
       begin
        max:=k;
        j:=i;
       end;
     end;
    delete(a[j],17,4);
    insert('0000',a[j],17);
    writeln(r,'. ',copy(a[j],1,16),max,' руб.');
    writeln(s,r,'. ',copy(a[j],1,16),max,' rub.');
   end;
 end;
begin
 clrscr;
 assign(f,'input.txt'); reset(f);
 assign(s,'output.txt'); rewrite(s);
 writeln(s,'Name            Price');
 writeln(s,'----------------------');
 writeln('Товар           Цена');
 line(22);
 for i:=1 to 10 do
  begin
   readln(f,a[i]);
   writeln(s,a[i]);
   writeln(a[i]);
  end;
 close(f);

 writeln(s); writeln(s);
 writeln(s,'The most expensive items:');
 writeln(s,'-------------------------');
 writeln; writeln;
 writeln('Самые дорогие вещи:');
 line(25);
 num:=3;
 findmax(num,a);

 close(s);
 readln;
end.