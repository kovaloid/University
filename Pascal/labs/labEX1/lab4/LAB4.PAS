program lab4;
uses module;
var a:mas;
    input,output:text;
    i:integer;
begin
 assign(input,'input.txt'); reset(input);
 assign(output,'output.txt'); rewrite(output);
 writeln(output,'Name            Price');
 writeln(output,'----------------------');
 writeln('Товар           Цена');
 line(22);
 for i:=1 to 10 do
  begin
   readln(input,a[i]);
   writeln(output,a[i]);
   writeln(a[i]);
  end;
 close(input);

 writeln(output); writeln(output);
 writeln(output,'The most expensive items:');
 writeln(output,'-------------------------');
 close(output);
 writeln; writeln;
 writeln('Самые дорогие вещи:');
 line(25);
 findmax(3,a);
 readln;
end.