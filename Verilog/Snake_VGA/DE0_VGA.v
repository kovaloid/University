// --------------------------------------------------------------------
// Copyright (c) 2009 by Terasic Technologies Inc. 
// --------------------------------------------------------------------
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development 
//   Kits made by Terasic.  Other use of this code, including the selling 
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use 
//   or functionality of this code.
//
// --------------------------------------------------------------------
//           
//                     Terasic Technologies Inc
//                     356 Fu-Shin E. Rd Sec. 1. JhuBei City,
//                     HsinChu County, Taiwan
//                     302
//
//                     web: http://www.terasic.com/
//                     email: support@terasic.com
//
// --------------------------------------------------------------------
//
// Major Functions:	DE0 VGA
//
// --------------------------------------------------------------------
//
// Revision History :
// --------------------------------------------------------------------
//   Ver  :| Author            :| Mod. Date :| Changes Made:

// --------------------------------------------------------------------


module DE0_VGA
	(
		////////////////////	Clock Input	 	////////////////////	 
		CLOCK_50,						//	50 MHz
		CLOCK_50_2,						//	50 MHz
		////////////////////	Push Button		////////////////////
		BUTTON,							//	Pushbutton[2:0]
		////////////////////	DPDT Switch		////////////////////
		SW,								//	Toggle Switch[9:0]
		////////////////////	7-SEG Dispaly	////////////////////
		HEX0_D,							//	Seven Segment Digit 0
		HEX0_DP,						//	Seven Segment Digit DP 0
		HEX1_D,							//	Seven Segment Digit 1
		HEX1_DP,						//	Seven Segment Digit DP 1
		HEX2_D,							//	Seven Segment Digit 2
		HEX2_DP,						//	Seven Segment Digit DP 2
		HEX3_D,							//	Seven Segment Digit 3
		HEX3_DP,						//	Seven Segment Digit DP 3
		////////////////////////	LED		////////////////////////
		LEDG,							//	LED Green[9:0]
		////////////////////////	UART	////////////////////////
		UART_TXD,						//	UART Transmitter
		UART_RXD,						//	UART Receiver
		UART_CTS,						//	UART Clear To Send
		UART_RTS,						//	UART Request To Send
		/////////////////////	SDRAM Interface		////////////////
		DRAM_DQ,						//	SDRAM Data bus 16 Bits
		DRAM_ADDR,						//	SDRAM Address bus 13 Bits
		DRAM_LDQM,						//	SDRAM Low-byte Data Mask 
		DRAM_UDQM,						//	SDRAM High-byte Data Mask
		DRAM_WE_N,						//	SDRAM Write Enable
		DRAM_CAS_N,						//	SDRAM Column Address Strobe
		DRAM_RAS_N,						//	SDRAM Row Address Strobe
		DRAM_CS_N,						//	SDRAM Chip Select
		DRAM_BA_0,						//	SDRAM Bank Address 0
		DRAM_BA_1,						//	SDRAM Bank Address 1
		DRAM_CLK,						//	SDRAM Clock
		DRAM_CKE,						//	SDRAM Clock Enable
		////////////////////	Flash Interface		////////////////
		FL_DQ,							//	FLASH Data bus 15 Bits
		FL_DQ15_AM1,					//	FLASH Data bus Bit 15 or Address A-1
		FL_ADDR,						//	FLASH Address bus 22 Bits
		FL_WE_N,						//	FLASH Write Enable
		FL_RST_N,						//	FLASH Reset
		FL_OE_N,						//	FLASH Output Enable
		FL_CE_N,						//	FLASH Chip Enable
		FL_WP_N,						//	FLASH Hardware Write Protect
		FL_BYTE_N,						//	FLASH Selects 8/16-bit mode
		FL_RY,							//	FLASH Ready/Busy
		////////////////////	LCD Module 16X2		////////////////
		LCD_BLON,						//	LCD Back Light ON/OFF
		LCD_RW,							//	LCD Read/Write Select, 0 = Write, 1 = Read
		LCD_EN,							//	LCD Enable
		LCD_RS,							//	LCD Command/Data Select, 0 = Command, 1 = Data
		LCD_DATA,						//	LCD Data bus 8 bits
		////////////////////	SD_Card Interface	////////////////
		SD_DAT0,						//	SD Card Data 0
		SD_DAT3,						//	SD Card Data 3
		SD_CMD,							//	SD Card Command Signal
		SD_CLK,							//	SD Card Clock
		SD_WP_N,						//	SD Card Write Protect
		////////////////////	PS2		////////////////////////////
		PS2_KBDAT,						//	PS2 Keyboard Data
		PS2_KBCLK,						//	PS2 Keyboard Clock
		PS2_MSDAT,						//	PS2 Mouse Data
		PS2_MSCLK,						//	PS2 Mouse Clock
		////////////////////	VGA		////////////////////////////
		VGA_HS,							//	VGA H_SYNC
		VGA_VS,							//	VGA V_SYNC
		VGA_R,   						//	VGA Red[3:0]
		VGA_G,	 						//	VGA Green[3:0]
		VGA_B,  						//	VGA Blue[3:0]
		////////////////////	GPIO	////////////////////////////
		GPIO0_CLKIN,						//	GPIO Connection 0 Clock In Bus
		GPIO0_CLKOUT,					//	GPIO Connection 0 Clock Out Bus
		GPIO0_D,						//	GPIO Connection 0 Data Bus
		GPIO1_CLKIN,					//	GPIO Connection 1 Clock In Bus
		GPIO1_CLKOUT,					//	GPIO Connection 1 Clock Out Bus
		GPIO1_D							//	GPIO Connection 1 Data Bus
	);

