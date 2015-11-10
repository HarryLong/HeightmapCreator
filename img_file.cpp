#include "img_file.h"
#include "utils.h"
#include <fstream>
#include <QString>
#include <iostream>
#include <QStringList>
#include <QDebug>
#include <cstdio>

ImgFile::ImgFile(const QString & filename)
{
    if(FileUtils::exists(filename.toStdString()))
    {
        FILE *file = fopen(filename.toStdString().c_str(), "r");
        char * code;
        size_t n = 0;
        int c;
        int w(-1), h(-1), processed_values(0);

        if (file != NULL)
        {
            std::string v;
            while ((c = fgetc(file)) != EOF) {
                if(c == ' ') // split
                {
                    QString q_value(QString::fromStdString(v));
                    if(w == -1) // First value --> height
                        w = q_value.toInt();
                    else if(h == -1)
                        h = q_value.toInt();
                    else
                    {
                        float value(q_value.toFloat());
                        set(processed_values % w, processed_values / w, new Pixel(value));
                        if(processed_values++ % 100000 == 0)
                        {
                            qCritical() << ((((float)processed_values)/(w*h))*100) << " %";
                        }
                    }
                    v.clear();
                }
                else
                {
                    v += (char)c;
                }
//                qCritical() << "Processed: " << processed_values;

            }
            {
                QString q_value(QString::fromStdString(v));
                float value(q_value.toFloat());
                set(processed_values % w, processed_values / w, new Pixel(value));
            }
        }
        else
            std::cerr << "Failed to open file: " << filename.toStdString() << std::endl;

        if(w == -1 || h == -1)
            std::cerr << "Error occured when parsing file: " << filename.toStdString() << std::endl;
        else if(processed_values != w*h)
            std::cerr << "Processed " << processed_values << " / " << (w*h) << std::endl;
        else
            setSize(w, h);
    }
    else
        std::cerr << "File doesn't exist: " << filename.toStdString() << std::endl;
}

ImgFile::~ImgFile()
{

}

QString ImgFile::pop_next_value(QString & values)
{
    int space_idx(0);

    // Find first occurence of space
    {
        int i(0);
        while(values.at(i) != ' ' && i < values.size())
            i++;

        space_idx = i;
    }

    QString ret(values.left(space_idx));


    values.remove(0,space_idx+1);


    return ret;
}

