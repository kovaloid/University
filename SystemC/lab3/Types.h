#ifndef _TYPES_H
#define _TYPES_H

#include <systemc.h>
#include <string>
#include <sstream>
//#include "sc_enum_trace.h"

/** IM_SYNC enum:
    used for vertical and horizontal
    image synchronization
 */
enum IM_SYNC
{
    IM_SYNC_PIXEL = 0, //pixel update
    IM_SYNC_ROW, //row update
    IM_SYNC_IMG //img update
};

/** Struct Pixel:
    Data type includes data and syncronization channels
 */
struct Pixel{
    sc_uint<2> type; //IM_SYNC type
    sc_uint<8> value; //is defined only for IM_SYNC_PIXEL

    // equality operator
    inline bool operator == (const Pixel &bl) const
    {
        return (type == bl.type) && (value == bl.value);
    }

    // outstream operator
    friend std::ostream& operator<< (std::ostream& stream, const Pixel& bl);
};
// tracing function
extern void sc_trace(sc_trace_file *tf, const Pixel &pixel,const std::string &name);


/** Struct SquareImBlock:
    image processing primitive for block-by-block processing
    Includes array of data and synchronization.
    Is parametrized by size of block.
 */
template<int N> struct SquareImBlock{
    sc_uint<2> type; //IM_SYNC type
    sc_uint<8> data[N][N]; //is defined only for IM_SYNC_PIXEL

    // equality operator
    inline bool operator == (const SquareImBlock &bl) const
    {
        int d = memcmp(&data[0][0],&bl.data[0][0],N*N*sizeof(sc_uint<8>));
        return (type == bl.type) && !d;
    }

    // outstream operator
    template<int N> friend std::ostream& operator<< (std::ostream& stream, const SquareImBlock& bl);
};

// outstream operator of SquareImBlock
template<int N> std::ostream& operator<< (std::ostream& stream, const SquareImBlock<N>& bl)
{
    switch(bl.type)
    {
    case IM_SYNC_PIXEL:
        {
            for(int i=0;i<N;i++)
                for(int j=0;j<N;j++)
                    stream << bl.data[i][j];
        }
        break;
    case IM_SYNC_ROW:
        stream << "RowSync";
        break;
    case IM_SYNC_IMG:
        stream << "ImgSync";
        break;
    default:
        assert(0);
    };
    return stream;
}

// tracing function of SquareImBlock
template<int N> void sc_trace(sc_trace_file *tf, const SquareImBlock<N> &bl,const std::string &name)
{
    sc_trace(tf,bl.type,name+".type");
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            std::ostringstream sig_name;
            sig_name << name << ".data(" << i << "," << j << ")";
            sc_trace(tf,bl.data[i][j],sig_name.str());
        }
    }
}

#endif //_TYPES_H