////////////////////////	Clock Input	 	////////////////////////
input			CLOCK_50;				//	50 MHz
input			CLOCK_50_2;				//	50 MHz
////////////////////////	Push Button		////////////////////////
input	[2:0]	BUTTON;					//	Pushbutton[2:0]
////////////////////////	DPDT Switch		////////////////////////
input	[9:0]	SW;						//	Toggle Switch[9:0]
////////////////////////	7-SEG Dispaly	////////////////////////
output	[6:0]	HEX0_D;					//	Seven Segment Digit 0
output			HEX0_DP;				//	Seven Segment Digit DP 0
output	[6:0]	HEX1_D;					//	Seven Segment Digit 1
output			HEX1_DP;				//	Seven Segment Digit DP 1
output	[6:0]	HEX2_D;					//	Seven Segment Digit 2
output			HEX2_DP;				//	Seven Segment Digit DP 2
output	[6:0]	HEX3_D;					//	Seven Segment Digit 3
output			HEX3_DP;				//	Seven Segment Digit DP 3
////////////////////////////	LED		////////////////////////////
output	[9:0]	LEDG;					//	LED Green[9:0]
////////////////////////////	UART	////////////////////////////
output			UART_TXD;				//	UART Transmitter
input			UART_RXD;				//	UART Receiver
output			UART_CTS;				//	UART Clear To Send
input			UART_RTS;				//	UART Request To Send
///////////////////////		SDRAM Interface	////////////////////////
inout	[15:0]	DRAM_DQ;				//	SDRAM Data bus 16 Bits
output	[12:0]	DRAM_ADDR;				//	SDRAM Address bus 13 Bits
output			DRAM_LDQM;				//	SDRAM Low-byte Data Mask
output			DRAM_UDQM;				//	SDRAM High-byte Data Mask
output			DRAM_WE_N;				//	SDRAM Write Enable
output			DRAM_CAS_N;				//	SDRAM Column Address Strobe
output			DRAM_RAS_N;				//	SDRAM Row Address Strobe
output			DRAM_CS_N;				//	SDRAM Chip Select
output			DRAM_BA_0;				//	SDRAM Bank Address 0
output			DRAM_BA_1;				//	SDRAM Bank Address 1
output			DRAM_CLK;				//	SDRAM Clock
output			DRAM_CKE;				//	SDRAM Clock Enable
////////////////////////	Flash Interface	////////////////////////
inout	[14:0]	FL_DQ;					//	FLASH Data bus 15 Bits
inout			FL_DQ15_AM1;			//	FLASH Data bus Bit 15 or Address A-1
output	[21:0]	FL_ADDR;				//	FLASH Address bus 22 Bits
output			FL_WE_N;				//	FLASH Write Enable
output			FL_RST_N;				//	FLASH Reset
output			FL_OE_N;				//	FLASH Output Enable
output			FL_CE_N;				//	FLASH Chip Enable
output			FL_WP_N;				//	FLASH Hardware Write Protect
output			FL_BYTE_N;				//	FLASH Selects 8/16-bit mode
input			FL_RY;					//	FLASH Ready/Busy
////////////////////	LCD Module 16X2	////////////////////////////
inout	[7:0]	LCD_DATA;				//	LCD Data bus 8 bits
output			LCD_BLON;				//	LCD Back Light ON/OFF
output			LCD_RW;					//	LCD Read/Write Select, 0 = Write, 1 = Read
output			LCD_EN;					//	LCD Enable
output			LCD_RS;					//	LCD Command/Data Select, 0 = Command, 1 = Data
////////////////////	SD Card Interface	////////////////////////
inout			SD_DAT0;				//	SD Card Data 0
inout			SD_DAT3;				//	SD Card Data 3
inout			SD_CMD;					//	SD Card Command Signal
output			SD_CLK;					//	SD Card Clock
input			SD_WP_N;				//	SD Card Write Protect
////////////////////////	PS2		////////////////////////////////
inout		 	PS2_KBDAT;				//	PS2 Keyboard Data
inout			PS2_KBCLK;				//	PS2 Keyboard Clock
inout		 	PS2_MSDAT;				//	PS2 Mouse Data
inout			PS2_MSCLK;				//	PS2 Mouse Clock
////////////////////////	VGA			////////////////////////////
output			VGA_HS;					//	VGA H_SYNC
output			VGA_VS;					//	VGA V_SYNC
output	[3:0]	VGA_R;   				//	VGA Red[3:0]
output	[3:0]	VGA_G;	 				//	VGA Green[3:0]
output	[3:0]	VGA_B;   				//	VGA Blue[3:0]
////////////////////////	GPIO	////////////////////////////////
input	[1:0]	GPIO0_CLKIN;			//	GPIO Connection 0 Clock In Bus
output	[1:0]	GPIO0_CLKOUT;			//	GPIO Connection 0 Clock Out Bus
inout	[31:0]	GPIO0_D;				//	GPIO Connection 0 Data Bus
input	[1:0]	GPIO1_CLKIN;			//	GPIO Connection 1 Clock In Bus
output	[1:0]	GPIO1_CLKOUT;			//	GPIO Connection 1 Clock Out Bus
inout	[31:0]	GPIO1_D;				//	GPIO Connection 1 Data Bus

