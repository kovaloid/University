#ifndef _MEDFILTER_H
#define _MEDFILTER_H

#include <systemc.h>
#include <algorithm>
#include <vector>
#include "Filter.h"

/**
 Median image filter class.
 Supports arbitrary size of filter.
 */
template<int N> struct MedFilter:
    public Filter<N>
{
    // Processing function
    void process()
    {
        SquareImBlock<N> in = buf_in.read();

        Pixel out;
        out.type = in.type;
        
        if(IM_SYNC_PIXEL == in.type)
        {
            // find median of array usind sorting
            
            // here we use that 2d array is placed in
            //  single block of memory
            std::sort(&in.data[0][0],&in.data[0][0]+N*N);
            // uncomment to check timed model
            //wait(20,SC_NS);
            if(N%2)
            {
                // if N is odd, median is located in the center of the filter
                out.value = in.data[N/2][N/2];
            }
            else
            {
                // if N is even, median is one of two center elements
                // or average of them
                out.value = (in.data[N/2-1][N-1]+in.data[N/2][0])/2;
            }
        }
        
        buf_out.write(out);
    }

    // SC_CTOR
    typedef MedFilter SC_CURRENT_USER_MODULE;
    MedFilter(::sc_core::sc_module_name mod_name):
        Filter(mod_name)
    {        
    }
};

#endif //_MEDFILTER_H
