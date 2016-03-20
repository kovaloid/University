program lab1;
var a:array[1..10, 1..25] of char;
    f,s:text;
    i,j,n,k,p,max,r:integer;
begin
 assign(f,'input.txt'); reset(f);
 assign(s,'output.txt'); rewrite(s);
 writeln(s,'Name          Price');
 writeln(s,'----------------------');
 writeln('Товар         Цена');
 writeln('----------------------');
 for i:=1 to 10 do
  begin
   for j:=1 to 25 do
    begin
     read(f,a[i,j]);
     write(s,a[i,j]);
     write(a[i,j]);
    end;
  end;
 close(f);

 writeln(s);writeln(s);
 writeln; writeln;
 writeln(s,'The most expensive:');
 writeln(s,'----------------------');
 writeln('Самые дорогие вещи:');
 writeln('----------------------');

 for r:=1 to 3 do
  begin
   max:=(ord(a[1,15])-ord('0'))*1000+
+(ord(a[1,16])-ord('0'))*100+
+(ord(a[1,17])-ord('0'))*10+
+(ord(a[1,18])-ord('0'));
   for i:=1 to 10 do
    begin
     k:=(ord(a[i,15])-ord('0'))*1000+
+(ord(a[i,16])-ord('0'))*100+
+(ord(a[i,17])-ord('0'))*10+
+(ord(a[i,18])-ord('0'));
     if k>=max then
      begin
       max:=k;
       p:=i;
      end;
    end;
   for n:=15 to 18 do
    begin
     a[p,n]:='0';
    end;
   write(r,'. ');
   write(s,r,'. ');
   for j:=1 to 14 do
    begin
     write(a[p,j]);
     write(s,a[p,j]);
    end;
   writeln(max,' руб.');
   writeln(s,max,' rub.');
  end;

 close(s);
 readln
end.