//=======================================================
//  REG/WIRE declarations
//=======================================================
//	All inout port turn to tri-state
assign			DRAM_DQ			=	16'hzzzz;
assign			FL_DQ			=	16'hzzzz;
assign			LCD_DATA		=	8'hzz;
assign			SD_DAT0			=	1'hz;
assign			SD_DAT3			=	1'hz;
assign			SD_CMD			=	1'hz;
assign			PS2_KBDAT		=	1'hz;
assign			PS2_KBCLK		=	1'hz;
assign			PS2_MSDAT		=	1'hz;
assign			PS2_MSCLK		=	1'hz;
assign			GPIO0_D			=	32'hzzzzzzzz;
assign			GPIO1_D			=	32'hzzzzzzzz;

////////////////////////	VGA			////////////////////////////
wire			VGA_CTRL_CLK;
wire	[9:0]	mVGA_X;
wire	[9:0]	mVGA_Y;

reg 	hand;
reg		up,down,left,right;
reg 	[1:0]	flag;
reg 	[9:0]	myX,myY;
reg		[9:0]	myX2,myY2;
reg		[9:0]	myX3,myY3;
reg		[9:0]	myX4,myY4;
reg		[9:0]	myX5,myY5;
reg 	[9:0]	myX6,myY6;
reg 	[9:0]	myX7,myY7;
reg 	[9:0]	myX8,myY8;
reg 	[9:0]	myX9,myY9;
reg 	[9:0]	myX10,myY10;
reg 	[9:0]	myX11,myY11;
reg 	[9:0]	myX12,myY12;
reg 	[25:0]	myCount;
reg 	[3:0]	dir;
integer	score0, score1;
integer	outgo;

