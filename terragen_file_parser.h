#ifndef TERRAGEN_FILE_PARSER_H
#define TERRAGEN_FILE_PARSER_H

#include <vector>
#include "png_file.h"
#include <iostream>

namespace TerragenFileParser {
    bool parse(const HeightmapFile * decoded_png_file, unsigned short base_height, float scale, float planet_radius, int mode,
               const std::string & filename, int width, int height, float height_scale = 1.0f);

    float meters_to_terrain_units(unsigned short distance_in_meters, float scale);
}

#endif // TERRAGEN_FILE_PARSER_H
