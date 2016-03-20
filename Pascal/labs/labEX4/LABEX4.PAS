program labEX4;
type sled=^Monom;
     Monom=record
      coef:integer;
      deg:integer;
      next,prev:sled
     end;
var input1,output1:text;
    kStart1,kStart2:sled;
procedure ReadData(var Start1,Start2:sled; var input:text);
 var A,B,Last1,Last2:sled;
 begin
  new(Start1);
  A:=Start1;
  Last1:=nil;
  while not eoln(input) do
   begin
    new(A^.next);
    read(input,A^.coef,A^.deg);
    A^.prev:=Last1;
    Last1:=A;
    A:=A^.next;
   end;
  A^.next:=nil;
  Last1:=A;
  readln(input);
  new(Start2);
  B:=Start2;
  Last2:=nil;
  while not eoln(input) do
   begin
    new(B^.next);
    read(input,B^.coef,B^.deg);
    B^.prev:=Last2;
    Last2:=B;
    B:=B^.next;
   end;
  B^.next:=nil;
  Last2:=B;
 end;
procedure PrintData(Start1,Start2:sled; var output:text);
 var A,B:sled;
 begin
  write(output,'A(x): ');
  A:=Start1;
  while A^.next<>nil do
   begin
    write(output,'(',A^.coef,';',A^.deg,');');
    A:=A^.next;
   end;
  writeln(output);
  write(output,'B(x): ');
  B:=Start2;
  while B^.next<>nil do
   begin
    write(output,'(',B^.coef,';',B^.deg,');');
    B:=B^.next;
   end;
 end;
procedure SumPolinom(Start1,Start2:sled; var output:text);
 var A,B,tmp:sled;
     k,i:integer;
 begin
  A:=Start1;
  B:=Start2;
  writeln(output);
  write(output,'A(x)+B(x): ');
  if A^.deg<B^.deg then
   begin
    k:=B^.deg-A^.deg;
    for i:=1 to k do
     B:=B^.next;
    while B^.next<>nil do
     begin
      if A^.deg=B^.deg then
       begin
        B^.coef:=B^.coef+A^.coef;
        B:=B^.next;
        A:=A^.next;
       end
      else if A^.deg>B^.deg then
            begin
             new(tmp);
             tmp^.coef:=A^.coef;
             tmp^.deg:=A^.deg;
             tmp^.prev:=B^.prev;
             tmp^.next:=B;
             B^.prev:=tmp;
             B:=B^.prev^.prev;
             B^.next:=tmp;
             B:=B^.next^.next;
             A:=A^.next;
            end
           else B:=B^.next;
     end;
    B:=Start2;
    while B^.next<>nil do
     begin
      if B^.coef<>0 then
       write(output,'(',B^.coef,';',B^.deg,');');
      B:=B^.next;
     end;
   end
  else
     if A^.deg>B^.deg then
      begin
       k:=A^.deg-B^.deg;
       for i:=1 to k do
        A:=A^.next;
       while A^.next<>nil do
        begin
         if A^.deg=B^.deg then
          begin
           A^.coef:=A^.coef+B^.coef;
           A:=A^.next;
           B:=B^.next;
          end
         else if A^.deg<B^.deg then
               begin
                new(tmp);
                tmp^.coef:=B^.coef;
                tmp^.deg:=B^.deg;
                tmp^.prev:=A^.prev;
                tmp^.next:=A;
                A^.prev:=tmp;
                A:=A^.prev^.prev;
                A^.next:=tmp;
                A:=A^.next^.next;
                B:=B^.next;
               end
              else A:=A^.next;
        end;
       A:=Start1;
       while A^.next<>nil do
        begin
         if A^.coef<>0 then
          write(output,'(',A^.coef,';',A^.deg,');');
         A:=A^.next;
        end;
      end
     else
        begin
         while A^.next<>nil do
          begin
           A^.coef:=B^.coef+A^.coef;
           A:=A^.next;
           B:=B^.next;
          end;
         A:=Start1;
         while A^.next<>nil do
          begin
           if A^.coef<>0 then
            write(output,'(',A^.coef,';',A^.deg,');');
           A:=A^.next;
          end;
        end;
 end;
begin
 assign(input1,'input.txt'); reset(input1);
 assign(output1,'output.txt'); rewrite(output1);
  ReadData(kStart1,kStart2,input1);
  PrintData(kStart1,kStart2,output1);
  SumPolinom(kStart1,kStart2,output1);
 close(input1); close(output1);
 readln;
end.