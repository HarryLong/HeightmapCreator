#include "pixel.h"

/**************
 * BASE PIXEL *
 **************/
Pixel::Pixel(float height) : m_height(height)
{

}

float Pixel::getHeight() const
{
    return m_height;
}

void Pixel::setHeight(float height)
{
    m_height = height;
}
