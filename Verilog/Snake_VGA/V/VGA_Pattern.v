module	VGA_Pattern	(	//	Read Out Side
						oRed,oGreen,oBlue,
						iVGA_X,iVGA_Y,
						iVGA_CLK,
						//	Control Signals
						iRST_n,
						iColor_SW,
						myX,myY,
						myX2,myY2,
						myX3,myY3,
						myX4,myY4,
						myX5,myY5,
						myX6,myY6,
						myX7,myY7,
						myX8,myY8,
						myX9,myY9,
						myX10,myY10,
						myX11,myY11,
						myX12,myY12,
						flag	);
//	Read Out Side
output	reg	[9:0]	oRed;
output	reg	[9:0]	oGreen;
output	reg	[9:0]	oBlue;
input	[9:0]		iVGA_X;
input	[9:0]		iVGA_Y;
input	[9:0]		myX,myY;
input	[9:0]		myX2,myY2;
input	[9:0]		myX3,myY3;
input	[9:0]		myX4,myY4;
input	[9:0]		myX5,myY5;
input	[9:0]		myX6,myY6;
input	[9:0]		myX7,myY7;
input	[9:0]		myX8,myY8;
input	[9:0]		myX9,myY9;
input	[9:0]		myX10,myY10;
input	[9:0]		myX11,myY11;
input	[9:0]		myX12,myY12;
input	[1:0]		flag;
input				iVGA_CLK;
//	Control Signals
input				iRST_n;
input				iColor_SW;

