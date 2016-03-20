UNIT func;
INTERFACE
type

	  bt=array[1..2] of real ;
    bn=array[1..2] of integer;
    res=array[1..2, 1..11] of real;
	
    Buffer=object
	    INDBUF,NOMBUF:integer;
      BUFT:bt;
      BUFN:bn;
      Constructor Init(var xINDBUF,xNOMBUF:integer;var xBUFT:bt; var xBUFN:bn);
      Procedure Put(var xINDBUF:integer;var xBUFT:bt; var xBUFN:bn;xTPOST:real;xNMIN:Integer);
      Procedure Take(var xINDBUF:Integer;var xBUFT : bt; var xBUFN : bn);
    end;

    Source=object 
      switch:integer;
      KOL, KOBR, KOTK, NUM : Integer;
      TPOST, TOG, LAM1, dLAM, TAY2_1, TAY2_2, TN : Real;
      Constructor Init(var xKOL, xKOBR, xKOTK : Integer;var xTPOST, xTN, xTOG: Real);
      Procedure MakeNext(var xKOL : Integer;var xTPOST : Real;xLAM1, xTAY2_1, xTAY2_2 : Real; xNUM : Integer);
    end;

    Device=object
	    THO, TAYOB, LAMOB, TOSV, TOSV_LAST : Real;
      NOMOB : Integer;
      Constructor Init(var xTOSV, xTOSV_LAST, xTHO, xTAYOB: Real; var xNOMOB : Integer);
      Procedure MakeWork(var xTOSV, xTOSV_LAST : Real; xTHO, xLAMOB, xTAYOB : Real);
    end;
	 
	  Main=object
	    KMIN, NMIN: Integer;
      TPOST_NMIN : Real;
      BOTK, MTOG : res;
      Constructor Init(var xKMIN, xNMIN : Integer; var xTPOST_NMIN : Real; xP,xMTOG : res);
	    Procedure Simulate;
    end;

Var
    xIst1, xIst2 : Source;
    xDevice : Device;
    xBuffer : Buffer;
    xMain : Main;

