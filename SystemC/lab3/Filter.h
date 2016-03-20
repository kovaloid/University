#ifndef _FILTER_H
#define _FILTER_H

#include <systemc.h>
#include "Types.h"

/**
 Abstract image filter base class.
 Supports 8-bit image block processing.
 Size of filter is template argument.
 */
template<int N> SC_MODULE(Filter)
{
    // Input buffer: read by blocks
    sc_in<SquareImBlock<N> > buf_in;
    // Output buffer: output processed pixels
    sc_out<Pixel> buf_out;

    // Process function: must be reimplemented
    //  in concrete descendants
    virtual void process() = 0;

    // Main Process
    void main()
    {
        while(1)
        {
            process();
            wait();
        }
    }

    // Sensitive to updates in buffers
    SC_CTOR(Filter)
    {
        SC_THREAD(main);
        sensitive << buf_in;
        dont_initialize();
    }
};

#endif //_FILTER_H
