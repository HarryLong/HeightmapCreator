#include "png_file.h"
#include <climits>

/*********
 * PIXEL *
 *********/
Pixel::Pixel(unsigned short intensity) : m_intensity(intensity)
{

}

float Pixel::getHeight() const
{
    return ((float)m_intensity/64.0f);
}

unsigned short Pixel::getIntensity() const
{
    return m_intensity;
}

//---------------------------------------------------------------------

DecodedGreyScalePNGFile::DecodedGreyScalePNGFile(std::vector<unsigned char> raw_data, int width, int height) :
    m_width(width), m_height(height), m_p_min(USHRT_MAX), m_p_max(0)
{
    for(int i(0); i < raw_data.size()-1; i+=2)
    {
        Pixel p(DecodedGreyScalePNGFile::to_short(raw_data[i], raw_data[i+1]));
        if(p.getIntensity() > m_p_max.getIntensity())
            m_p_max = p;
        if(p.getIntensity() < m_p_min.getIntensity())
            m_p_min = p;

        m_decoded_data.push_back(p);
    }    
}

DecodedGreyScalePNGFile::DecodedGreyScalePNGFile() : m_decoded_data(), m_width(0), m_height(0), m_p_min(USHRT_MAX), m_p_max(0)
{

}

DecodedGreyScalePNGFile::~DecodedGreyScalePNGFile()
{

}

Pixel DecodedGreyScalePNGFile::operator()(int x, int y) const{
    int index ((y*m_width+x)); // 2 bytes per pixel value (16 bit Greyscale)
    return Pixel(m_decoded_data[index]);
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

Pixel DecodedGreyScalePNGFile::min() const
{
    return m_p_min;
}

Pixel DecodedGreyScalePNGFile::max() const
{
    return m_p_max;
}
