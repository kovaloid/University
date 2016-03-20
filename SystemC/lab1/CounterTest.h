#ifndef COUNTERTEST_H
#define COUNTERTEST_H

#include <iostream>
#include <systemc.h>
#include "Counter.h"

/**
  Source module for counter test
  */
SC_MODULE(Source)
{
    // input clk
    sc_in<bool> clk;
    // clk for counter
    sc_out<bool> ctr_clk;
    sc_out<bool> ctr_rst;

    // main thread function
    void run();  

    // constructor of module
    SC_CTOR(Source)
    {
        SC_THREAD(run);
        // run will be triggered on every posedge of clock
        sensitive << clk.pos();
    }

    // maximum increment cycle count
    static const int maxc = 33;
};

/**
  Sink module for counter test.
  Prints counter's value to the output
  */
SC_MODULE(Sink)
{
    // input clk
    sc_in<bool> clk;
    // output ctr value
    sc_in<sc_uint<4> > ctr_val;
    
    // main function; will be called in the end
    // of the cycle
    void on_tick();  

    // constructor of module
    SC_CTOR(Sink)
    {
        SC_METHOD(on_tick);
        // check the value in the end of the cycle
        sensitive << clk.neg();
        
        // print "header"
        std::cout << "ctr_val" << std::endl;
    }  
};

/**
 UnitTest for simple Counter
 */
SC_MODULE(CounterTest)
{
    // counter submodule
    Counter ctr;
    // counter src submodule
    Source src;
    // counter sink submodule
    Sink sink;

    // clock oscillator
    sc_clock clk;
    /*** signals ***/
    sc_signal<bool> ctr_rst;
    sc_signal<bool> ctr_clk;
    sc_signal<sc_uint<4> > ctr_val;

    // output trace file 
    sc_trace_file *tf;
    
    // constructor of test bench
    SC_CTOR(CounterTest):
        clk("clk",5,SC_PS),
        ctr("ctr0"),
        src("src0"),
        sink("sink0")
    {
        // initialise source signals
        src.clk(clk);
        src.ctr_clk(ctr_clk);
        src.ctr_rst(ctr_rst);

        // initialise sink signals
        sink.clk(clk);
        sink.ctr_val(ctr_val);

        // initialise counter signals
        ctr.clk(ctr_clk);
        ctr.state(ctr_val);
        ctr.rst(ctr_rst);

        // creating trace file CounterTest.vcd
        tf = sc_create_vcd_trace_file("CounterTest");
        tf->set_time_unit(1,SC_PS);
        
        // all changed in signals will be auto output'ed to trace file
        sc_trace(tf,clk,"clk");
        sc_trace(tf,ctr_rst,"rst");
        sc_trace(tf,ctr_clk,"ctr_clk");
        sc_trace(tf,ctr_val,"ctr_val");
    }

    ~CounterTest()
    {
        // closing trace file on exit
        sc_close_vcd_trace_file(tf);
    }
};

#endif // COUNTERTEST_H
