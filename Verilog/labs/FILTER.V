module RStrigger (out,x,xdop);
   
   input x,xdop;
   output out;
   reg res;

   always @(xdop or x)
      begin
        if (~xdop)
           res = 0;
        else
          if (~x)
           res = 1;
      end
   assign out = !res;
endmodule

module FILTER (OutResult, X, A, B);

   input   X, A, B;
   output  OutResult;

   not NOT1 (AInv, A);
   not NOT2 (BInv, B);

   RStrigger call1 (out1, X, A);
   RStrigger call2 (out2, X, B);
   RStrigger call3 (out3, X, AInv);
   RStrigger call4 (out4, X, BInv);

   and  AND1 (OutResult, out1, out2, out3, out4);
endmodule
         
