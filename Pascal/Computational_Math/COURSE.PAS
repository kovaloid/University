program course;
{$N-}
uses FMM, crt, dos, graph;
const H = 0.0001;
      errorD = 1;
      t1 = 0;
      t2 = 20;
      N = trunc((t2-t1)/H);
      dim = trunc((t2-t1)/0.1);
      mu1 = 1/82.45;
      mu2 = 1 - mu1;

var result,errest,flag,
    relerr,abserr,ax,bx,
    A,B,C,D,tol,r1,r2,tt,
    xx,dx,ddx,yy,dy,ddy    : float;
    nofun,j,count          : longint;
    x,y,t                  : array[1..dim+1] of float;
    i,px,py,pt,
    x0,y0,t0,wdx,wdy,wdt,
    xold,yold,told,grD,grM : integer;
    s                      : string;
    h1, h2, h3, h4,
    k1, k2, k3, k4         : word;
    n1                     : integer absolute h1;
    n2                     : integer absolute h2;
    n3                     : integer absolute h3;
    n4                     : integer absolute h4;
    l1                     : integer absolute k1;
    l2                     : integer absolute k2;
    l3                     : integer absolute k3;
    l4                     : integer absolute k4;

{$F+}
function funC(t : float) : float;
  begin
    funC:=1/sqrt((t*t+1)*(3*t*t+4))
  end;
{$F-}

{$F+}
function funD(x : float) : float;
  begin
    funD:=2*ln(x)/ln(10)+1-x/2;
  end;
{$F-}

begin
  clrscr;
  writeln;
  writeln('  Course work (Task # 10 B)');
  writeln;

  A:=1.2;
  B:=0;

  relerr:=1e-9;
  abserr:=0;
  ax:=0;
  bx:=1;
  quanc8(@funC,ax,bx,abserr,relerr,result,errest,nofun,flag);
  C:=exp(ln(result-0.40218305)*4);

  tol:=1e-9;
  ax:=0.0001;
  bx:=1;
  D:=zeroin(ax,bx,tol,@funD);
  D:=-2.639594*D;

  t[1]:=0;
  x[1]:=A;
  dx:=B;
  y[1]:=C;
  dy:=D*errorD;

  writeln('    H = ',H:9:6);
  writeln('    mu1 = ',mu1:9:6);
  writeln('    mu2 = ',mu2:9:6);
  writeln('    x(0) = ',x[1]:2:1);
  writeln('    dx(0) = ',dx:1:0);
  writeln('    y(0) = ',y[1]);
  writeln('    dy(0) = ',dy:9:6);
  writeln;
  writeln('  Press ENTER to continue...');
  readln;
  clrscr;

{------------------------------------------------------------------}

  gettime(h1,h2,h3,h4);

  r1:=sqrt((x[1]+mu1)*(x[1]+mu1)+y[1]*y[1]);
  r1:=r1*r1*r1;
  r2:=sqrt((x[1]-mu2)*(x[1]-mu2)+y[1]*y[1]);
  r2:=r2*r2*r2;
  ddx:=2*dy+x[1]-mu2*(x[1]+mu1)/r1-mu1*(x[1]-mu2)/r2;
  ddy:=-2*dx+y[1]-mu2*y[1]/r1-mu1*y[1]/r2;

  writeln('      x = ',x[1]:9:6,'       y = ',y[1]:9:6,'       t = ',t[1]:4:1);

  tt:=t[1];
  xx:=x[1];
  yy:=y[1];
  count:=0;
  i:=2;

  for j:=1 to N do begin
    tt:=tt+H;
    xx:=xx+H*dx+H*H*ddx/2;
    yy:=yy+H*dy+H*H*ddy/2;

    r1:=sqrt((xx+mu1)*(xx+mu1)+yy*yy);
    r1:=r1*r1*r1;
    r2:=sqrt((xx-mu2)*(xx-mu2)+yy*yy);
    r2:=r2*r2*r2;
    dx:=2*yy+xx*xx/2-mu2*(xx*xx/2+mu1*tt)/r1-mu1*(xx*xx/2-mu2*tt)/r2;
    dy:=-2*xx+yy*yy/2-mu2*yy*yy/(2*r1)-mu1*yy*yy/(2*r2);

    ddx:=2*dy+xx-mu2*(xx+mu1)/r1-mu1*(xx-mu2)/r2;
    ddy:=-2*dx+yy-mu2*yy/r1-mu1*yy/r2;

    count:=count+1;
    if count mod trunc(N/dim) = 0 then
    begin
      y[i]:=yy;
      x[i]:=xx;
      t[i]:=tt;
      i:=i+1;
      writeln('      x = ',xx:9:6,'       y = ',yy:9:6,'       t = ',tt:4:1);
    end;
  end;

  gettime(k1,k2,k3,k4);
  writeln;
  writeln('  Total time = ',
  ((l1-n1)*360000.0+(l2-n2)*6000.0+(l3-n3)*100.0+(l4-n4))/100.0:6:2,' seconds');
  writeln;
  writeln('  Press ENTER to continue...');
  readln;

