#ifndef CENTRAL_WIDGET_H
#define CENTRAL_WIDGET_H

#include <QWidget>
#include "form_row.h"
#include <map>
#include "heightmap_file.h"

class QPushButton;
class ImgFile;
class CentralWidget : public QWidget
{
Q_OBJECT
public:
    CentralWidget(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~CentralWidget();

private slots:
    void launch_heightmap_loader();
    void create_terragen_file();
    void valid_heightmap_loaded(QString filename);
    void invalid_heightmap_loaded();

private:
    enum HeightMapFormElements{
        HEIGHTMAP_FILE,
        FILE_TYPE,
        BIT_DEPTH,
        WIDTH,
        HEIGHT,
        MIN_HEIGHT,
        MAX_HEIGHT
    };

    enum TerragenFormElements{
        BASE_HEIGHT,
        ACTUAL_SIZE,
        PLANET_RADIUS,
        MODE,
        HEIGHT_SCALE,
        REPRODUCE_WIDTH,
        REPRODUCE_HEIGHT,
    };

    enum FileType{
        PNG,
        IMG,
        TER
    };

    void init_layout();
    void enable_terragen_form_elements(bool enabled);
    void establish_connections();
    void delete_files();

    bool is_set(TerragenFormElements element);
    QString get_content(TerragenFormElements element);

    int get_base_height();
    float get_scale();
    float get_planet_radius();
    int get_mode();
    float get_height_scale();
    int get_width();
    int get_height();

    std::map<HeightMapFormElements, FormRow*> m_heightmap_form_elements;
    std::map<TerragenFormElements, FormRow*> m_terragen_form_elements;
    QPushButton * m_create_btn;
    HeightmapFile * m_heightmap;
    FileType m_filetype;
};

#endif // CENTRAL_WIDGET_H
