unit module;
interface
 type mas=array[1..10] of string[25];
 var output:text;
 procedure line (n:integer);
 procedure findmax (x:integer; var a:mas);
implementation
 procedure line;
  var i:integer;
  begin
   for i:=1 to n do
    write('-');
   writeln;
  end;
 procedure findmax;
  var i,k,r,j,code,max:integer;
      p:string;
  begin
  assign(output,'output.txt'); append(output);
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
     writeln(output,r,'. ',copy(a[j],1,16),max,' rub.');
    end;
  close(output);
  end;
end.