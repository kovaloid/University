UNIT menu;
INTERFACE
USES new_crt, graph, func;

Type

  Display = object
    k:char;
    gflag:boolean;
    index, index1, index2, int_data, code:integer;
    str_data: string;
    real_data: real;
  	Constructor Init;
    Procedure ShowMenu;
    Procedure ButON(but:integer);
    Procedure ShowPodMenu(xIND:integer);
    Procedure ReadMe;
   	Procedure SelectButtonMain;
  	Procedure SelectButtonPodMenu(xIND:integer);
    Function InputData : string;
  end;

Var

   xDisplay:Display;

IMPLEMENTATION

Constructor Display.Init;
   Begin
	   gflag := true;
     index:=0;
     index1:=5;
     index2:=10;
   End;
	   
	   
Procedure Display.ShowMenu;
  Begin
    cleardevice;
	  Setfillstyle(1, red);
	  Bar(10,10,160,230);
	  Setfillstyle(1, green);
	  Bar(20,20,150,220);
		SetColor(red);
		line(20,60,150,60);
		line(20,100,150,100);
		line(20,140,150,140);
		line(20,180,150,180);
		SetColor(white);
		Outtextxy(40,40, 'SET VALUES');
		Outtextxy(40,80, 'SET OUTPUT');
		Outtextxy(40, 120, 'RESULTS');
		Outtextxy(40, 160, 'HELP');
		Outtextxy(40, 200, 'EXIT');
  End;


Procedure Display.ButON(but:integer);
  Begin
   Setfillstyle(1, red);
   case but of
{-----------------------MainMenu----------------------------}
	   1 : begin
			     Bar(22,22,148,57);
			     Outtextxy(40,40, 'SET VALUES');
	       end;
	   2 : begin
			     Bar(22,63,148,97);
			     Outtextxy(40,80, 'SET OUTPUT');
	       end;
	   3 : begin
			     Bar(22,103,148,137);
			     Outtextxy(40, 120, 'RESULTS');
	       end;
	   4 : begin
	  		   Bar(22,143,148,177);
			     Outtextxy(40, 160, 'HELP');
	       end;
	   5 : begin
			     Bar(22,183,148,218);
			     Outtextxy(40, 200, 'EXIT');
	       end;
{-----------------------PodMenu_1----------------------------}
	   6 : begin
			     Bar(152,27,218,53);
			     Outtextxy(170,40, 'dLAM');
	       end;
	   7 : begin
			     Bar(222,27,288,53);
			     Outtextxy(240,40, 'TAY1');
	       end;
	   8 : begin
			     Bar(292,27,358,53);
			     Outtextxy(310,40, 'TAY2');
	       end;
	   9 : begin
			     Bar(362,27,428,53);
			     Outtextxy(380,40, 'LAMOB');
	       end;
	   10 : begin
			      Bar(432,27,498,53);
			      Outtextxy(450,40, 'KMIN');
	        end;

{------------------------PodMEnu_2---------------------------}
	   11 : begin
			      Bar(152,67,248,93);
			      Outtextxy(170,80, 'Graphic');
	        end;
	   12 : begin
			      Bar(252,67,348,93);
			      Outtextxy(270,80, 'Table');
	        end;
     end;

    End;


Procedure Display.ShowPodMenu(xIND:integer);
  Begin
  
if xIND=1 then
 begin

    Setfillstyle(1, green);
    Bar(150,25,500,55);
		SetColor(red);
		line(150,25,150,55);
		line(220,25,220,55);
		line(290,25,290,55);
		line(360,25,360,55);
		line(430,25,430,55);
		SetColor(white);
		Outtextxy(170,40, 'dLAM');
		Outtextxy(240,40, 'TAY1');
		Outtextxy(310,40, 'TAY2');
		Outtextxy(380,40, 'LAMOB');
		Outtextxy(450,40, 'KMIN');

 end
else if xIND=2 then
 begin

    Setfillstyle(1, green);
    Bar(150,65,350,95);
		SetColor(red);
		line(150,65,150,95);
		line(250,65,250,95);
		SetColor(white);
		Outtextxy(170,80, 'Graphic');
		Outtextxy(270,80, 'Table');

 end;
End;
  
  
Procedure Display.ReadMe;
Var
 f2:text;
 i:Integer;
 s:string;
Begin
 assign(f2,'readme.txt');
 reset(f2);

 Setfillstyle(1, red);
 Bar(170,10,GetMaxX-20,230);
 Setfillstyle(1, green);
 Bar(180,20,GetMaxX-30,220);
 
 For i:=0 To 5 Do
  Begin
   readln(f2, s);
   outtextxy(190, 60+i*20, s );
  End;
 readkey;
 close(f2);
End;
  
  
  
