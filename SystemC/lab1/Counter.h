#ifndef COUNTER_H
#define COUNTER_H

#include <systemc.h>

/**
  Simple 4-bit counter
  */
SC_MODULE(Counter)
{
    /*** INPUT SIGNALS: ***/
    sc_in<bool> clk; // input clock
    sc_in<bool> rst; // input reset signal
    
    /*** OUTPUT SIGNALS: ***/
    sc_out<sc_uint<4> > state; // output: 4-bit state of counter
    
    // main method; is called on every clk
    void on_tick();

    // constructor of module
    SC_CTOR(Counter):
        c(0)
    {
        // on_tick will be called on every positive clk
        SC_METHOD(on_tick);
        sensitive << clk.pos();
    }

private:
    // 4-bit internal counter state
    sc_uint<4> c;
};

#endif // COUNTER_H
