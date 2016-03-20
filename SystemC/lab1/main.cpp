#include <systemc.h>
#include "CounterTest.h"

int sc_main(int argc,char *argv[])
{
    /*// create output trace file lab1.vcd
    sc_trace_file *tf = sc_create_vcd_trace_file("lab1");
    // set tracefile timeunit = 1 ps
    tf->set_time_unit(1,SC_PS);*/
    
    // Create Counter test object
    CounterTest ctr_test("ctr_test");
    // set trace for internal signals out
    /*ctr_test.set_tracefile(tf);
    // set clock
    ctr_test.clk(testclk);
    
    sc_start(1000,SC_PS);

    // close output trace file
    sc_close_vcd_trace_file(tf);*/

    sc_start(1000,SC_PS);
    
    return 0;
}
