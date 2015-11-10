#include "terragen_file_parser.h"
#include <algorithm>
#include "include/terragen_file_manager/terragen_file.h"

#include <iostream>
bool TerragenFileParser::parse(const HeightmapFile * heightmap_file, unsigned short base_height, float scale, float planet_radius,
                               int mode, const std::string & filename, int width, int height, float height_scale)
{
    TerragenFile ter_file;

    ter_file.m_header_data.base_height = TerragenFileParser::meters_to_terrain_units(base_height * height_scale, scale);
    ter_file.m_header_data.depth = height;
    ter_file.m_header_data.width = width;
    ter_file.m_header_data.scale = scale;
    ter_file.m_header_data.planet_radius = planet_radius;
    ter_file.m_header_data.mode = mode;

    // Now insert the data

    ter_file.m_height_data = (float *) malloc(sizeof(float)*heightmap_file->width() * heightmap_file->height());

    float min(-1), max(-1);
    for(int x(0); x < width; x++)
    {
        for(int y(0); y < height; y++)
        {
            float h(meters_to_terrain_units((*heightmap_file)(x,y)->getHeight()*height_scale, scale));
            if(min == -1 || h < min)
                min = h;
            if(max == -1 || h > max)
                max = h;

            ter_file(x,y) = h;
        }
    }

    // Calculate the range
    int extreme((int) std::ceil(std::max(max, std::abs(min))));

    ter_file.m_header_data.height_scale = (extreme/32767.0f); // h is a signed 16 bit integer
//    ter_file.m_header_data.min_height = min;
//    ter_file.m_header_data.max_height = max;

    return ter_file.write(filename);
}

float TerragenFileParser::meters_to_terrain_units(unsigned short distance_in_meters, float scale)
{
    return ((float)distance_in_meters)/scale;
}
