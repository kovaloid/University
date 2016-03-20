#ifndef DECODER_H
#define DECODER_H

#include <systemc.h>

SC_MODULE(Decoder)
{
	sc_in<bool> enable;
	sc_in<sc_uint<3> > input;
	sc_out<sc_bv<8> > output;
    
    void on_tick();

	SC_CTOR(Decoder)
    {
        SC_METHOD(on_tick);
        sensitive << input;
    }

private:
    sc_uint<3> tmp;
};

#endif
