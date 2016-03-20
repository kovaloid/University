program task3a;
{$N-}
uses FMM, dos, crt;
label 111;
const n = 2;
      eps = 1E-4;
var relerr,abserr,
    t,tout,tfinal,tprint : float;
    iflag                : integer;
    iwork                : ivec5;
    work                 : rvecn;
    x,xp                 : floatvector;

{$F+}
procedure F(t : float; var x,xp : floatvector);
  begin
    xp[1]:=-40*x[1]+260*x[2]+1/(10*t*t+1);
    xp[2]:=30*x[1]-270*x[2]+exp(-2*t);
  end;
{$F-}

begin
  clrscr;
  t:=0;
  x[1]:=0;
  x[2]:=1;
  relerr:=eps;
  abserr:=0;
  tfinal:=0.4;
  tprint:=0.02;
  iflag:=1;
  tout:=t;
  writeln;
  writeln('        t           x[1]             x[2]        Flag');
  writeln('      ------------------------------------------------');

111:
  rkf45(@F,n,x,t,tout,relerr,abserr,iflag,work,iwork);
  writeln('     ',t:6:2, '     ',x[1]:12:9,'     ',x[2]:12:9,'     ',iflag);

  case iflag of
    1,8 : exit;
    2   : begin
            tout:=t+tprint;
            if t<tfinal then goto 111
          end;
    4   : goto 111;
    5   : begin
            abserr:=eps;
            goto 111
          end;
    6   : begin
            relerr:=10*relerr;
            iflag:=2;
            goto 111
          end;
    7   : begin
            iflag:=2;
            goto 111
          end
  end;
  readln;
end.






