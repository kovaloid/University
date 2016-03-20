UNIT schedule;
INTERFACE
USES graph;
Type

    GrafMaker=object
	    last_x11, last_y11, last_x12, last_y12,
      last_x21, last_y21, last_x22, last_y22: real;
	    n1,n2,n3,n4:integer;
      Constructor Init;
      Procedure DrawPlate;
      Procedure DrawLine(x, y : real; GRAF_TYPE, SOURCE_NUM, STEP : integer);
      Procedure MakeTable;
	    Procedure MakeData(DATA:real; SOURCE_NUM, GRAF_TYPE: integer);
    end;
  
Var
     xGrafMaker : GrafMaker;

IMPLEMENTATION

  Constructor GrafMaker.Init;
    Begin
		   last_x11 := 0;
		   last_y11 := 0;
		   last_x12 := 0;
		   last_y12 := 0;
		   last_x21 := 0;
		   last_y21 := 0;
		   last_x22 := 0;
		   last_y22 := 0;
		   n1:=0;
		   n2:=0;
		   n3:=0;
		   n4:=0;
    End;
	   
	   
  Procedure GrafMaker.DrawPlate;
     var
       i : integer;
     begin
	     OutTextXY(170,10,'1 STREAM - RED ; 2 STREAM - GREEN');
	
       SetColor(white);
	     OutTextXY(GetMaxX div 10-20,GetMaxY div 2-200,'Pi');
	     OutTextXY(8*GetMaxX div 10-50,GetMaxY div 2-20,'LAM1');
       line(GetMaxX div 10,GetMaxY div 2-30,8*GetMaxX div 10-40,GetMaxY div 2-30); {OX1}
	     line(GetMaxX div 10,GetMaxY div 2-30,GetMaxX div 10,GetMaxY div 2-200); {OY1}
		
	     OutTextXY(GetMaxX div 10-20,GetMaxY-200,'Mi');
	     OutTextXY(8*GetMaxX div 10-50,GetMaxY-20,'LAM1');
	     line(GetMaxX div 10,GetMaxY-30,8*GetMaxX div 10-40,GetMaxY-30); {OX2}
	     line(GetMaxX div 10,GetMaxY-30,GetMaxX div 10,GetMaxY-200); {OY2}
{shkala OX}
	     for i:=1 to 10 do
         begin
           line(GetMaxX div 10+35*i,GetMaxY div 2-25,GetMaxX div 10+35*i,GetMaxY div 2-35); {1_graf_OX}
           line(GetMaxX div 10+35*i,GetMaxY-25,GetMaxX div 10+35*i,GetMaxY-35); {2_graf_OX}
         end;
{shkala OY}
	     for i:=1 to 4 do
         begin
           line(GetMaxX div 10+5,GetMaxY div 2-25-35*i,GetMaxX div 10-5,GetMaxY div 2-25-35*i);
           line(GetMaxX div 10+5,GetMaxY-25-35*i,GetMaxX div 10-5,GetMaxY-25-35*i)
         end;
{1_graf_OX}	 
	     OutTextXY(GetMaxX div 10-10,GetMaxY div 2-20,'0.5');
     	 OutTextXY(GetMaxX div 10+165,GetMaxY div 2-20,'1.0');
	     OutTextXY(GetMaxX div 10+340,GetMaxY div 2-20,'1.5');
	     OutTextXY(GetMaxX div 10-35,GetMaxY div 2-100,'50%');
	     OutTextXY(GetMaxX div 10-40,GetMaxY div 2-170,'100%');
{2_graf_OX}
	     OutTextXY(GetMaxX div 10-10,GetMaxY-20,'0.5');
	     OutTextXY(GetMaxX div 10+165,GetMaxY-20,'1.0');
	     OutTextXY(GetMaxX div 10+340,GetMaxY-20,'1.5');
	     OutTextXY(GetMaxX div 10-35,GetMaxY-100,'50%');
	     OutTextXY(GetMaxX div 10-40,GetMaxY-170,'100%');
{triangles}
       Line(8*GetMaxX div 10-40, GetMaxY div 2-27, 8*GetMaxX div 10-40, GetMaxY div 2-33);
       Line(8*GetMaxX div 10-40, GetMaxY div 2-33, 8*GetMaxX div 10-30, GetMaxY div 2-30);
       Line(8*GetMaxX div 10-30, GetMaxY div 2-30, 8*GetMaxX div 10-40, GetMaxY div 2-27);

       Line(8*GetMaxX div 10-40, GetMaxY-27, 8*GetMaxX div 10-40, GetMaxY-33);
       Line(8*GetMaxX div 10-40, GetMaxY-33, 8*GetMaxX div 10-30, GetMaxY-30);
       Line(8*GetMaxX div 10-30, GetMaxY-30, 8*GetMaxX div 10-40, GetMaxY-27);

       Line(GetMaxX div 10-3, GetMaxY div 2-200, GetMaxX div 10+3, GetMaxY div 2-200);
       Line(GetMaxX div 10+3, GetMaxY div 2-200, GetMaxX div 10, GetMaxY div 2-210);
       Line(GetMaxX div 10, GetMaxY div 2-210, GetMaxX div 10-3, GetMaxY div 2-200);

       Line(GetMaxX div 10-3, GetMaxY-200, GetMaxX div 10+3, GetMaxY-200);
       Line(GetMaxX div 10+3, GetMaxY-200, GetMaxX div 10, GetMaxY-210);
       Line(GetMaxX div 10, GetMaxY-210, GetMaxX div 10-3, GetMaxY-200);
     End;


   Procedure GrafMaker.DrawLine(x, y : real; GRAF_TYPE, SOURCE_NUM, STEP : integer);
     begin
       if SOURCE_NUM = 1 then
         setcolor(red)
       else
         setcolor(green);

       if STEP = 1 then
         case SOURCE_NUM of
           1 : case GRAF_TYPE of
                 1 : begin
                       last_x11 := x;
                       last_y11 := y;
                     end;
                 2 : begin
                       last_x12 := x;
                       last_y12 := y;
                     end;
                 end;
           2 : case GRAF_TYPE of
                 1 : begin
                       last_x21 := x;
                       last_y21 := y;
                     end;
                 2 : begin
                       last_x22 := x;
                       last_y22 := y;
                     end;
           end;
       end
     else
         case SOURCE_NUM of
           1 : case GRAF_TYPE of
                 1 : begin
                       {P for 1 stream}

					             circle(GetMaxX div 10 + (STEP - 2) * 35,GetMaxY div 2-40 - round(last_y11*100),2);
					             line(GetMaxX div 10 + (STEP - 2) * 35, GetMaxY div 2-40 - round(last_y11*100),
                       GetMaxX div 10 + (STEP-1) * 35, GetMaxY div 2-40 - round(y*100));
					   
                       last_x11 := x;
                       last_y11 := y;
                     end;
                 2 : begin
                       {M for 1 stream}
					  
                       circle(GetMaxX div 10 + (STEP - 2) * 35, GetMaxY - 40 - round(last_y12*100),2);
					             line(GetMaxX div 10 + (STEP - 2) * 35, GetMaxY - 40 - round(last_y12*100),
                       GetMaxX div 10 + (STEP-1) * 35, GetMaxY - 40 - round(y*100));
					   
                       last_x12 := x;
                       last_y12 := y;
                     end;

           end;
         2 : case GRAF_TYPE of
                 1 : begin
                       {P for 2 stream}

                       circle(GetMaxX div 10 + (STEP - 2) * 35, GetMaxY div 2 - 40 - round(last_y21*100),2);
				               line(GetMaxX div 10 + (STEP - 2) * 35, GetMaxY div 2 - 40 - round(last_y21*100),
                       GetMaxX div 10 + (STEP-1) * 35, GetMaxY div 2 - 40 - round(y*100));

                       last_x21 := x;
                       last_y21 := y;
                     end;
                 2 : begin
                       {M for 2 stream}

                       circle(GetMaxX div 10 + (STEP - 2) * 35, GetMaxY - 40 - round(last_y22*100),2);
				            	 line(GetMaxX div 10 + (STEP - 2) * 35, GetMaxY - 40 - round(last_y22*100),
                       GetMaxX div 10 + (STEP-1)  * 35, GetMaxY - 40 - round(y*100));
					   
                       last_x22 := x;
                       last_y22 := y;
                 end;
         end;
       end;
     end;
	 
	 

  Procedure GrafMaker.MakeTable;
    var
      s : string;
      i : integer;
    begin
    	SetColor(white);
    	OutTextXY(GetMaxX div 2 - 35,10,'RESULTS');
	    for i := 0 to 5 do
           line(3*GetMaxX div 16 + GetMaxX div 8 * i, 20, 3*GetMaxX div 16 + GetMaxX div 8 * i, 20 + GetMaxY div 13 * 12);
      for i := 0 to 12 do
           line(3*GetMaxX div 16, 20 + GetMaxY div 13 * i, 3*GetMaxX div 16 + GetMaxX div 8 * 5, 20+GetMaxY div 13 * i);
	  
      outtextxy(3*GetMaxX div 16+25, 30, 'LAM1');
      outtextxy(3*GetMaxX div 16+ GetMaxX div 8 * 1+30, 30, 'P1');
      outtextxy(3*GetMaxX div 16+ GetMaxX div 8 * 2+30, 30, 'P2');
      outtextxy(3*GetMaxX div 16+ GetMaxX div 8 * 3+30, 30, 'M1');
      outtextxy(3*GetMaxX div 16+ GetMaxX div 8 * 4+30, 30, 'M2');

      for i := 0 to 10 do
        begin
          str(0.5 + i * 0.1 : 0 : 1, s);
          outtextxy(3*GetMaxX div 16+30, 35 + GetMaxY div 13+GetMaxY div 13 * i, s);
        end;

	end;


  Procedure GrafMaker.MakeData(DATA:real; SOURCE_NUM, GRAF_TYPE: integer);
    var
      s : string;
    begin
    	SetColor(white);
     	str(DATA : 2 : 2, s);
	
         case SOURCE_NUM of
           1 : case GRAF_TYPE of
                 1 : begin
                       {P for 1 potoka}		
							         outtextxy(3*GetMaxX div 16+ GetMaxX div 8*1+30, 35 + GetMaxY div 13+GetMaxY div 13 * n1, s);
							         n1:=n1+1;
                     end;
                 2 : begin
                      {M for 1 potoka}
							        outtextxy(3*GetMaxX div 16+ GetMaxX div 8*2+30, 35 + GetMaxY div 13+GetMaxY div 13 * n2, s);
							        n2:=n2+1;
                     end;

           end;
         2 : case GRAF_TYPE of
             1 : begin
                {P for 2 potoka}
							      outtextxy(3*GetMaxX div 16+ GetMaxX div 8*3+30, 35 + GetMaxY div 13+GetMaxY div 13 * n3, s);
							      n3:=n3+1;
                 end;
             2 : begin
                  {M for 2 potoka}
							      outtextxy(3*GetMaxX div 16+ GetMaxX div 8*4+30, 35 + GetMaxY div 13+GetMaxY div 13 * n4, s);
						      	n4:=n4+1;
                 end;
         end;
	    end;
    end;

BEGIN


END.