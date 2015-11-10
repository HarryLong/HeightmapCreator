#include "terragen_heightmap_wrapper.h"
#include "include/terragen_file_manager/terragen_file.h"


TerragenHeightmapWrapper::TerragenHeightmapWrapper(const QString & filename)
{
    TerragenFile terragen_file(filename.toStdString());

    for(int x(0); x < terragen_file.m_header_data.width; x++)
    {
        for(int y(0); y < terragen_file.m_header_data.depth; y++)
        {
            set(x, y, new Pixel(terragen_file(x,y)*terragen_file.m_header_data.scale));
        }
    }
    setSize(terragen_file.m_header_data.width, terragen_file.m_header_data.depth);
}

TerragenHeightmapWrapper::~TerragenHeightmapWrapper()
{

}
