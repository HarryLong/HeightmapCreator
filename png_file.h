#ifndef DECODED_PNG_FILE_H
#define DECODED_PNG_FILE_H

#include <vector>

class Pixel{
public:
    Pixel(unsigned short intensity);

    virtual float getHeight() const = 0;
    unsigned short getIntensity() const;

protected:
    unsigned short m_intensity;
};

class _8BitPixel : public Pixel {
public:
    _8BitPixel(unsigned short intensity);
    float getHeight() const;
};

class _16BitPixel : public Pixel {
public:
    _16BitPixel(unsigned short intensity);
    virtual float getHeight() const;
};

class DecodedGreyScalePNGFile {
public:
    enum GrayScaleMode {
        _8_BIT,
        _16_BIT
    };

    DecodedGreyScalePNGFile(const std::vector<unsigned char> & m_raw_data, int width, int height, GrayScaleMode mode = GrayScaleMode::_8_BIT);
    DecodedGreyScalePNGFile();
    ~DecodedGreyScalePNGFile();
    Pixel * operator()(int x, int y) const;

    int width() const;
    int height() const;

    Pixel * min() const;
    Pixel * max() const;

    GrayScaleMode getMode();

    static unsigned short to_short(unsigned char c1, unsigned char c2);

private:
    void _8_bit_decode(const std::vector<unsigned char> & raw_data);
    void _16_bit_decode(const std::vector<unsigned char> & raw_data);

    std::vector<Pixel*> m_decoded_data; // row_order
    Pixel * m_p_min;
    Pixel * m_p_max;
    int m_width, m_height;
    GrayScaleMode m_mode;
};

#endif // DECODED_PNG_FILE_H
