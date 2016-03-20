module LEDG_Driver(oLED,iCLK,iRST_n,outgo,hand);
output	[9:0]	oLED;
input	[9:0]	outgo;
input 			hand;
input			iCLK;
input			iRST_n;
reg		[9:0]	mLED;

always@(posedge iCLK or negedge iRST_n)
begin
	if(!iRST_n)
		mLED = 10'b1100110011;	
	else
		if(hand == 0)
			case(outgo)
				4'h0: mLED	<=	10'b0000000000;
				4'h1: mLED	<=	10'b0000000001;	
				4'h2: mLED	<=	10'b0000000011;
				4'h3: mLED	<=	10'b0000000111;	
				4'h4: mLED	<=	10'b0000001111;	
				4'h5: mLED	<=	10'b0000011111;
				4'h6: mLED	<=	10'b0000111111;	
				4'h7: mLED	<=	10'b0001111111;
				4'h8: mLED	<=	10'b0011111111;
				4'h9: mLED	<=	10'b0111111111;
				4'ha: mLED	<=	10'b1111111111;
				4'hb: mLED	<=	10'b1111111110;
				4'hc: mLED	<=	10'b1111111100;
				4'hd: mLED	<=	10'b1111111000;
				4'he: mLED	<=	10'b1111110000;
				4'hf: mLED	<=	10'b1111100000;
				5'h10: mLED	<=	10'b1111000000;
				5'h11: mLED	<=	10'b1110000000;
				5'h12: mLED	<=	10'b1100000000;
				5'h13: mLED	<=	10'b1000000000;
				default: mLED	<=	10'b0011001100;
			endcase
		else
			mLED	<=	10'b1010101010;
end
assign	oLED	=	mLED;
endmodule