Procedure Display.SelectButtonMain;  
begin
Repeat

	k := readkey;
		case k of

    #80 : begin  {vniz}
			
			      index:=index+1;
			      if index>5 then index:=1;
			      if index<1 then index:=5;
		      	xDisplay.ShowMenu;
			      xDisplay.ButON(index);
 
				  end;
    #72 :  begin   {vverh}
			
			      index:=index-1;
			      if index>5 then index:=1;
			      if index<1 then index:=5;
			      xDisplay.ShowMenu;
			      xDisplay.ButON(index);
			
			     end;
		#27: halt;
		end;
  until (k = #13);

End;	
	
	

Procedure Display.SelectButtonPodMenu(xIND:integer);  
begin	

if xIND=1 then
 begin

	  xDisplay.ShowPodMenu(1);
    Repeat
	  k := readkey;
		case k of
			#77 : begin  		{vpravo}
			    	 index1:=index1+1;
					   if index1>10 then index1:=6;
					   if index1<6 then index1:=10;
					   xDisplay.ShowMenu;
					   xDisplay.ShowPodMenu(1);
					   xDisplay.ButON(index1);
			      end;
			#75 : begin        {vlevo}
			       index1:=index1-1;
					   if index1>10 then index1:=6;
					   if index1<6 then index1:=10;
					   xDisplay.ShowMenu;
					   xDisplay.ShowPodMenu(1);
					   xDisplay.ButON(index1);
				    end;
			#27: halt;
		  end;
    until (k = #13);


 Setfillstyle(1, red);
 Bar(170,60,GetMaxX-20,230);
 Setfillstyle(1, green);
 Bar(180,70,GetMaxX-30,220);
	
	
    case index1 of
			6 : begin
            outtextXY(200,100,'Write value of dLAM and press ENTER:');
            outtextXY(200,115,'dLAM =');
            str_data:=InputData;
            val(str_data, real_data, code);
            if (code = 0) and (real_data >= 0.1) and (real_data <= 1.5) then
               xIst1.dLAM := real_data
            else
              begin
                outtextXY(200,130,'BAD VALUE!');
                outtextXY(200,145,'dLAM = 0.1');
                xIst1.dLAM := 0.1;
                readkey;
              end;
          end;
			7 : begin
            outtextXY(200,100,'Write value of TAY1 and press ENTER:');
            outtextXY(200,115,'TAY1 =');
            str_data:=InputData;
            val(str_data, real_data, code);
            if (code = 0) and (real_data > 0) then
               xIst2.TAY2_1 := real_data
            else
              begin
                outtextXY(200,130,'BAD VALUE!');
                outtextXY(200,145,'TAY1 = 0.1');
                xIst2.TAY2_1 := 0.1;
                readkey;
              end;
				   end;
			8 : begin
            outtextXY(200,100,'Write value of TAY2 and press ENTER:');
            outtextXY(200,115,'TAY2 =');
            str_data:=InputData;
            val(str_data, real_data, code);
            if (code = 0) and (real_data > 0) then
               xIst2.TAY2_2 := real_data
            else
              begin
                outtextXY(200,130,'BAD VALUE!');
                outtextXY(200,145,'TAY2 = 0.5');
                xIst2.TAY2_2 := 0.5;
                readkey;
              end;
			    end;
      9 : begin
            outtextXY(200,100,'Write value of LAMOB and press ENTER:');
            outtextXY(200,115,'LAMOB =');
            str_data:=InputData;
            val(str_data, real_data, code);
            if (code = 0) and (real_data > 0) then
               xDevice.LAMOB := real_data
            else
              begin
                outtextXY(200,130,'BAD VALUE!');
                outtextXY(200,145,'LAMOB = 1');
                xDevice.LAMOB := 1;
                readkey;
              end;
				   end;
      10 : begin
             outtextXY(200,100,'Write value of KMIN and press ENTER:');
             outtextXY(200,115,'KMIN =');
             str_data:=InputData;
             val(str_data, int_data, code);
             if (code = 0) and (int_data > 0) and (int_data < 4000) then
                xMain.KMIN := int_data
             else
               begin
                 outtextXY(200,130,'BAD VALUE!');
                 outtextXY(200,145,'KMIN = 1000');
                 xMain.KMIN := 1000;
                 readkey;
               end;
				    end;
		  end;

 end
else if xIND=2 then
 begin

	    xDisplay.ShowPodMenu(2);
	    Repeat
	    k := readkey;
		  case k of
			#77 : begin  		{vpravo}

			    	 index2:=index2+1;
					   if index2>12 then index2:=11;
					   if index2<11 then index2:=12;
					   xDisplay.ShowMenu;
				   	 xDisplay.ShowPodMenu(2);
					   xDisplay.ButON(index2);

			      end;
			#75 :  begin       {vlevo}

				      index2:=index2-1;
				    	if index2>12 then index2:=11;
					    if index2<11 then index2:=12;
					    xDisplay.ShowMenu;
					    xDisplay.ShowPodMenu(2);
					    xDisplay.ButON(index2);

				     end;
			#27: halt;
		  end;
    until (k = #13);


	  if index2=11 then
		begin
			gflag:=true;
			ShowPodMenu(2);
			Outtextxy(170,80, 'Graphic #');
			readkey;
		end
	  else if index2=12 then
		begin
			gflag:=false;
			ShowPodMenu(2);
			Outtextxy(270,80, 'Table #');
			readkey;
		end;
 end;

End;
	
	
	
Function Display.InputData : string;
var
   i : integer;
   c : char;
   res : string;
Begin
     res := '';
     i := 0;
     Repeat
           c := readkey;
           i:=i+1;
           if c <> #13 then
              begin
                   outtextxy(250 + 8 * i, 115, c);
                   res := res + c;
              end;
     Until c = #13;
     setfillstyle(1, 0);
     InputData := res;
end;	
	
	
BEGIN

END.