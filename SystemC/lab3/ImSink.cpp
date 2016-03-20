#include <assert.h>
#include "ImSink.h"
#include "Filter.h"
#include "qdbmp.h"

// Main process of sink: reads pixels and counts rows
void ImSink::writeImagePixels()
{
    bool run = true;
    height = 0;
    _out_img.clear();
    while(run)
    {
        wait();
        Pixel pixel = buf_in.read();
        switch(pixel.type)
        {
        case IM_SYNC_PIXEL:
            _out_img.push_back(unsigned char(pixel.value));
            break;
        case IM_SYNC_ROW:
            std::cout << "ImSink row: "<<height<<std::endl;
            height++;
            break;
        case IM_SYNC_IMG:
            // stop synchronization after full image processing
            run = false;
            break;
        default:
            assert(0);
        };
    }
    sc_stop();
}

// writes bmp to output file
void ImSink::writeBMP(const char *filename)
{
    assert(filename);
    assert(_out_img.size());

    int width= _out_img.size()/height;
    BMP *bmp = BMP_Create(width,height,8);
    // setting grayscale pallette
    for(unsigned int i=0; i<255; i++)
    {
        BMP_SetPaletteColor(bmp,i,i,i,i);
    }
    // saving image
    for(unsigned int i=0; i<_out_img.size(); i++)
    {
        // synchronization using counted parameters from sync signals
        BMP_SetPixelIndex(bmp,i%width,i/width,_out_img[i]);
    }
    BMP_WriteFile(bmp,filename);
    if (BMP_GetError() != BMP_OK)
    {
        std::cerr << "Failed to write file " << filename <<std::endl;
        exit(1);
    }
    BMP_Free(bmp);

    std::cout << filename << " was successfully written" << std::endl;
}
