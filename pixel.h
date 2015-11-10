#ifndef PIXEL_H
#define PIXEL_H

class Pixel{
public:
    Pixel(float height);

    virtual float getHeight() const;
    void setHeight(float height);

protected:
    float m_height;
};

#endif // PIXEL_H
