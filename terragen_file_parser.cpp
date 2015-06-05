#include "terragen_file_parser.h"
#include <algorithm>

#include <iostream>
bool TerragenFileParser::parse(const DecodedGreyScalePNGFile & decoded_png_file, unsigned short base_height, float scale, float planet_radius, int mode, const std::string & filename)
{
    TerragenFile ter_file;

    ter_file.m_header_data.base_height = TerragenFileParser::meters_to_terrain_units(base_height, scale);
    ter_file.m_header_data.depth = decoded_png_file.height();
    ter_file.m_header_data.width = decoded_png_file.width();
    ter_file.m_header_data.scale = scale;
    ter_file.m_header_data.planet_radius = planet_radius;
    ter_file.m_header_data.mode = mode;

    // Calculate the range
    float min_in_terrain_units (TerragenFileParser::meters_to_terrain_units(decoded_png_file.min().getHeight(), scale));
    float max_in_terrain_units (TerragenFileParser::meters_to_terrain_units(decoded_png_file.max().getHeight(), scale));

    int extreme((int) std::ceil(std::max(max_in_terrain_units, std::abs(min_in_terrain_units))));

    ter_file.m_header_data.height_scale = (extreme/32768.0f); // h is a signed 16 bit integer

    // Now insert the data

    ter_file.m_height_data = (float *) malloc(sizeof(float)*decoded_png_file.width() * decoded_png_file.height());
    float min_meters(50000);
    float max_meters(-1);

    float min_tu(50000);
    float max_tu(-1);

    for(int x(0); x < decoded_png_file.width(); x++)
    {
        for(int y(0); y < decoded_png_file.height(); y++)
        {
            unsigned short height_in_meters(decoded_png_file(x,y).getHeight());

            if(height_in_meters > max_meters)
                max_meters = height_in_meters;
            if(height_in_meters < min_meters)
                min_meters = height_in_meters;

            float height_in_tu(meters_to_terrain_units(decoded_png_file(x,y).getHeight(), scale));
            if(height_in_tu < min_tu)
                min_tu = height_in_tu;
            if(height_in_tu > max_tu)
                max_tu = height_in_tu;

            ter_file(x,y) = (ter_file.m_header_data.base_height + meters_to_terrain_units(decoded_png_file(x,y).getHeight(), scale));

        }
    }
    std::cout << "METERS --> Min: " << min_meters << " | Max: " << max_meters << std::endl;
    std::cout << "TU --> Min: " << min_tu << " | Max: " << max_tu << std::endl;

    return ter_file.write(filename);
}

float TerragenFileParser::meters_to_terrain_units(unsigned short distance_in_meters, float scale)
{
    return ((float)distance_in_meters)/scale;
}
