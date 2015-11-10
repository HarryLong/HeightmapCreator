#include "png_file.h"
#include <climits>
#include <cstring>

/***************
 * 8 BIT PIXEL *
 ***************/
_8BitPixel::_8BitPixel(unsigned short intensity) : Pixel(intensity)
{

}

/***************
 * 16 BIT PIXEL *
 ***************/
_16BitPixel::_16BitPixel(unsigned short intensity) : Pixel((float)intensity/64.0f)
{

}

//---------------------------------------------------------------------

/*******************
 * BASE DECODED GS *
 *******************/
DecodedGreyScalePNGFile::DecodedGreyScalePNGFile(const std::vector<unsigned char> & raw_data, int width, int height, GrayScaleMode mode) :
    HeightmapFile(width, height), m_mode(mode)
{
    if(mode == GrayScaleMode::_8_BIT)
        _8_bit_decode(raw_data);
    else
        _16_bit_decode(raw_data);
}

DecodedGreyScalePNGFile::DecodedGreyScalePNGFile() : HeightmapFile(0,0) , m_mode(GrayScaleMode::_8_BIT)
{

}

DecodedGreyScalePNGFile::~DecodedGreyScalePNGFile()
{

}

void DecodedGreyScalePNGFile::_8_bit_decode(const std::vector<unsigned char> & raw_data)
{
    for(int y(0); y < m_height; y++)
        for(int x(0); x < m_width; x++)
        {
            set(x,y,new _8BitPixel(raw_data[y*m_width+x]));
        }
}

void DecodedGreyScalePNGFile::_16_bit_decode(const std::vector<unsigned char> & raw_data)
{
    for(int y(0); y < m_height; y++)
        for(int x(0); x < m_width-1; x+=2)
        {
            int i(y*m_width+x);
            set(x,y,new _16BitPixel(DecodedGreyScalePNGFile::to_short(raw_data[i], raw_data[i+1])));
        }
}

unsigned short DecodedGreyScalePNGFile::to_short(unsigned char c1, unsigned char c2)
{
    // Retrieve the first 8 bits
    unsigned short value = (unsigned short) c1;
    value = value << 8; // Left-shift by 8 bits

    value += (unsigned short) c2;

    return value;
}

DecodedGreyScalePNGFile::GrayScaleMode DecodedGreyScalePNGFile::getMode()
{
    return m_mode;
}

