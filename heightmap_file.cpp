#include "heightmap_file.h"

HeightmapFile::HeightmapFile(int w, int h) : m_width(w), m_height(h), m_p_min(nullptr), m_p_max(nullptr)
{
}

HeightmapFile::HeightmapFile() : HeightmapFile(0,0)
{

}

HeightmapFile::~HeightmapFile()
{
    for(auto it(m_data.begin()); it != m_data.end(); it++)
    {
        for(auto it2(it->second.begin()); it2 != it->second.end(); it2++)
        {
            delete it2->second;
        }
    }
}

void HeightmapFile::setSize(int w, int h)
{
    m_width = w;
    m_height = h;
}

Pixel * HeightmapFile::operator()(int x, int y) const
{
    if(!contains(x,y))
        return nullptr;
    return m_data.find(x)->second.find(y)->second;
}

void HeightmapFile::set(int x, int y, Pixel * p)
{
    if(contains(x,y))
        delete m_data[x][y];
    m_data[x][y] = p;

    if(m_p_min == nullptr || m_p_min->getHeight() > p->getHeight())
        m_p_min = p;
    if(m_p_max == nullptr || m_p_max->getHeight() < p->getHeight())
        m_p_max = p;
}

int HeightmapFile::width() const
{
    return m_width;
}

int HeightmapFile::height() const
{
    return m_height;
}

Pixel * HeightmapFile::min() const
{
    return m_p_min;
}

Pixel * HeightmapFile::max() const
{
    return m_p_max;
}

bool HeightmapFile::contains(int x, int y) const
{
    auto it(m_data.find(x));

    if(it != m_data.end())
    {
        auto it2(it->second.find(y));
        if(it2 != it->second.end())
            return true;
    }

    return false;
}
