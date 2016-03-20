program task2;
{$N-}
uses FMM, crt;
label 111;
var A     : floatmatrix;
    B,Z,w : floatvector;
    ip    : ivector;
    cond  : float;
    i,N   : integer;

procedure MakeMatrix;
  var i,j : integer;
      mul : float;
  begin
    mul:=0.1;
    for j:=1 to N do
      A[1,j]:=1;
    for i:=1 to N do begin
      A[i,N]:=1+mul;
      mul:=mul*0.1;
    end;
    for i:=2 to N do
      for j:=1 to N-1 do
        A[i,j]:=exp(ln(j)*(i-1));
  end;

procedure PrintMatrix;
  var i,j : integer;
  begin
    writeln('  Matrix A:');
    for i:=1 to N do begin
      for j:=1 to N do
        if j=N then
          write(A[i,j]:14:9)
        else
          write(A[i,j]:8:0);
        writeln;
    end;
  end;

procedure MakeVector;
  var i : integer;
  begin
    for i:=1 to N do
      B[i]:=exp(ln(2)*i)+cos(i);
  end;

procedure PrintVector;
  var i : integer;
  begin
    writeln('  Vector B:');
    for i:=1 to N do
      write('  ',B[i]:6:3);
    writeln;
  end;

begin
  clrscr;
111:
  writeln;
  writeln(' To exit enter number < or = 0.');
  write(' Enter dimension N of square matrix A: ');
  readln(N);
  if N <= 0 then exit;
  clrscr;
  writeln('  N = ',N);

  MakeMatrix;
  PrintMatrix;
  MakeVector;
  PrintVector;

  writeln;
  decomp(N,A,cond,ip,w);

  writeln('  Cond(A) = ',cond:8:2);
  writeln('  Solution of A * Z = B:');

  solve(N,A,B,ip);
  for i:=1 to N do
    writeln('       Z[',i:1,'] =',B[i]:9:5);

  repeat until keypressed;
  goto 111;
end.