wire	[9:0]	mVGA_R;
wire	[9:0]	mVGA_G;
wire	[9:0]	mVGA_B;
wire	[9:0]	sVGA_R;
wire	[9:0]	sVGA_G;
wire	[9:0]	sVGA_B;
assign	VGA_R	=	sVGA_R[3:0];
assign	VGA_G	=	sVGA_G[3:0];
assign	VGA_B	=	sVGA_B[3:0];

//=======================================================
//  Structural coding
//=======================================================

SEG7_LUT_4	u0
		(	.oSEG0(HEX0_D),
			.oSEG0_DP(HEX0_DP),
			.oSEG1(HEX1_D),
			.oSEG1_DP(HEX1_DP),
			.oSEG2(HEX2_D),
			.oSEG2_DP(HEX2_DP),
			.oSEG3(HEX3_D),
			.oSEG3_DP(HEX3_DP),
			.score0(score0),
			.score1(score1),
			.dir(dir)
		);

////////////////////////	VGA			////////////////////////////

VGA_CLK		u1
		(	.inclk0(CLOCK_50),
			.c0(VGA_CTRL_CLK)
		);

VGA_Ctrl	u2
		(	//	Host Side
			.oCurrent_X(mVGA_X),
			.oCurrent_Y(mVGA_Y),
			.iRed(mVGA_R),
			.iGreen(mVGA_G),
			.iBlue(mVGA_B),
			//	VGA Side
			.oVGA_R(sVGA_R),
			.oVGA_G(sVGA_G),
			.oVGA_B(sVGA_B),
			.oVGA_HS(VGA_HS),
			.oVGA_VS(VGA_VS),
			.oVGA_SYNC(),
			.oVGA_BLANK(),
			.oVGA_CLOCK(),
			//	Control Signal
			.iCLK(VGA_CTRL_CLK),
			.iRST_N(!SW[9])
		);

VGA_Pattern	u3
		(	//	Read Out Side
			.oRed(mVGA_R),
			.oGreen(mVGA_G),
			.oBlue(mVGA_B),
			.iVGA_X(mVGA_X),
			.iVGA_Y(mVGA_Y),
			.iVGA_CLK(VGA_CTRL_CLK),
			//	Control Signals
			.iRST_n(BUTTON[0]),
			.iColor_SW(SW[0]),
			.myX(myX),.myY(myY),
			.myX2(myX2),.myY2(myY2),
			.myX3(myX3),.myY3(myY3),
			.myX4(myX4),.myY4(myY4),
			.myX5(myX5),.myY5(myY5),
			.myX6(myX6),.myY6(myY6),
			.myX7(myX7),.myY7(myY7),
			.myX8(myX8),.myY8(myY8),
			.myX9(myX9),.myY9(myY9),
			.myX10(myX10),.myY10(myY10),
			.myX11(myX11),.myY11(myY11),
			.myX12(myX12),.myY12(myY12),
			.flag(flag)
		);
		
////////////////////////////	LED		////////////////////////////

LEDG_Driver	u4
		(	.oLED(LEDG),
			.iCLK(CLOCK_50),
			.iRST_n(!SW[9]),
			.outgo(outgo),
			.hand(hand)
		);

