program labEX6;
uses graph,crt;
const Triangle: Array [1..32] of PointType = ((X: 50; Y: 50),
                                              (X: 100; Y:50),
                                              (X: 100; Y: 80),
                                              (X: 200; Y: 80),
                                              (X: 200; Y: 90),
                                              (X: 210; Y: 90),
                                              (X: 210; Y: 80),
                                              (X: 200; Y: 40),
                                              (X: 230; Y: 40),
                                              (X: 220; Y: 80),
                                              (X: 220; Y: 90),
                                              (X: 227; Y: 100),
                                              (X: 230; Y: 110),
                                              (X: 227; Y: 120),
                                              (X: 220; Y: 130),
                                              (X: 230; Y: 130),
                                              (X: 230; Y: 140),
                                              (X: 220; Y: 140),
                                              (X: 240; Y: 155),
                                              (X: 200; Y: 155),
                                              (X: 200; Y: 140),
                                              (X: 195; Y: 140),
                                              (X: 195; Y: 130),
                                              (X: 200; Y: 130),
                                              (X: 190; Y: 120),
                                              (X: 90; Y: 120),
                                              (X: 80; Y: 130),
                                              (X: 80; Y: 150),
                                              (X: 40; Y: 150),
                                              (X: 40; Y: 110),
                                              (X: 50; Y: 110),
                                              (X: 50; Y: 50));
label 1;
var gd,gm,n,x1,x2,y1,y2,x1kol,x2kol,x3kol,ykol,xporsh,yporsh:integer;
    Poezd,Hor:pointer;
    SizeP,SizeH,speed:word;
    arrow:char;
begin
 gd:=0;
 DetectGraph(gd,gm);
 InitGraph(gd,gm,'');
 if GraphResult<>0 then
  begin
   writeln('mistake:',GraphResult);
   halt
  end;
 SetBkColor(Blue);
 SetFillStyle(Solidfill,8);
 SetTextStyle(TriplexFont,0,1);
 ClearDevice;

 OutTextXY(280,300,'PRESS ARROWS:');
 OutTextXY(200,320,'BUTTON /LEFT/ FOR LOW SPEED');
 OutTextXY(330,340,'OR');
 OutTextXY(200,360,'BUTTON /RIGHT/ FOR MORE SPEED');
 OutTextXY(240,380,'BUTTON /ESC/ FOR EXIT');
 FillPoly(32,Triangle);
 SetFillStyle(Solidfill,Red);
 FillEllipse(105,140,15,15);
 FillEllipse(140,140,15,15);
 FillEllipse(175,140,15,15);
 Circle(105,140,13);
 Circle(140,140,13);
 Circle(175,140,13);
 Circle(105,140,5);
 Circle(140,140,5);
 Circle(175,140,5);
 SetFillStyle(Emptyfill,0);
 Bar(60,60,90,90);
 Rectangle(60,60,90,90);

 x1:=40; y1:=40;
 x2:=240; y2:=155;
 SizeP:=Imagesize(x1,y1,x2,y2);
 Getmem(Poezd,SizeP);
 Getimage(x1,y1,x2,y2,Poezd^);

 x1kol:=105;
 x2kol:=140;
 x3kol:=175;
 ykol:=153;
 xporsh:=195;yporsh:=135;
 line(x1kol,ykol,xporsh,yporsh);
 line(x2kol,ykol,xporsh,yporsh);
 line(x3kol,ykol,xporsh,yporsh);
 line(x1kol,ykol,x3kol,ykol);

 SizeH:=Imagesize(x1kol,ykol,x3kol,ykol);
 Getmem(Hor,SizeH);
 Getimage(x1kol,ykol,x3kol,ykol,Hor^);

 n:=0;
 speed:=100;
 Repeat
1:arrow:=readkey;
  Case arrow of
   #75:begin
        speed:=speed+10;
        if speed<20 then speed:=20;
        Repeat
         if xporsh>580 then
          begin
           x1:=40;
           y1:=40;
           x1kol:=105;
           x2kol:=140;
           x3kol:=175;
           ykol:=153;
           xporsh:=195;
           yporsh:=135;
           n:=1;
          end;

         x1:=x1+5;
         x1kol:=round(4*sin(pi*n/10-pi/2))+x1kol;
         x2kol:=round(4*sin(pi*n/10-pi/2))+x2kol;
         x3kol:=round(4*sin(pi*n/10-pi/2))+x3kol;
         ykol:=round(-4*cos(pi*n/10-pi/2))+ykol;
         x1kol:=x1kol+5;
         x2kol:=x2kol+5;
         x3kol:=x3kol+5;
         xporsh:=xporsh+5;
         n:=n+1;
         delay(speed);

         ClearDevice;
         Putimage(x1,y1,Poezd^,0);
         Putimage(x1kol,ykol,Hor^,0);
         line(x1kol,ykol,xporsh,yporsh);
         line(x2kol,ykol,xporsh,yporsh);
         line(x3kol,ykol,xporsh,yporsh);
        Until keypressed;
        goto 1;
       end;
   #77:begin
        speed:=speed-10;
        if speed<20 then speed:=20;
        Repeat
         if xporsh>580 then
          begin
           x1:=40;
           y1:=40;
           x1kol:=105;
           x2kol:=140;
           x3kol:=175;
           ykol:=153;
           xporsh:=195;
           yporsh:=135;
           n:=1;
          end;

         x1:=x1+5;
         x1kol:=round(4*sin(pi*n/10-pi/2))+x1kol;
         x2kol:=round(4*sin(pi*n/10-pi/2))+x2kol;
         x3kol:=round(4*sin(pi*n/10-pi/2))+x3kol;
         ykol:=round(-4*cos(pi*n/10-pi/2))+ykol;
         x1kol:=x1kol+5;
         x2kol:=x2kol+5;
         x3kol:=x3kol+5;
         xporsh:=xporsh+5;
         n:=n+1;
         delay(speed);

         ClearDevice;
         Putimage(x1,y1,Poezd^,0);
         Putimage(x1kol,ykol,Hor^,0);
         line(x1kol,ykol,xporsh,yporsh);
         line(x2kol,ykol,xporsh,yporsh);
         line(x3kol,ykol,xporsh,yporsh);
        Until keypressed;
        goto 1;
       end;
  end;
 Until arrow=#27;
 FreeMem(Poezd,SizeP);
 FreeMem(Hor,SizeH);
 CloseGraph;
end.

