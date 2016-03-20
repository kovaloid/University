#ifndef _AVGFILTER_H
#define _AVGFILTER_H

#include <systemc.h>
#include "FIRFilter.h"

/**
 Average image filter class.
 Supports arbitrary size of filter.
 Is based on FIRFilter.
 */
template<int N> struct AVGFilter:
    public FIRFilter<N>
{
    //SC_CTOR
    typedef AVGFilter SC_CURRENT_USER_MODULE;
    AVGFilter(::sc_core::sc_module_name mod_name):
        FIRFilter(mod_name,_coeffs,N*N,0,false)
    {
        // all coeffs are 1, but denominator is window size
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                _coeffs[i][j] = 1;
            }
        }
        _denominator = N*N;
        _shift = 0;
        _absolute = false;
    }
};

#endif //_FIRFILTER_H