IMPLEMENTATION

  Constructor Source.Init(var xKOL, xKOBR, xKOTK : Integer; var xTPOST, xTN, xTOG: Real);
       Begin
         xKOL := 0;
         xKOBR := 0;
         xKOTK := 0;
         xTPOST := 0;
         xTN := 0;
         xTOG := 0;
       End;

  Procedure Source.MakeNext(var xKOL : Integer; var xTPOST : Real; xLAM1, xTAY2_1, xTAY2_2 : Real; xNUM : Integer);
       Begin
         If xNUM = 1 Then
		       xTPOST := xTPOST + (-1) / xLAM1 * ln(random)
         Else If xNUM = 2 Then
	         If switch = 1 Then
              xTPOST := xTPOST + xTAY2_1+(xTAY2_2-xTAY2_1)*random
	         Else
	            xTPOST := xTPOST - ln(random);
         KOL:=KOL+1;
       End;

	   {************************************************************}
	   
    Constructor Device.Init(var xTOSV, xTOSV_LAST, xTHO, xTAYOB : Real; var xNOMOB : Integer);
       Begin
         xTOSV := 0;
         xTOSV_LAST := 0;
         xTHO := 0;
         xTAYOB := 0;
         xNOMOB := 0;
       End;

    Procedure Device.MakeWork(var xTOSV, xTOSV_LAST : Real; xTHO, xLAMOB, xTAYOB : Real);
       Begin
         xTOSV_LAST := THO;
		     xTAYOB := (-1) / xLAMOB * ln(random);
         xTOSV := xTOSV + xTAYOB;
       End;

	   {************************************************************}
	   
    Constructor Buffer.Init(var xINDBUF, xNOMBUF : Integer; var xBUFT : bt; var xBUFN : bn);
       Var
         i : Integer;
       Begin
         xINDBUF := 0;
         xNOMBUF := 1;
         For i := 1 To 2 Do
           Begin
             xBUFT[i] := 0;
             xBUFN[i] := 0;
           End;
       End;

    Procedure Buffer.Put(var xINDBUF : Integer; var xBUFT : bt; var xBUFN : bn; xTPOST : Real; xNMIN : Integer);
       Begin
         xINDBUF:=xINDBUF+1;
         xBUFT[xINDBUF] := xTPOST;
         xBUFN[xINDBUF] := xNMIN;
       End;

    Procedure Buffer.Take(var xINDBUF : Integer; var xBUFT : bt; var xBUFN : bn);
      Begin	  
        If (xINDBUF = (NOMBUF + 1)) Then
          Begin
            xBUFT[NOMBUF] := xBUFT[NOMBUF+1];
            xBUFN[NOMBUF] := xBUFN[NOMBUF+1];
          End;  
        xBUFT[xINDBUF] := 0;
        xBUFN[xINDBUF] := 0;
        xINDBUF:=xINDBUF-1;
      End;

	  {************************************************************}
	  
    Constructor Main.Init(var xKMIN, xNMIN : Integer; var xTPOST_NMIN : Real; xP, xMTOG : res);
      Var
        i : Integer;
      Begin
        xKMIN := 1000;
        xNMIN := 0;
        xTPOST_NMIN := 0;
        For i := 1 to 11 do
          Begin
            xP[1, i] := 0;
            xP[2, i] := 0;
            xMTOG[1, i] := 0;
            xMTOG[2, i] := 0;
          End;
      End;

	  Procedure Main.Simulate;
      Begin	  
	       Randomize;

         xIst1.Init(xIst1.KOL, xIst1.KOBR, xIst1.KOTK, xIst1.TPOST, xIst1.TN, xIst1.TOG);
         xIst2.Init(xIst2.KOL, xIst2.KOBR, xIst2.KOTK, xIst2.TPOST, xIst2.TN, xIst2.TOG);
         xDevice.Init(xDevice.TOSV, xDevice.TOSV_LAST, xDevice.THO, xDevice.TAYOB, xDevice.NOMOB);
         xBuffer.Init(xBuffer.INDBUF, xBuffer.NOMBUF, xBuffer.BUFT, xBuffer.BUFN);
         xIst1.MakeNext(xIst1.KOL, xIst1.TPOST, xIst1.LAM1, 0, 0, xIst1.NUM);
         xIst2.MakeNext(xIst2.KOL, xIst2.TPOST, 0, xIst2.TAY2_1, xIst2.TAY2_2, xIst2.NUM);
	  
	 
                 REPEAT
				 
                   if (xIst1.TPOST < xIst2.TPOST) then
                     begin
                       xMain.NMIN := xIst1.NUM;
                       xMain.TPOST_NMIN := xIst1.TPOST;
                     end
                   else
                     begin
                       xMain.NMIN := xIst2.NUM;
                       xMain.TPOST_NMIN := xIst2.TPOST;
                     end;
					 
					 
                if (xDevice.TOSV < xMain.TPOST_NMIN) then
                     if (xBuffer.INDBUF = 0) then    {BUFFER HAVE WORK}
                        begin
                         xDevice.THO := xMain.TPOST_NMIN;
                         xDevice.MakeWork(xDevice.TOSV, xDevice.TOSV_LAST, xDevice.THO, xDevice.LAMOB, xDevice.TAYOB);
                         if (xMain.NMIN = 1) then
                           begin
                             xIst1.KOBR:=xIst1.KOBR+1;
                             xIst1.TN := xIst1.TN + (xDevice.TOSV - xIst1.TPOST);
                             xIst1.MakeNext(xIst1.KOL,xIst1.TPOST,xIst1.LAM1,0, 0,xIst1.NUM);
                           end
                         else
                           begin
                            xIst2.KOBR:=xIst2.KOBR+1;
                            xIst2.TN := xIst2.TN + (xDevice.TOSV - xIst2.TPOST);
                            xIst2.MakeNext(xIst2.KOL, xIst2.TPOST, 0, xIst2.TAY2_1, xIst2.TAY2_2, xIst2.NUM);
                           end;
                        end
                     else                   {BUFFER NO WORK}
                       begin
                         xBuffer.Take(xBuffer.INDBUF, xBuffer.BUFT, xBuffer.BUFN);
                         xDevice.THO := xDevice.TOSV;
                         xDevice.MakeWork(xDevice.TOSV, xDevice.TOSV_LAST, xDevice.THO, xDevice.LAMOB, xDevice.TAYOB);
                         if (xBuffer.BUFN[xBuffer.NOMBUF] = 1) then
                           begin
                             xIst1.KOBR:=xIst1.KOBR+1;
                             xIst1.TN := xIst1.TN + (xDevice.TOSV - xBuffer.BUFT[xBuffer.NOMBUF]);
                             xIst1.TOG := xIst1.TOG + (xDevice.THO - xBuffer.BUFT[xBuffer.NOMBUF]);
                           end
                         else if (xBuffer.BUFN[xBuffer.NOMBUF] = 2) then
                           begin
                             xIst2.KOBR:=xIst2.KOBR+1;
                             xIst2.TN := xIst2.TN + (xDevice.TOSV - xBuffer.BUFT[xBuffer.NOMBUF]);
                             xIst2.TOG := xIst2.TOG + (xDevice.THO - xBuffer.BUFT[xBuffer.NOMBUF]);
                           end;
                       end
                else				 {BUFFER EMPTY}
                   if (xBuffer.INDBUF < 2) then 
                     if (xMain.NMIN = 1) then
                       begin
                         xBuffer.Put(xBuffer.INDBUF, xBuffer.BUFT, xBuffer.BUFN, xMain.TPOST_NMIN, xMain.NMIN);
                         xIst1.MakeNext(xIst1.KOL, xIst1.TPOST, xIst1.LAM1, 0, 0, xIst1.NUM);
                       end
                     else
                       begin
                         xBuffer.Put(xBuffer.INDBUF, xBuffer.BUFT, xBuffer.BUFN, xMain.TPOST_NMIN, xMain.NMIN);
                         xIst2.MakeNext(xIst2.KOL, xIst2.TPOST, 0, xIst2.TAY2_1, xIst2.TAY2_2, xIst2.NUM);
                       end
                   else					{BUFFER NO EMPTY}
                     if (xMain.NMIN = 1) then
                       begin
                         xIst1.KOTK:=xIst1.KOTK+1;
                         xIst1.MakeNext(xIst1.KOL, xIst1.TPOST, xIst1.LAM1, 0, 0, xIst1.NUM);
                       end
                     else
                       begin
                         xIst2.KOTK:=xIst2.KOTK+1;
                         xIst2.MakeNext(xIst2.KOL, xIst2.TPOST, 0, xIst2.TAY2_1, xIst2.TAY2_2, xIst2.NUM);
                       end;
               UNTIL ((xIst1.KOL >= xMain.KMIN )and(xIst2.KOL>=xMain.KMIN));
			   
      End;

BEGIN

   xIst1.Init(xIst1.KOL, xIst1.KOBR, xIst1.KOTK, xIst1.TPOST, xIst1.TN, xIst1.TOG);
   xIst2.Init(xIst2.KOL, xIst2.KOBR, xIst2.KOTK, xIst2.TPOST, xIst2.TN, xIst2.TOG);
   xDevice.Init(xDevice.TOSV, xDevice.TOSV_LAST, xDevice.THO, xDevice.TAYOB, xDevice.NOMOB);
   xBuffer.Init(xBuffer.INDBUF, xBuffer.NOMBUF, xBuffer.BUFT, xBuffer.BUFN);
   xIst1.NUM:= 1;
   xIst2.NUM:= 2;
   xIst1.dLAM := 0.1;
   xIst2.TAY2_1:=0.1;
   xIst2.TAY2_2:=0.5;
   xDevice.LAMOB := 1;

END.