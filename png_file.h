#ifndef DECODED_PNG_FILE_H
#define DECODED_PNG_FILE_H

#include <vector>
#include "pixel.h"
#include "heightmap_file.h"

class _8BitPixel : public Pixel {
public:
    _8BitPixel(unsigned short intensity);
};

class _16BitPixel : public Pixel {
public:
    _16BitPixel(unsigned short intensity);
};

class DecodedGreyScalePNGFile : public HeightmapFile{
public:
    enum GrayScaleMode {
        _8_BIT,
        _16_BIT
    };

    DecodedGreyScalePNGFile(const std::vector<unsigned char> & m_raw_data, int width, int height, GrayScaleMode mode = GrayScaleMode::_8_BIT);
    DecodedGreyScalePNGFile();
    ~DecodedGreyScalePNGFile();


    GrayScaleMode getMode();

    static unsigned short to_short(unsigned char c1, unsigned char c2);

private:
    void _8_bit_decode(const std::vector<unsigned char> & raw_data);
    void _16_bit_decode(const std::vector<unsigned char> & raw_data);

    GrayScaleMode m_mode;
};

#endif // DECODED_PNG_FILE_H
