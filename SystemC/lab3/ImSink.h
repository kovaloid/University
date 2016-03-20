#ifndef _IMSINK_H
#define _IMSINK_H

#include <systemc.h>
#include <vector>
#include "Filter.h"

/**
 Image sink class.
 Reads image pixel-by-pixel from port
 and writes it to file.
 Supports only bmp now.
 */
SC_MODULE(ImSink)
{
    // input Pixel & sync
    sc_in<Pixel > buf_in;

    SC_CTOR(ImSink)
    {
        SC_THREAD(writeImagePixels);
        sensitive << buf_in;
    }

    // main process
    void writeImagePixels();
    // writes bmp to file after simulation
    void writeBMP(const char *filename);

private:
    // image is stored here
    std::vector<unsigned char> _out_img;
    // row count
    int height;
};

#endif //_IMSINK_H
