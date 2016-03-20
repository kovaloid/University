PROGRAM CMO;
USES new_crt, graph, func, schedule, menu;
LABEL START;
VAR
   d, m, i : integer;
   f1:text;
BEGIN
   clrscr;
   writeln('Enter type of 1 stream ( 1-ravn ; 2-prost )');
   readln(xIst2.switch);
   DetectGraph(d, m);
   InitGraph(d, m, '');
   
   START:

   xMain.Init(xMain.KMIN, xMain.NMIN, xMain.TPOST_NMIN, xMain.BOTK, xMain.MTOG);
   xDisplay.Init;
   xGrafMaker.Init;
   xIst1.LAM1:= 0.5;
   xDisplay.ShowMenu;

while true do begin
   xDisplay.SelectButtonMain;
   
   case xDisplay.index of
		1 : begin
		
            xDisplay.SelectButtonPodMenu(1);
            xDisplay.ShowMenu;
			  
        end;
		2 : begin
		
	          xDisplay.SelectButtonPodMenu(2); 
	          xDisplay.ShowMenu;
			  
        end;
		3 : begin

              assign(f1,'output.txt');
              rewrite(f1);
              writeln(f1,'LAM1  ','   P1   ','   P2   ','   M1   ','   M2   ');
              for i:=0 to 36 do write(f1,'_');
              writeln(f1);

              cleardevice;
              if xDisplay.gflag then xGrafMaker.DrawPlate
              else xGrafMaker.MakeTable;
              i := 1;
			  
              REPEAT 
                xMain.SIMULATE;
				
                xMain.BOTK[1, i] := xIst1.KOTK / xIst1.KOL;
                xMain.BOTK[2, i] := xIst2.KOTK / xIst2.KOL;
                xMain.MTOG[1, i] := xIst1.TOG / xIst1.KOBR;
                xMain.MTOG[2, i] := xIst2.TOG / xIst2.KOBR;
				
                write(f1,xIst1.LAM1:2:2,'    ');
			          write(f1,xMain.BOTK[1,i]:2:2,'    ',xMain.BOTK[2,i]:2:2,'    ');
                writeln(f1,xMain.MTOG[1,i]:2:2,'    ',xMain.MTOG[2,i]:2:2);
         

                if xDisplay.gflag then
                   begin
					           xGrafMaker.DrawLine(xIst1.LAM1, xMain.BOTK[1, i], 1, 1, i);
					           xGrafMaker.DrawLine(xIst1.LAM1, xMain.BOTK[2, i], 1, 2, i);
					           xGrafMaker.DrawLine(xIst1.LAM1, xMain.MTOG[1, i], 2, 1, i);
					           xGrafMaker.DrawLine(xIst1.LAM1, xMain.MTOG[2, i], 2, 2, i);
			             end
                else
		               begin
					           xGrafMaker.MakeData(xMain.BOTK[1, i], 1, 1);
					           xGrafMaker.MakeData(xMain.BOTK[2, i], 1, 2);
					           xGrafMaker.MakeData(xMain.MTOG[1, i], 2, 1);
					           xGrafMaker.MakeData(xMain.MTOG[2, i], 2, 2);
		               end;
				   
				        i:=i+1;
                xIst1.LAM1 := xIst1.LAM1 + xIst1.dLAM;
              UNTIL (xIst1.LAM1 > 1.6);
	  
              readkey;
              cleardevice;
              SetColor(white);
              OutTextXY(GetMaxX div 3,20,'PRESS ANY KEY...');
              readkey;
              close(f1);
              goto START;
           end;		

		4 : xDisplay.ReadMe;
		5 : begin
          CloseGraph;
          exit;
        end;
		   
   end;
end;

END.