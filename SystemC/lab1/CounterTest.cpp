#include "CounterTest.h"

/**
    SC_THREAD of source:
        1. triggers reset; counter should be nulled
        2. maxc times triggers clock; counter should be incremented
 */
void Source::run() 
{
    ctr_rst.write(1); // write 0 to ctr rst
    wait(1,SC_PS);    //wait 1ps for counter
    ctr_rst.write(0); // write 1 to ctr rst; ctr should be nulled
    wait();           //wait 1ps for new clock

    for(int i=0;i<maxc;i++)
    {
        ctr_clk.write(0); // write 0 to ctr clk
        wait(1,SC_PS);    //wait 1ps for counter
        ctr_clk.write(1); // write 1 to ctr clk; ctr should be incremented
        wait();           //wait 1ps for new clock
    }
  
    // stop simulation
    sc_stop();
}

/**
    SC_METHOD of sink:
        simply outputs value to cout.
 */
void Sink::on_tick() 
{
    std::cout << ctr_val.read() << std::endl;
}
