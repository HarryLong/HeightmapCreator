#include "terragen_file_parser.h"
#include <algorithm>

#include <iostream>
bool TerragenFileParser::parse(const DecodedGreyScalePNGFile & decoded_png_file, unsigned short base_height, float scale, float planet_radius,
                               int mode, const std::string & filename, float height_scale)
{
    TerragenFile ter_file;

    ter_file.m_header_data.base_height = TerragenFileParser::meters_to_terrain_units(base_height * height_scale, scale);
    ter_file.m_header_data.depth = decoded_png_file.height();
    ter_file.m_header_data.width = decoded_png_file.width();
    ter_file.m_header_data.scale = scale;
    ter_file.m_header_data.planet_radius = planet_radius;
    ter_file.m_header_data.mode = mode;

    // Calculate the range
    float min_in_terrain_units (TerragenFileParser::meters_to_terrain_units(decoded_png_file.min()->getHeight()*height_scale, scale));
    float max_in_terrain_units (TerragenFileParser::meters_to_terrain_units(decoded_png_file.max()->getHeight()*height_scale, scale));

    int extreme((int) std::ceil(std::max(max_in_terrain_units, std::abs(min_in_terrain_units))));

    ter_file.m_header_data.height_scale = (extreme/32767.0f); // h is a signed 16 bit integer

    // Now insert the data

    ter_file.m_height_data = (float *) malloc(sizeof(float)*decoded_png_file.width() * decoded_png_file.height());

    for(int x(0); x < decoded_png_file.width(); x++)
    {
        for(int y(0); y < decoded_png_file.height(); y++)
        {
            ter_file(x,y) = (ter_file.m_header_data.base_height * height_scale) + (meters_to_terrain_units(decoded_png_file(x,y)->getHeight()*height_scale, scale));
        }
    }

    return ter_file.write(filename);
}

float TerragenFileParser::meters_to_terrain_units(unsigned short distance_in_meters, float scale)
{
    return ((float)distance_in_meters)/scale;
}
