#include "Filter.h"

// outstream operator of SquareImBlock
std::ostream& operator<< (std::ostream& stream, const Pixel& pixel)
{
    switch(pixel.type)
    {
    case IM_SYNC_PIXEL:
        stream << pixel.value;
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

// tracing function of Pixel
void sc_trace(sc_trace_file *tf, const Pixel &v,const std::string &name)
{
    sc_trace(tf,v.type,name+".type");
    sc_trace(tf,v.value,name+".value");
}
