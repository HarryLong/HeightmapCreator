#ifndef TERRAGEN_HEIGHTMAP_WRAPPER_H
#define TERRAGEN_HEIGHTMAP_WRAPPER_H

#include "heightmap_file.h"
#include <QString>

class TerragenHeightmapWrapper : public HeightmapFile
{
public:
    TerragenHeightmapWrapper(const QString & filename);
    ~TerragenHeightmapWrapper();
};

#endif // TERRAGEN_HEIGHTMAP_WRAPPER_H
