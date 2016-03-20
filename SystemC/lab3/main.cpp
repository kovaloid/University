#include <systemc.h>
#include "FIRFilter.h"
#include "AVGFilter.h"
#include "MEDFilter.h"
#include "ImSource.h"
#include "ImSink.h"

#define FilterTaps 3

int sc_main(int,char**)
{
    ///////////////////////////
    // Creating components
    //////////////////////////
    ImSource<FilterTaps> src("src");
    ImSink sink("sink");
    
    /*float fir_coeffs[FilterTaps][FilterTaps]
            = {{1,-2,1},
                {-2,4,-2},
                {1,-2,1}};
    float fir_denominator = 1,fir_shift = 0;
    FIRFilter<FilterTaps> filter("fir",fir_coeffs,fir_denominator,fir_shift,true);*/
    AVGFilter<FilterTaps> filter("avg");
    //MedFilter<FilterTaps> filter("med");
    sc_buffer<SquareImBlock<FilterTaps> > block_buf;
    sc_buffer<Pixel> pixel_buf;
    
    ///////////////////////////
    // Connecting components
    //////////////////////////
    src.buf_out(block_buf);
    filter.buf_in(block_buf);
    filter.buf_out(pixel_buf);
    sink.buf_in(pixel_buf);

    /////////////////////////////
    // Setting trace properties
    ////////////////////////////
    sc_trace_file *tf = sc_create_vcd_trace_file("Filter");
    tf->set_time_unit(1,SC_PS);
    sc_trace(tf,block_buf,"Block");
    sc_trace(tf,pixel_buf,"Pixel");
    
    //////////////////////////////
    // Setting i/o and simulating
    //////////////////////////////
    
    /*src.readBMP("pirate.bmp");
    sc_start();
    sink.writeBMP("pirate_filtered.bmp");*/

    /*src.readBMP("pirate_noise.bmp");
    sc_start();
    sink.writeBMP("pirate_n_filtered.bmp");*/

    src.readBMP("pirate_noise_sp.bmp");
    sc_start();
    sink.writeBMP("pirate_nsp_filtered.bmp");

    /*src.readBMP("peppers.bmp");
    sc_start();
    sink.writeBMP("peppers_filtered.bmp");*/

    ///////////////
    // Clearing
    ///////////////
    sc_close_vcd_trace_file(tf);

    return 0;
}
