#include "DecoderTest.h"

void Source::run() 
{
	dc_enable.write(0);
    wait(1,SC_PS);
    dc_enable.write(1);
    wait();

	for(int i=0;i<maxc;i++)
    {
        dc_input.write(i);
        wait();
    }

    sc_stop();
}

void Sink::on_tick() 
{
    std::cout << dc_output.read() << std::endl;
}
