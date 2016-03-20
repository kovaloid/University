#ifndef DECODERTEST_H
#define DECODERTEST_H

#include <iostream>
#include <systemc.h>
#include "Decoder.h"

SC_MODULE(Source)
{
	sc_in<bool> clk;
	sc_out<sc_uint<3> > dc_input;
	sc_out<bool> dc_enable;

    void run();  

    SC_CTOR(Source)
    {
        SC_THREAD(run);
        sensitive << clk.pos();
    }

    static const int maxc = 8;
};


SC_MODULE(Sink)
{
	sc_in<bool> clk;
	sc_in<sc_bv<8> > dc_output;
    
    void on_tick();  

    SC_CTOR(Sink)
    {
        SC_METHOD(on_tick);
        sensitive << clk.neg();
        std::cout << "dc_output" << std::endl;
    }  
};


SC_MODULE(DecoderTest)
{
    Decoder dc;
    Source src;
    Sink sink;

    sc_clock clk;
	sc_signal<sc_uint<3> > dc_input;
	sc_signal<bool> dc_enable;
	sc_signal<sc_bv<8> > dc_output;

    sc_trace_file *tf;
    
    SC_CTOR(DecoderTest):
        clk("clk",5,SC_PS),
        dc("dc0"),
        src("src0"),
        sink("sink0")
    {
        src.clk(clk);
        src.dc_input(dc_input);
        src.dc_enable(dc_enable);

        sink.clk(clk);
        sink.dc_output(dc_output);

		dc.enable(dc_enable);
        dc.output(dc_output);
        dc.input(dc_input);

        tf = sc_create_vcd_trace_file("DecoderTest");
        tf->set_time_unit(1,SC_PS);
        
        sc_trace(tf,clk,"clk");
        sc_trace(tf,dc_enable,"enable");
        sc_trace(tf,dc_input,"input");
        sc_trace(tf,dc_output,"output");
    }

    ~DecoderTest()
    {
        sc_close_vcd_trace_file(tf);
    }
};

#endif