always@(posedge iVGA_CLK)
begin
	if (flag == 0)
	begin
		oRed <=	(((iVGA_X>myX && iVGA_X<myX+20) && (iVGA_Y>myY && iVGA_Y<myY+20))    || 
				((iVGA_X>myX2 && iVGA_X<myX2+20) && (iVGA_Y>myY2 && iVGA_Y<myY2+20)) || 
				((iVGA_X>myX3 && iVGA_X<myX3+20) && (iVGA_Y>myY3 && iVGA_Y<myY3+20)) ||
				((iVGA_X>myX4 && iVGA_X<myX4+20) && (iVGA_Y>myY4 && iVGA_Y<myY4+20)) ||					
			//frame
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=20))    ||		//top
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=460 && iVGA_Y<=480)) ||		//bottom
				((iVGA_X>=0 && iVGA_X<=20) && (iVGA_Y>=0 && iVGA_Y<=480))    ||		//left
				((iVGA_X>=620 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=480)) ||		//right
			//leaf
				((iVGA_X>=318 && iVGA_X<=322) && (iVGA_Y>=202 && iVGA_Y<=206)) ||
				((iVGA_X>=320 && iVGA_X<=322) && (iVGA_Y>=200 && iVGA_Y<=202)) ||
				((iVGA_X>=322 && iVGA_X<=326) && (iVGA_Y>=198 && iVGA_Y<=204)) ||
				((iVGA_X>=324 && iVGA_X<=328) && (iVGA_Y>=196 && iVGA_Y<=200)))	?	0	: 15;
					  
			//background	
		oBlue <= ((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=480))	?	0	: 15;
	
		oGreen <= (((iVGA_X>myX && iVGA_X<myX+20) && (iVGA_Y>myY && iVGA_Y<myY+20))  || 
				((iVGA_X>myX2 && iVGA_X<myX2+20) && (iVGA_Y>myY2 && iVGA_Y<myY2+20)) || 
				((iVGA_X>myX3 && iVGA_X<myX3+20) && (iVGA_Y>myY3 && iVGA_Y<myY3+20)) ||
				((iVGA_X>myX4 && iVGA_X<myX4+20) && (iVGA_Y>myY4 && iVGA_Y<myY4+20)) ||
			//frame
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=20))    ||		//top
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=460 && iVGA_Y<=480)) ||		//bottom
				((iVGA_X>=0 && iVGA_X<=20) && (iVGA_Y>=0 && iVGA_Y<=480))    ||		//left
				((iVGA_X>=620 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=480)) ||		//right
			//door
				((iVGA_X>20 && iVGA_X<30) && (iVGA_Y>95 && iVGA_Y<100))  ||
				((iVGA_X>20 && iVGA_X<30) && (iVGA_Y>120 && iVGA_Y<125)) ||
			//apple (300-340 && 200-240)
				((iVGA_X>=304 && iVGA_X<=332) && (iVGA_Y>=208 && iVGA_Y<=234)) ||
				((iVGA_X>=308 && iVGA_X<=332) && (iVGA_Y>=234 && iVGA_Y<=238)) ||
				((iVGA_X>=332 && iVGA_X<=336) && (iVGA_Y>=226 && iVGA_Y<=234)) ||
				((iVGA_X>=332 && iVGA_X<=334) && (iVGA_Y>=224 && iVGA_Y<=226)) ||
				((iVGA_X>=332 && iVGA_X<=334) && (iVGA_Y>=234 && iVGA_Y<=236)) ||
				((iVGA_X>=336 && iVGA_X<=338) && (iVGA_Y>=228 && iVGA_Y<=230)) ||
				((iVGA_X>=306 && iVGA_X<=308) && (iVGA_Y>=234 && iVGA_Y<=236)) ||
				((iVGA_X>=310 && iVGA_X<=316) && (iVGA_Y>=238 && iVGA_Y<=240)) ||
				((iVGA_X>=324 && iVGA_X<=330) && (iVGA_Y>=238 && iVGA_Y<=240)) ||
				((iVGA_X>=300 && iVGA_X<=302) && (iVGA_Y>=214 && iVGA_Y<=226)) ||
				((iVGA_X>=302 && iVGA_X<=304) && (iVGA_Y>=210 && iVGA_Y<=232)) ||
				((iVGA_X>=308 && iVGA_X<=316) && (iVGA_Y>=206 && iVGA_Y<=208)) ||
				((iVGA_X>=324 && iVGA_X<=332) && (iVGA_Y>=206 && iVGA_Y<=208)) ||
				((iVGA_X>=332 && iVGA_X<=336) && (iVGA_Y>=208 && iVGA_Y<=212)) ||
				((iVGA_X>=332 && iVGA_X<=334) && (iVGA_Y>=212 && iVGA_Y<=214)))	?	0	: 15;
	end
	if(flag == 1)
	begin
		oRed <= (((iVGA_X>myX && iVGA_X<myX+20) && (iVGA_Y>myY && iVGA_Y<myY+20))    || 
				((iVGA_X>myX2 && iVGA_X<myX2+20) && (iVGA_Y>myY2 && iVGA_Y<myY2+20)) || 
				((iVGA_X>myX3 && iVGA_X<myX3+20) && (iVGA_Y>myY3 && iVGA_Y<myY3+20)) ||
				((iVGA_X>myX4 && iVGA_X<myX4+20) && (iVGA_Y>myY4 && iVGA_Y<myY4+20)) ||
				((iVGA_X>myX5 && iVGA_X<myX5+20) && (iVGA_Y>myY5 && iVGA_Y<myY5+20)) ||
				((iVGA_X>myX6 && iVGA_X<myX6+20) && (iVGA_Y>myY6 && iVGA_Y<myY6+20)) ||	
				((iVGA_X>myX7 && iVGA_X<myX7+20) && (iVGA_Y>myY7 && iVGA_Y<myY7+20)) ||	
				((iVGA_X>myX8 && iVGA_X<myX8+20) && (iVGA_Y>myY8 && iVGA_Y<myY8+20)) ||											
			//frame
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=20))    ||
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=460 && iVGA_Y<=480)) ||		
				((iVGA_X>=0 && iVGA_X<=20) && (iVGA_Y>=0 && iVGA_Y<=480))    ||	
				((iVGA_X>=620 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=480)))	?	0	: 15;
					  
			//background
		oBlue <= ((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=480))	?	0	: 15;
	
		oGreen <= (((iVGA_X>myX && iVGA_X<myX+20) && (iVGA_Y>myY && iVGA_Y<myY+20))  || 
				((iVGA_X>myX2 && iVGA_X<myX2+20) && (iVGA_Y>myY2 && iVGA_Y<myY2+20)) || 
				((iVGA_X>myX3 && iVGA_X<myX3+20) && (iVGA_Y>myY3 && iVGA_Y<myY3+20)) ||
				((iVGA_X>myX4 && iVGA_X<myX4+20) && (iVGA_Y>myY4 && iVGA_Y<myY4+20)) ||
				((iVGA_X>myX5 && iVGA_X<myX5+20) && (iVGA_Y>myY5 && iVGA_Y<myY5+20)) ||
				((iVGA_X>myX6 && iVGA_X<myX6+20) && (iVGA_Y>myY6 && iVGA_Y<myY6+20)) ||
				((iVGA_X>myX7 && iVGA_X<myX7+20) && (iVGA_Y>myY7 && iVGA_Y<myY7+20)) ||	
				((iVGA_X>myX8 && iVGA_X<myX8+20) && (iVGA_Y>myY8 && iVGA_Y<myY8+20)) ||
			//heart (160-200 && 300-340)	
				((iVGA_X>=160 && iVGA_X<=205) && (iVGA_Y>=305 && iVGA_Y<=320)) ||	
				((iVGA_X>=165 && iVGA_X<=180) && (iVGA_Y>=300 && iVGA_Y<=325)) ||
				((iVGA_X>=185 && iVGA_X<=200) && (iVGA_Y>=300 && iVGA_Y<=325)) ||
				((iVGA_X>=170 && iVGA_X<=195) && (iVGA_Y>=325 && iVGA_Y<=330)) ||	
				((iVGA_X>=175 && iVGA_X<=190) && (iVGA_Y>=330 && iVGA_Y<=335)) ||
				((iVGA_X>=180 && iVGA_X<=185) && (iVGA_Y>=320 && iVGA_Y<=340)) ||
			//door
				((iVGA_X>20 && iVGA_X<30) && (iVGA_Y>95 && iVGA_Y<100))  ||
				((iVGA_X>20 && iVGA_X<30) && (iVGA_Y>120 && iVGA_Y<125)) ||
			//frame
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=20))    ||
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=460 && iVGA_Y<=480)) ||	
				((iVGA_X>=0 && iVGA_X<=20) && (iVGA_Y>=0 && iVGA_Y<=480))    ||	
				((iVGA_X>=620 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=480)))	?	0	: 15;
	end
	if (flag == 2)
	begin
		oRed <= (((iVGA_X>myX && iVGA_X<myX+20) && (iVGA_Y>myY && iVGA_Y<myY+20))    || 
				((iVGA_X>myX2 && iVGA_X<myX2+20) && (iVGA_Y>myY2 && iVGA_Y<myY2+20)) || 
				((iVGA_X>myX3 && iVGA_X<myX3+20) && (iVGA_Y>myY3 && iVGA_Y<myY3+20)) ||
				((iVGA_X>myX4 && iVGA_X<myX4+20) && (iVGA_Y>myY4 && iVGA_Y<myY4+20)) ||
				((iVGA_X>myX5 && iVGA_X<myX5+20) && (iVGA_Y>myY5 && iVGA_Y<myY5+20)) ||
				((iVGA_X>myX6 && iVGA_X<myX6+20) && (iVGA_Y>myY6 && iVGA_Y<myY6+20)) ||	
				((iVGA_X>myX7 && iVGA_X<myX7+20) && (iVGA_Y>myY7 && iVGA_Y<myY7+20)) ||	
				((iVGA_X>myX8 && iVGA_X<myX8+20) && (iVGA_Y>myY8 && iVGA_Y<myY8+20)) ||	
				((iVGA_X>myX9 && iVGA_X<myX9+20) && (iVGA_Y>myY9 && iVGA_Y<myY9+20)) ||	
				((iVGA_X>myX10 && iVGA_X<myX10+20) && (iVGA_Y>myY10 && iVGA_Y<myY10+20)) ||
				((iVGA_X>myX11 && iVGA_X<myX11+20) && (iVGA_Y>myY11 && iVGA_Y<myY11+20)) ||	
				((iVGA_X>myX12 && iVGA_X<myX12+20) && (iVGA_Y>myY12 && iVGA_Y<myY12+20)) ||							
			//frame
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=20))    ||
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=460 && iVGA_Y<=480)) ||		
				((iVGA_X>=0 && iVGA_X<=20) && (iVGA_Y>=0 && iVGA_Y<=480))    ||	
				((iVGA_X>=620 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=480)))	?	0	: 15;
					  
			//background
		oBlue <= ((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=480))	?	0	: 15;	
	
		oGreen <= (((iVGA_X>myX && iVGA_X<myX+20) && (iVGA_Y>myY && iVGA_Y<myY+20))  || 
				((iVGA_X>myX2 && iVGA_X<myX2+20) && (iVGA_Y>myY2 && iVGA_Y<myY2+20)) || 
				((iVGA_X>myX3 && iVGA_X<myX3+20) && (iVGA_Y>myY3 && iVGA_Y<myY3+20)) ||
				((iVGA_X>myX4 && iVGA_X<myX4+20) && (iVGA_Y>myY4 && iVGA_Y<myY4+20)) ||
				((iVGA_X>myX5 && iVGA_X<myX5+20) && (iVGA_Y>myY5 && iVGA_Y<myY5+20)) ||
				((iVGA_X>myX6 && iVGA_X<myX6+20) && (iVGA_Y>myY6 && iVGA_Y<myY6+20)) ||
				((iVGA_X>myX7 && iVGA_X<myX7+20) && (iVGA_Y>myY7 && iVGA_Y<myY7+20)) ||	
				((iVGA_X>myX8 && iVGA_X<myX8+20) && (iVGA_Y>myY8 && iVGA_Y<myY8+20)) ||
				((iVGA_X>myX9 && iVGA_X<myX9+20) && (iVGA_Y>myY9 && iVGA_Y<myY9+20)) ||	
				((iVGA_X>myX10 && iVGA_X<myX10+20) && (iVGA_Y>myY10 && iVGA_Y<myY10+20)) ||
				((iVGA_X>myX11 && iVGA_X<myX11+20) && (iVGA_Y>myY11 && iVGA_Y<myY11+20)) ||	
				((iVGA_X>myX12 && iVGA_X<myX12+20) && (iVGA_Y>myY12 && iVGA_Y<myY12+20)) ||
			//door
				((iVGA_X>20 && iVGA_X<30) && (iVGA_Y>95 && iVGA_Y<100))  ||
				((iVGA_X>20 && iVGA_X<30) && (iVGA_Y>120 && iVGA_Y<125)) ||
			//frame
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=20))    ||
				((iVGA_X>=0 && iVGA_X<=640) && (iVGA_Y>=460 && iVGA_Y<=480)) ||	
				((iVGA_X>=0 && iVGA_X<=20) && (iVGA_Y>=0 && iVGA_Y<=480))    ||	
				((iVGA_X>=620 && iVGA_X<=640) && (iVGA_Y>=0 && iVGA_Y<=480)))	?	0	: 15;
	end
end
endmodule