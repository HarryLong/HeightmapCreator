#ifndef TERRAGEN_FILE_PARSER_H
#define TERRAGEN_FILE_PARSER_H

#include <vector>
#include "include/terragen_file_manager/terragen_file.h"
#include "png_file.h"

namespace TerragenFileParser {
    bool parse(const DecodedGreyScalePNGFile & decoded_png_file, unsigned short base_height, float scale, float planet_radius, int mode,
               const std::string & filename);

    float meters_to_terrain_units(unsigned short distance_in_meters, float scale);
}

#endif // TERRAGEN_FILE_PARSER_H