initial begin
	score0 = 0;
	score1 = 0;
	outgo = 0;
	myCount = 0;
	flag = 0;
	hand = 0;
	up = 0; down = 0;
	left = 0; right = 1;
	myX = 20; myY = 100;
	myX2 = 0; myY2 = 100;
	myX3 = 0; myY3 = 100;
	myX4 = 0; myY4 = 100;
	myX5 = 0; myY5 = 100;
	myX6 = 0; myY6 = 100;
	myX7 = 0; myY7 = 100;
	myX8 = 0; myY8 = 100;
	myX9 = 0; myY9 = 100;
	myX10 = 0; myY10 = 100;
	myX11 = 0; myY11 = 100;
	myX12 = 0; myY12 = 100;
end

always@(posedge VGA_CTRL_CLK)
begin
	if(myCount > 5000000)
	begin
		myCount = 0;
		if(SW[1])
		begin
			hand = 1;
			up = 0; down = 0;
			left = 0; right = 0;
			if(SW[0])
			begin
				dir <= 4'hb;
				if(!BUTTON[1])
				begin
					myX12 <= myX11; myY12 <= myY11;
					myX11 <= myX10; myY11 <= myY10;
					myX10 <= myX9; myY10 <= myY9;	
					myX9 <= myX8; myY9 <= myY8;
					myX8 <= myX7; myY8 <= myY7;	
					myX7 <= myX6; myY7 <= myY6;	
					myX6 <= myX5; myY6 <= myY5;		
					myX5 <= myX4; myY5 <= myY4;		
					myX4 <= myX3; myY4 <= myY3;		
					myX3 <= myX2; myY3 <= myY2;
					myX2 <= myX; myY2 <= myY;
					myY <= myY - 20;
					if(myY <= 20)
					begin
						myY <= 440;
						outgo = outgo + 1;
					end	
				end
			end
			else
			begin
				dir <= 4'hc;
				if(!BUTTON[1])
				begin
					myX12 <= myX11; myY12 <= myY11;
					myX11 <= myX10; myY11 <= myY10;
					myX10 <= myX9; myY10 <= myY9;	
					myX9 <= myX8; myY9 <= myY8;
					myX8 <= myX7; myY8 <= myY7;	
					myX7 <= myX6; myY7 <= myY6;
					myX6 <= myX5; myY6 <= myY5;		
					myX5 <= myX4; myY5 <= myY4;		
					myX4 <= myX3; myY4 <= myY3;		
					myX3 <= myX2; myY3 <= myY2;
					myX2 <= myX; myY2 <= myY;
					myY <= myY + 20;
					if(myY >= 440)
					begin
						myY <= 20;
						outgo = outgo + 1;
					end
				end
			end
			if(!BUTTON[0])
			begin
				myX12 <= myX11; myY12 <= myY11;
				myX11 <= myX10; myY11 <= myY10;
				myX10 <= myX9; myY10 <= myY9;	
				myX9 <= myX8; myY9 <= myY8;
				myX8 <= myX7; myY8 <= myY7;	
				myX7 <= myX6; myY7 <= myY6;
				myX6 <= myX5; myY6 <= myY5;		
				myX5 <= myX4; myY5 <= myY4;		
				myX4 <= myX3; myY4 <= myY3;		
				myX3 <= myX2; myY3 <= myY2;
				myX2 <= myX; myY2 <= myY;
				myX <= myX + 20;
				if(myX >= 600)
				begin
					myX <= 20;
					outgo = outgo + 1;
				end
			end
			if(!BUTTON[2])
			begin
				myX12 <= myX11; myY12 <= myY11;
				myX11 <= myX10; myY11 <= myY10;
				myX10 <= myX9; myY10 <= myY9;	
				myX9 <= myX8; myY9 <= myY8;
				myX8 <= myX7; myY8 <= myY7;	
				myX7 <= myX6; myY7 <= myY6;
				myX6 <= myX5; myY6 <= myY5;		
				myX5 <= myX4; myY5 <= myY4;		
				myX4 <= myX3; myY4 <= myY3;		
				myX3 <= myX2; myY3 <= myY2;
				myX2 <= myX; myY2 <= myY;
				myX <= myX - 20;
				if(myX <= 20)
				begin
					myX <= 600;
					outgo = outgo + 1;
				end	
			end
		end
		else
		begin
			hand = 0;
			if(SW[0])
			begin
				dir <= 4'hb;
				if(!BUTTON[1])
				begin
					up = 1; down = 0;
					left = 0; right = 0;
				end
			end
			else
			begin
				dir <= 4'hc;
				if(!BUTTON[1])
				begin
					up = 0; down = 1;
					left = 0; right = 0;
				end
			end	
			if(!BUTTON[0])
			begin
				up = 0; down = 0;
				left = 0; right = 1;
			end
			if(!BUTTON[2])
			begin
				up = 0; down = 0;
				left = 1; right = 0;
			end
		end
		
		if(left == 1)
		begin
			myX12 <= myX11; myY12 <= myY11;
			myX11 <= myX10; myY11 <= myY10;
			myX10 <= myX9; myY10 <= myY9;	
			myX9 <= myX8; myY9 <= myY8;
			myX8 <= myX7; myY8 <= myY7;	
			myX7 <= myX6; myY7 <= myY6;	
			myX6 <= myX5; myY6 <= myY5;		
			myX5 <= myX4; myY5 <= myY4;		
			myX4 <= myX3; myY4 <= myY3;		
			myX3 <= myX2; myY3 <= myY2;
			myX2 <= myX; myY2 <= myY;
			myX <= myX - 20;
			if(myX <= 20)
			begin
				myX <= 600;
				outgo = outgo + 1;
			end	
		end
		if(right == 1)
		begin
			myX12 <= myX11; myY12 <= myY11;
			myX11 <= myX10; myY11 <= myY10;
			myX10 <= myX9; myY10 <= myY9;	
			myX9 <= myX8; myY9 <= myY8;
			myX8 <= myX7; myY8 <= myY7;	
			myX7 <= myX6; myY7 <= myY6;	
			myX6 <= myX5; myY6 <= myY5;		
			myX5 <= myX4; myY5 <= myY4;		
			myX4 <= myX3; myY4 <= myY3;		
			myX3 <= myX2; myY3 <= myY2;
			myX2 <= myX; myY2 <= myY;
			myX <= myX + 20;
			if(myX >= 600)
			begin
				myX <= 20;
				outgo = outgo + 1;
			end
		end
		if(up == 1)
		begin
			myX12 <= myX11; myY12 <= myY11;
			myX11 <= myX10; myY11 <= myY10;
			myX10 <= myX9; myY10 <= myY9;	
			myX9 <= myX8; myY9 <= myY8;
			myX8 <= myX7; myY8 <= myY7;	
			myX7 <= myX6; myY7 <= myY6;	
			myX6 <= myX5; myY6 <= myY5;		
			myX5 <= myX4; myY5 <= myY4;		
			myX4 <= myX3; myY4 <= myY3;		
			myX3 <= myX2; myY3 <= myY2;
			myX2 <= myX; myY2 <= myY;
			myY <= myY - 20;
			if(myY <= 20)
			begin
				myY <= 440;
				outgo = outgo + 1;
			end	
		end
		if(down == 1)
		begin
			myX12 <= myX11; myY12 <= myY11;
			myX11 <= myX10; myY11 <= myY10;
			myX10 <= myX9; myY10 <= myY9;	
			myX9 <= myX8; myY9 <= myY8;
			myX8 <= myX7; myY8 <= myY7;	
			myX7 <= myX6; myY7 <= myY6;	
			myX6 <= myX5; myY6 <= myY5;		
			myX5 <= myX4; myY5 <= myY4;		
			myX4 <= myX3; myY4 <= myY3;		
			myX3 <= myX2; myY3 <= myY2;
			myX2 <= myX; myY2 <= myY;
			myY <= myY + 20;
			if(myY >= 440)
			begin
				myY <= 20;
				outgo = outgo + 1;
			end
		end	
		
		if(flag == 2)
		begin
			if( ((myY == myY2) && (myX == myX2)) || 
				((myY == myY3) && (myX == myX3)) || 
				((myY == myY4) && (myX == myX4)) || 
				((myY == myY5) && (myX == myX5)) || 
				((myY == myY6) && (myX == myX6)) ||
				((myY == myY7) && (myX == myX7)) || 
				((myY == myY8) && (myX == myX8)) ||
				((myY == myY9) && (myX == myX9)) || 
				((myY == myY10) && (myX == myX10)) ||
				((myY == myY11) && (myX == myX11)) ||
				((myY == myY12) && (myX == myX12)) )
			begin
				myY <= 100; myX <= 20;
				myX2 <= 0; myY2 <= 100;
				myX3 <= 0; myY3 <= 100;	
				myX4 <= 0; myY4 <= 100;			
				myX5 <= 0; myY5 <= 100;			
				myX6 <= 0; myY6 <= 100;
				myX7 <= 0; myY7 <= 100;
				myX8 <= 0; myY8 <= 100;
				myX9 <= 0; myY9 <= 100;
				myX10 <= 0; myY10 <= 100;
				myX11 <= 0; myY11 <= 100;
				myX12 <= 0; myY12 <= 100;
				up = 0; down = 0;
				left = 0; right = 1;
				score0 = score0 + 1;
				if((score1 == 9) && (score0 == 10))
				begin
					score0 = 0;
					score1 = 0;
				end
				else 
				begin
					if(score0 == 10)
					begin
						score0 = 0;
						score1 = score1 + 1;
					end
				end	
			end
		end
		if(flag == 1)
		begin
			if( ((myY == myY2) && (myX == myX2)) || 
				((myY == myY3) && (myX == myX3)) || 
				((myY == myY4) && (myX == myX4)) || 
				((myY == myY5) && (myX == myX5)) || 
				((myY == myY6) && (myX == myX6)) ||
				((myY == myY7) && (myX == myX7)) || 
				((myY == myY8) && (myX == myX8)) )
			begin
				myY <= 100; myX <= 20;
				myX2 <= 0; myY2 <= 100;
				myX3 <= 0; myY3 <= 100;	
				myX4 <= 0; myY4 <= 100;			
				myX5 <= 0; myY5 <= 100;			
				myX6 <= 0; myY6 <= 100;
				myX7 <= 0; myY7 <= 100;
				myX8 <= 0; myY8 <= 100;
				up = 0; down = 0;
				left = 0; right = 1;
				score0 = score0 + 1;
				if((score1 == 9) && (score0 == 10))
				begin
					score0 = 0;
					score1 = 0;
				end
				else 
				begin
					if(score0 == 10)
					begin
						score0 = 0;
						score1 = score1 + 1;
					end
				end	
			end
		end
		else
		begin
			if( ((myY == myY2) && (myX == myX2)) || 
				((myY == myY3) && (myX == myX3))|| 
				((myY == myY4) && (myX == myX4)) )
			begin
				myY <= 100; myX <= 20;
				myX2 <= 0; myY2 <= 100;
				myX3 <= 0; myY3 <= 100;	
				myX4 <= 0; myY4 <= 100;
				up = 0; down = 0;
				left = 0; right = 1;
				score0 = score0 + 1;
				if((score1 == 9) && (score0 == 10))
				begin
					score0 = 0;
					score1 = 0;
				end
				else 
				begin
					if(score0 == 10)
					begin
						score0 = 0;
						score1 = score1 + 1;
					end
				end	
			end
		end
					
		if(flag == 0)
			if(((myX >= 290) && (myX < 340)) && ((myY >= 190) && (myY < 240)))
				flag <= 1;	
		if(flag == 1)
			if(((myX >= 160) && (myX < 200)) && ((myY >= 300) && (myY < 340)))
				flag <= 2;
	end
	else
	begin
		myCount = myCount + 1;
	end
end
endmodule