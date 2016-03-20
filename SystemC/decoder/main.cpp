#include <systemc.h>
#include "DecoderTest.h"

int sc_main(int argc,char *argv[])
{
    DecoderTest dc_test("dc_test");
    sc_start(1000,SC_PS);
    return 0;
}
