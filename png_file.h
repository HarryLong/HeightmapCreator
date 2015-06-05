#ifndef DECODED_PNG_FILE_H
#define DECODED_PNG_FILE_H

#include <vector>

class Pixel{
public:
    Pixel(unsigned short m_intensity);

    float getHeight() const;
    unsigned short getIntensity() const;

private:
    unsigned short m_intensity;
};

class DecodedGreyScalePNGFile {
public:
    DecodedGreyScalePNGFile(std::vector<unsigned char> raw_data, int width, int height);
    DecodedGreyScalePNGFile();
    ~DecodedGreyScalePNGFile();
    Pixel operator()(int x, int y) const;

    int width() const;
    int height() const;

    Pixel min() const;
    Pixel max() const;

    static unsigned short to_short(unsigned char c1, unsigned char c2);

private:
    std::vector<Pixel> m_decoded_data; // row_order
    int m_width, m_height;
    Pixel m_p_min, m_p_max;
};

#endif // DECODED_PNG_FILE_H
