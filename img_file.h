#ifndef IMG_FILE_H
#define IMG_FILE_H

#include "heightmap_file.h"
#include <QString>

class ImgFile : public HeightmapFile{
public:
    ImgFile(const QString & filename);
    ~ImgFile();

private:
    QString pop_next_value(QString & values);
};

#endif // IMG_FILE_H
