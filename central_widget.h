#ifndef CENTRAL_WIDGET_H
#define CENTRAL_WIDGET_H

#include <QWidget>
#include "form_row.h"
#include <map>
#include "png_file.h"
#include "include/terragen_file_manager/terragen_file.h"

enum HeightMapFormElements{
    HEIGHTMAP_FILE,
    POINTS_X,
    POINTS_Y,
    MIN_HEIGHT,
    MAX_HEIGHT
};

enum TerragenFormElements{
    BASE_HEIGHT,
    SCALE,
    PLANET_RADIUS,
    MODE,
};

class QPushButton;
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
    void init_layout();
    void enable_terragen_form_elements(bool enabled);
    void establish_connections();

    bool is_set(TerragenFormElements element);
    QString get_content(TerragenFormElements element);

    int get_base_height();
    float get_scale();
    float get_planet_radius();
    int get_mode();

    std::map<HeightMapFormElements, FormRow*> m_heightmap_form_elements;
    std::map<TerragenFormElements, FormRow*> m_terragen_form_elements;
    QPushButton * m_create_btn;
    DecodedGreyScalePNGFile m_decoded_png_file;
    TerragenFile m_parsed_terragen_file;
};

#endif // CENTRAL_WIDGET_H
