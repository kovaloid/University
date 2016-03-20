#ifndef _FIRFILTER_H
#define _FIRFILTER_H

#include <systemc.h>
#include "Filter.h"

/**
 Finite Input Response image filter class.
 Supports arbitrary coefficients.
 */
template<int N> struct FIRFilter:
    public Filter<N>
{
    // Processing function; is called on every input update
    void process()
    {
        // Read input buffer
        SquareImBlock<N> in = buf_in.read();

        float val = 0;
        if(IM_SYNC_PIXEL == in.type)
        {
            // Process simple convolution
            for(int y=0;y<N;y++)
            {
                for(int x=0;x<N;x++)
                {
                    val += in.data[x][y] * _coeffs[x][y];
                }
            }

            // Using denominator, shift and abs
            //  we can put value in 0..255 range
            val /= _denominator;
            val += _shift;
            if(_absolute)
                val = fabs(val);
        }
        
        // output value to out buffer
        Pixel out;
        out.value = val;
        out.type = in.type;

        buf_out.write(out);
    }

    // SC_CTOR constructor with additional parameters
    typedef FIRFilter SC_CURRENT_USER_MODULE;
    FIRFilter(::sc_core::sc_module_name mod_name,float coeffs[N][N],float denominator,float shift,bool absolute):
        Filter(mod_name),
        _denominator(denominator),
        _shift(shift),
        _absolute(absolute)
    {
        memcpy(&_coeffs[0][0],&coeffs[0][0],N*N*sizeof(float));
    }

protected:
    // Constructor for reimplemention: 
    //  parameters are setup in descendant
    FIRFilter(::sc_core::sc_module_name mod_name):
        Filter(mod_name)
    {
    }

    // filter parameters
    float _coeffs[N][N];
    float _denominator,_shift;
    bool _absolute;
};

#endif //_FIRFILTER_H
