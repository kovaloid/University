module REG (indata, read, write, clock, outdata);

   input   indata, read, write, clock;
   output [3:0] outdata;
   reg [3:0] mem, res;
   integer i=0;

   always @(posedge clock)
      begin
        if (write == 1)
           mem[i] = indata;
        if (read == 1)
           res = mem;
        if (i == 3)
           i = 0;
        else i=i+1;
      end
   assign outdata = res;

endmodule
         
