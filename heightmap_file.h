#ifndef HEIGHTMAP_FILE_H
#define HEIGHTMAP_FILE_H

#include "pixel.h"
#include <vector>
#include <map>

class HeightmapFile {
public:
    HeightmapFile(int w, int h);
    HeightmapFile();
    ~HeightmapFile();
    Pixel * operator()(int x, int y) const;

    void set(int x, int y, Pixel * p);

    int width() const;
    int height() const;

    void setSize(int w, int h);

    Pixel * min() const;
    Pixel * max() const;

protected:
    std::map<int, std::map<int, Pixel*> > m_data;
    Pixel * m_p_min;
    Pixel * m_p_max;
    int m_width, m_height;

private:
    bool contains(int x, int y) const;
};

#endif //HEIGHTMAP_FILE_H