{------------------------------------------------------------------}

  clrscr;
  grD:=detect;
  InitGraph(grD,grM,'');

  y0:=GetMaxY div 2 - 50;
  x0:=GetMaxX div 2 - 60;
  SetBkColor(7);
  SetLineStyle(1,0,0);
  SetColor(9);

  wdx:=GetMaxX div 12;
  wdy:=GetMaxY div 12;
  outtextXY(x0-10,y0+5,'0');

  for i:=1 to 7 do begin
    line(0,y0-i*wdy,GetMaxX,y0-i*wdy);
    line(0,y0+i*wdy,GetMaxX,y0+i*wdy);
    line(x0+i*wdx,0,x0+i*wdx,GetMaxY);
    line(x0-i*wdx,0,x0-i*wdx,GetMaxY);
    if i mod 2 = 0 then begin
      str(i div 2,s);
      outtextXY(x0-10,y0-i*wdy-10,s);
      outtextXY(x0-20,y0+i*wdy+5,'-'+s);
      outtextXY(x0+i*wdx+5,y0+5,s);
      outtextXY(x0-i*wdx-15,y0+5,'-'+s);
    end;
  end;

  outtextXY(getmaxX-10,y0-10,'X');
  outtextXY(x0+10,5,'Y');
  SetLineStyle(0,0,1);
  SetColor(1);
  line(0,y0,GetMaxX,y0);
  line(x0,GetMaxY,x0,0);

  px:=x0+round(-mu1*2*wdx);
  circle(px,y0,3);
  outtextXY(px-45,y0-15,'Earth');

  px:=x0+round(mu2*2*wdx);
  circle(px,y0,3);
  outtextXY(px-35,y0+5,'Moon');

  SetColor(4);
  px:=x0+round(x[1]*2*wdx);
  py:=y0+round(y[1]*2*wdy);
  circle(px,py,3);
  outtextXY(px-55,y0-15,'Apollo');

  px:=x0+round(x[1]*2*wdx);
  py:=y0-round(y[1]*2*wdy);
  circle(px,py,1);
  for i:=2 to 201 do begin
    xold:=px;
    yold:=py;
    px:=x0+round(x[i]*2*wdx);
    py:=y0-round(y[i]*2*wdy);
    line(xold,yold,px,py);
    circle(px,py,1);
  end;

  circle(px,py,3);
  outtextXY(px-5,py-20,'Apollo in t=20');
  readln;

{------------------------------------------------------------------}

  cleardevice;

  x0:=GetMaxY div 2;
  t0:=20;
  SetBkColor(7);
  SetLineStyle(1,0,0);
  SetColor(9);

  wdt:=GetMaxX div (t2-t1);
  wdx:=GetMaxY div 10;
  outtextXY(t0-10,x0+5,'0');

  for i:=1 to 20 do begin
    line(0,x0-i*wdx,GetMaxX,x0-i*wdx);
    line(0,x0+i*wdx,GetMaxX,x0+i*wdx);
    line(t0+i*wdt,0,t0+i*wdt,GetMaxY);
    if i mod 2 = 0 then begin
      str(i,s);
      outtextXY(t0-10,x0-i*wdx-10,s);
      outtextXY(t0-18,x0+i*wdx+5,'-'+s);
      outtextXY(t0+i*wdt+5,x0+5,s);
    end;
  end;

  outtextXY(GetMaxX-10,x0-10,'T');
  outtextXY(t0+10,5,'X');
  SetLineStyle(0,0,1);
  SetColor(1);
  line(0,x0,GetMaxX,x0);
  line(t0,GetMaxY,t0,0);

  SetColor(4);
  pt:=t0+round(t[1]*wdt);
  px:=x0-round(x[1]*wdx);
  circle(pt,px,1);
  for i:=2 to 201 do begin
    told:=pt;
    xold:=px;
    pt:=t0+round(t[i]*wdt);
    px:=x0-round(x[i]*wdx);
    line(told,xold,pt,px);
    circle(pt,px,1);
  end;
  readln;

{------------------------------------------------------------------}

  cleardevice;

  y0:=GetMaxY div 2;
  t0:=20;
  SetBkColor(7);
  SetLineStyle(1,0,0);
  SetColor(9);

  wdt:=GetMaxX div (t2-t1);
  wdy:=GetMaxY div 10;
  outtextXY(t0-10,y0+5,'0');

  for i:=1 to 20 do begin
    line(0,y0-i*wdy,GetMaxX,y0-i*wdy);
    line(0,y0+i*wdy,GetMaxX,y0+i*wdy);
    line(t0+i*wdt,0,t0+i*wdt,GetMaxY);
    if i mod 2 = 0 then begin
      str(i,s);
      outtextXY(t0-10,y0-i*wdy-10,s);
      outtextXY(t0-18,y0+i*wdy+5,'-'+s);
      outtextXY(t0+i*wdt+5,y0+5,s);
    end;
  end;

  outtextXY(GetMaxX-10,y0-10,'T');
  outtextXY(t0+10,5,'Y');
  SetLineStyle(0,0,1);
  SetColor(1);
  line(0,y0,GetMaxX,y0);
  line(t0,GetMaxY,t0,0);

  SetColor(4);
  pt:=t0+round(t[1]*wdt);
  py:=y0-round(y[1]*wdy);
  circle(pt,py,1);
  for i:=2 to 201 do begin
    told:=pt;
    yold:=py;
    pt:=t0+round(t[i]*wdt);
    py:=x0-round(y[i]*wdy);
    line(told,yold,pt,py);
    circle(pt,py,1);
  end;

  readln;
  closegraph
end.





