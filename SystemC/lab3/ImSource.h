#ifndef _IMSOURCE_H
#define _IMSOURCE_H

#include <systemc.h>
#include <iostream>
#include "qdbmp.h"
#include "Filter.h"

/**
 Image source class.
 Reads image and writes it to port using
 overlapped blocks.
 Supports only bmp now.
 Is parametrized by size of output blocks.
 */
template <int N> SC_MODULE(ImSource)
{
    // output block buffer
    sc_out<SquareImBlock<N> > buf_out;
    // using internal pixel trigger
    sc_clock clk;

    SC_CTOR(ImSource):
        clk("SrcClk",1,SC_NS),
        bmp(0)
    {
        SC_THREAD(readImageBlocks);
        sensitive << clk;
        dont_initialize();
    }

    ~ImSource()
    {
        if(bmp)
            BMP_Free(bmp);
    }

    // main process function - writes read image to output buffer
    void readImageBlocks();
    
    // reads 8-bit bmp from file
    void readBMP(const char *filename);

private:
    // qdbmp bmp handle
    BMP *bmp;
};

// reads bmp from file and checks it is valid
template<int N> void ImSource<N>::readBMP(const char *filename)
{
    bmp = BMP_ReadFile(filename);
    if (BMP_GetError() != BMP_OK)
    {
        std::cerr << "Failed to read file " << filename <<std::endl;
        exit(1);
    }
    if (BMP_GetDepth(bmp) != 8)
    {
        std::cerr << "Bit depth should be 8 " << filename <<std::endl;
        exit(1);
    }
    std::cout << filename << " was successfully read" << std::endl;
}

// main process: read image blocks from bmp and
//  write them to buffer
template<int N> void ImSource<N>::readImageBlocks()
{
    // Square Overlapping blocks
    SquareImBlock<N> block;
    int w = BMP_GetWidth(bmp);
    int h = BMP_GetHeight(bmp);
    for(int y=0; y<h-N+1; y++)
    {
        std::cout << "ImSource row: "<<y<<std::endl;
        for(int x=0; x<w-N+1; x++)
        {                    
            // copy block to buffer pixel-by-pixel
            for(int y_bl=0; y_bl<N; y_bl++)
            {
                for(int x_bl=0; x_bl<N; x_bl++)
                {
                    UCHAR val;
                    BMP_GetPixelIndex(bmp,x+x_bl,y+y_bl,&val);
                    block.data[y_bl][x_bl] = val;
                }
            }
            // write data block to file
            block.type = IM_SYNC_PIXEL;
            buf_out->write(block);
            // uncomment here for timed model
            //wait(10,SC_NS);
            wait();
        }
        // row synchrosignal
        block.type = IM_SYNC_ROW;
        buf_out->write(block);
        wait();
    }
    std::cout << std::endl;
    
    // end of img synchrosignal
    block.type = IM_SYNC_IMG;
    buf_out->write(block);

    // waiting for completion
    while(1)
        wait();
}

#endif //_IMSOURCE_H
