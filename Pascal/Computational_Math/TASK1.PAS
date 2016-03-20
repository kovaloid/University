program task1;
{$N-}
uses FMM, crt;
const n = 6;
var x,y,b,c,d : floatvector;
    ax,bx,eps : float;
    i,j       : integer;

{$F+}
function F(u : float) : float;
  begin
    F:=seval(n,u,x,y,b,c,d)-1.8*u*u;
    inc(j);
  end;
{$F-}

begin
  clrscr;

  x[1]:=-1.0; y[1]:=0.5440;
  x[2]:=-0.9; y[2]:=-0.4121;
  x[3]:=-0.8; y[3]:=-0.9894;
  x[4]:=-0.7; y[4]:=-0.6570;
  x[5]:=-0.6; y[5]:=0.2794;
  x[6]:=-0.5; y[6]:=0.9589;

  writeln;
  write('  x   |');
  for i:=1 to n do
    write(x[i]:8:1);
  writeln;
  write(' f(x) |');
  for i:=1 to n do
    write(y[i]:8:4);
  writeln;
  writeln;

  spline(n,x,y,b,c,d);

  ax:=-1;
  bx:=-0.5;
  eps:=1;
  writeln('        Eps             Root          Nofun');
  writeln('      -------------------------------------');

  for i:=1 to 10 do begin
    j:=0;
    eps:=eps*0.1;
    writeln('     ',eps:8,'     ',zeroin(ax,bx,eps,@F):16:12,'      ',j);
  end;
  readln;
end.