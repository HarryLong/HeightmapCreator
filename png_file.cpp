#include "png_file.h"
#include <climits>
#include <cstring>

/**************
 * BASE PIXEL *
 **************/
Pixel::Pixel(unsigned short intensity) : m_intensity(intensity)
{

}

unsigned short Pixel::getIntensity() const
{
    return m_intensity;
}

/***************
 * 8 BIT PIXEL *
 ***************/
_8BitPixel::_8BitPixel(unsigned short intensity) : Pixel(intensity)
{

}

float _8BitPixel::getHeight() const
{
    return m_intensity;
}


/***************
 * 16 BIT PIXEL *
 ***************/
_16BitPixel::_16BitPixel(unsigned short intensity) : Pixel(intensity)
{

}

float _16BitPixel::getHeight() const
{
    return ((float)m_intensity/64.0f);
}


//---------------------------------------------------------------------

/*******************
 * BASE DECODED GS *
 *******************/
DecodedGreyScalePNGFile::DecodedGreyScalePNGFile(const std::vector<unsigned char> & raw_data, int width, int height, GrayScaleMode mode) :
    m_width(width), m_height(height), m_p_min(NULL), m_p_max(NULL), m_mode(mode)
{
    if(mode == GrayScaleMode::_8_BIT)
        _8_bit_decode(raw_data);
    else
        _16_bit_decode(raw_data);
}

DecodedGreyScalePNGFile::DecodedGreyScalePNGFile() : m_decoded_data(), m_width(0), m_height(0), m_p_min(NULL), m_p_max(NULL), m_mode(GrayScaleMode::_8_BIT)
{

}

DecodedGreyScalePNGFile::~DecodedGreyScalePNGFile()
{
    if(m_p_min)
        delete m_p_min;
    if(m_p_max)
        delete m_p_max;

    for(Pixel* p : m_decoded_data)
        delete p;
}

Pixel * DecodedGreyScalePNGFile::operator()(int x, int y) const{
    int index ((y*m_width+x)); // 2 bytes per pixel value (16 bit Greyscale)
    return m_decoded_data[index];
}

void DecodedGreyScalePNGFile::_8_bit_decode(const std::vector<unsigned char> & raw_data)
{
    for(int i(0); i < raw_data.size(); i++)
    {
        Pixel * p = new _8BitPixel(raw_data[i]);
        if(!m_p_max || p->getIntensity() > m_p_max->getIntensity())
            m_p_max = p;
        if(!m_p_min || p->getIntensity() < m_p_min->getIntensity())
            m_p_min = p;

        m_decoded_data.push_back(p);
    }
}

void DecodedGreyScalePNGFile::_16_bit_decode(const std::vector<unsigned char> & raw_data)
{
    for(int i(0); i < raw_data.size()-1; i+=2)
    {
        Pixel * p = new _16BitPixel(DecodedGreyScalePNGFile::to_short(raw_data[i], raw_data[i+1]));
        if(!m_p_max || p->getIntensity() > m_p_max->getIntensity())
            m_p_max = p;
        if(!m_p_min || p->getIntensity() < m_p_min->getIntensity())
            m_p_min = p;

        m_decoded_data.push_back(p);
    }
}

int DecodedGreyScalePNGFile::width() const
{
    return m_width;
}

int DecodedGreyScalePNGFile::height() const
{
    return m_height;
}

unsigned short DecodedGreyScalePNGFile::to_short(unsigned char c1, unsigned char c2)
{
    // Retrieve the first 8 bits
    unsigned short value = (unsigned short) c1;
    value = value << 8; // Left-shift by 8 bits

    value += (unsigned short) c2;

    return value;
}

Pixel * DecodedGreyScalePNGFile::min() const
{
    return m_p_min;
}

Pixel * DecodedGreyScalePNGFile::max() const
{
    return m_p_max;
}

DecodedGreyScalePNGFile::GrayScaleMode DecodedGreyScalePNGFile::getMode()
{
    return m_mode;
}

