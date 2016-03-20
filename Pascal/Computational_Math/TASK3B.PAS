program task3b;
{$N-}
uses FMM, dos, crt;
label 111;
const n = 2;
      eps = 1E-4;
var t0print,t1print,t2print,
    t,tout,relerr,abserr,tfinal : float;
    iflag,q,i                   : integer;
    iwork                       : ivec5;
    work                        : rvecn;
    x0,x1,x2                    : floatvector;
    func0,func1,func2,
    x0print,x1print,x2print     : floatmatrix;

{$F+}
procedure F(t : float; var x,xp : floatvector);
  begin
    xp[1]:=-40*x[1]+260*x[2]+1/(10*t*t+1);
    xp[2]:=30*x[1]-270*x[2]+exp(-2*t);
  end;
{$F-}

begin
  clrscr;
  writeln('  Source data:');

  t:=0;
  x1[1]:=0;
  x1[2]:=1;
  relerr:=eps;
  abserr:=0;
  t0print:=0.002;
  t1print:=0.001;
  t2print:=0.0001;
  tfinal:=t+2*t1print;
  iflag:=1;
  tout:=t;
  i:=1;
  writeln;

111:
  rkf45(@F,n,x1,t,tout,relerr,abserr,iflag,work,iwork);

  func1[1,i]:=-40*x1[1]+260*x1[2]+1/(10*t*t+1);
  func1[2,i]:=30*x1[1]-270*x1[2]+exp(-2*t);

  writeln('  t=',t:4:3,'  x[1]=',x1[1]:8:6,'  x[2]=',x1[2]:8:6,
          '  f[1,',i,']=',func1[1,i]:7:3,'  f[2,',i,']=',func1[2,i]:7:3);
  inc(i);

  case iflag of
    1,8 : exit;
    2   : begin
            tout:=t+t1print;
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

  writeln;
  writeln(' Press ENTER to continue...');
  readln;

{------------------------------------------------------------------}

  clrscr;
  writeln('                        Hint = 0.002               ');
  writeln('  -------------------------------------------------');
  writeln('     t            x[1]               x[2]          ');
  writeln('  -------------------------------------------------');

  tfinal:=0.4;
  x0[1]:=x1[1];
  x0[2]:=x1[2];
  func0[1,1]:=func1[1,1];
  func0[2,1]:=func1[2,1];
  func0[1,2]:=func1[1,2];
  func0[2,2]:=func1[2,2];
  func0[1,3]:=func1[1,3];
  func0[2,3]:=func1[2,3];

  q:=2;
  i:=1;

  while t<tfinal do begin
    t:=t+t0print;

    x0[1]:=x0[1]+t0print*(23*func0[1,3]-16*func0[1,2]+5*func0[1,1])/12;
    x0[2]:=x0[2]+t0print*(23*func0[2,3]-16*func0[2,2]+5*func0[2,1])/12;

    func0[1,1]:=func0[1,2];
    func0[2,1]:=func0[2,2];
    func0[1,2]:=func0[1,3];
    func0[2,2]:=func0[2,3];
    func0[1,3]:=-40*x0[1]+260*x0[2]+1/(10*t*t+1);
    func0[2,3]:=30*x0[1]-270*x0[2]+exp(-2*t);

    if q mod 10 = 0 then begin
      x0print[1,i]:=x0[1];
      x0print[2,i]:=x0[2];
      inc(i);
    end;
    inc(q);
  end;

  t:=0.02;
  for i:=1 to 20 do begin
    writeln(t:8:2,'        ',x0print[1,i]:12:2,'        ',x0print[2,i]:12:2);
    t:=t+0.02;
  end;
  readln;

{------------------------------------------------------------------}

  clrscr;
  writeln('                     Hint = 0.001                    Hint = 0.0001        ');
  writeln('  ------------------------------------------------------------------------');
  writeln('     t          x1[1]           x1[2]           x2[1]           x2[2]     ');
  writeln('  ------------------------------------------------------------------------');

  x2[1]:=x1[1];
  x2[2]:=x1[2];
  func2[1,1]:=func1[1,1];
  func2[2,1]:=func1[2,1];
  func2[1,2]:=func1[1,2];
  func2[2,2]:=func1[2,2];
  func2[1,3]:=func1[1,3];
  func2[2,3]:=func1[2,3];

  t:=0.002;
  q:=3;
  i:=1;

  while t<tfinal do begin
    t:=t+t1print;

    x1[1]:=x1[1]+t1print*(23*func1[1,3]-16*func1[1,2]+5*func1[1,1])/12;
    x1[2]:=x1[2]+t1print*(23*func1[2,3]-16*func1[2,2]+5*func1[2,1])/12;

    func1[1,1]:=func1[1,2];
    func1[2,1]:=func1[2,2];
    func1[1,2]:=func1[1,3];
    func1[2,2]:=func1[2,3];
    func1[1,3]:=-40*x1[1]+260*x1[2]+1/(10*t*t+1);
    func1[2,3]:=30*x1[1]-270*x1[2]+exp(-2*t);

    if q mod 20 = 0 then begin
      x1print[1,i]:=x1[1];
      x1print[2,i]:=x1[2];
      inc(i);
    end;
    inc(q);
  end;

  t:=0.002;
  q:=21;
  i:=1;

  while t<tfinal do begin
    t:=t+t2print;

    x2[1]:=x2[1]+t2print*(23*func2[1,3]-16*func2[1,2]+5*func2[1,1])/12;
    x2[2]:=x2[2]+t2print*(23*func2[2,3]-16*func2[2,2]+5*func2[2,1])/12;

    func2[1,1]:=func2[1,2];
    func2[2,1]:=func2[2,2];
    func2[1,2]:=func2[1,3];
    func2[2,2]:=func2[2,3];
    func2[1,3]:=-40*x2[1]+260*x2[2]+1/(10*t*t+1);
    func2[2,3]:=30*x2[1]-270*x2[2]+exp(-2*t);

    if q mod 200 = 0 then begin
      x2print[1,i]:=x2[1];
      x2print[2,i]:=x2[2];
      inc(i);
    end;
    inc(q);
  end;

  t:=0.02;
  for i:=1 to 20 do begin
    writeln(t:8:2,'      ',x1print[1,i]:9:8,'      ',x1print[2,i]:9:8,
            '      ',x2print[1,i]:9:8,'      ',x2print[2,i]:9:8);
    t:=t+0.02;
  end;
  readln;
end.






