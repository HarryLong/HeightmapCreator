#include "central_widget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QtWidgets>
#include "lodepng/lodepng.h"
#include "terragen_file_parser.h"

CentralWidget::CentralWidget(QWidget * parent, Qt::WindowFlags f) : QWidget(parent, f)
{
    // Heightmap form elements
    m_heightmap_form_elements[HEIGHTMAP_FILE] = new FormRow("File:", true, "Load");
    m_heightmap_form_elements[BIT_DEPTH] = new FormRow("Bit depth:");
    m_heightmap_form_elements[POINTS_X] = new FormRow("Points (X):");
    m_heightmap_form_elements[POINTS_Y] = new FormRow("Points (Y):");
    m_heightmap_form_elements[MIN_HEIGHT] = new FormRow("Minimum height (m):");
    m_heightmap_form_elements[MAX_HEIGHT] = new FormRow("Maximum height (m):");
    // Terragen form elements
    m_terragen_form_elements[BASE_HEIGHT] = m_terragen_form_elements[BASE_HEIGHT] = new FormRow("Base height (m) (optional):");
    m_terragen_form_elements[ACTUAL_SIZE] = m_terragen_form_elements[ACTUAL_SIZE] = new FormRow("Actual size (m):");
    m_terragen_form_elements[PLANET_RADIUS] = m_terragen_form_elements[PLANET_RADIUS] = new FormRow("Planet Radius (optional):");
    m_terragen_form_elements[MODE] = m_terragen_form_elements[MODE] = new FormRow("Mode (optional):");
    m_terragen_form_elements[HEIGHT_SCALE] = m_terragen_form_elements[HEIGHT_SCALE] = new FormRow("Height Scale (optional):");
    m_create_btn = new QPushButton("Create terragen file");

    init_layout();
    enable_terragen_form_elements(false);
    establish_connections();
}

CentralWidget::~CentralWidget()
{

}

void CentralWidget::init_layout()
{
    QVBoxLayout * layout (new QVBoxLayout);

    // Add HeightMap Elements
    {
        QLabel * heightmap_title = new QLabel(this);
        heightmap_title->setTextFormat(Qt::RichText);
        heightmap_title->setText("<html> <span style=\"font-size:14pt; font-weight:600;\"> HEIGHTMAP INFO </span> </html>");
        layout->addWidget(heightmap_title, 1, Qt::AlignCenter);
    }
    for(std::pair<HeightMapFormElements, FormRow *> form_element : m_heightmap_form_elements)
        layout->addWidget(form_element.second,0);

    // Add Terragen Settings
    {
        QLabel * terragen_title = new QLabel(this);
        terragen_title->setTextFormat(Qt::RichText);
        terragen_title->setText("<html> <span style=\"font-size:14pt; font-weight:600;\"> TERRAGEN SETTINGS </span> </html>");
        layout->addWidget(terragen_title, 1, Qt::AlignCenter);
    }
    for(std::pair<TerragenFormElements, FormRow *> form_element : m_terragen_form_elements)
        layout->addWidget(form_element.second,0);

    layout->addWidget(m_create_btn, 0, Qt::AlignCenter);
    layout->addWidget(new QLabel(""), 1); // Padding

    setLayout(layout);
}

void CentralWidget::enable_terragen_form_elements(bool enabled)
{
    for(std::pair<TerragenFormElements, FormRow *> terragen_form_element : m_terragen_form_elements)
        terragen_form_element.second->setEditable(enabled);
    m_create_btn->setEnabled(enabled);
}

void CentralWidget::establish_connections()
{
    connect(m_create_btn, SIGNAL(clicked()), this, SLOT(create_terragen_file()));
    connect(m_heightmap_form_elements[HEIGHTMAP_FILE]->getButton(), SIGNAL(clicked()), this, SLOT(launch_heightmap_loader()));
}

#include <iostream>
void CentralWidget::launch_heightmap_loader()
{
    QFileDialog::Options options;
    QString selectedFilter;

    QString filename ( QFileDialog::getOpenFileName(this,
                                                    tr("Select heightmap image"),
                                                    QDir::homePath(),
                                                    tr("PNG files (*.png)"),
                                                    &selectedFilter,
                                                    options));

    if(filename != QString::null)
    {
        std::vector<unsigned char> image; //the raw pixels
        unsigned int width, height, error;
        lodepng::State state;

        // Decode PNG file
        {
            state.decoder.color_convert = 0;
            std::vector<unsigned char> png;
            lodepng::load_file(png, filename.toStdString()); //load the image file with given filename
            error = lodepng::decode(image, width, height, state, png);
        }

        //if there's an error, display it
        if(!error)
        {
            DecodedGreyScalePNGFile::GrayScaleMode mode (state.info_png.color.bitdepth == 8 ? DecodedGreyScalePNGFile::GrayScaleMode::_8_BIT :
                                                                                                DecodedGreyScalePNGFile::GrayScaleMode::_16_BIT);
            m_decoded_png_file = new DecodedGreyScalePNGFile(image, width, height, mode);
            valid_heightmap_loaded(filename);
        }
        else // Disable editable widgets
        {
            std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
            invalid_heightmap_loaded();
        }
    }
}

#define TER_FILE_EXTENSION ".ter"
void CentralWidget::create_terragen_file()
{
    QString filename ( QFileDialog::getSaveFileName(this,
                                                    tr("Save as"),
                                                    QDir::homePath()) );

    if(filename != QString::null)
    {
        if(!filename.endsWith(TER_FILE_EXTENSION))
            filename.append(TER_FILE_EXTENSION);

        if(TerragenFileParser::parse(*m_decoded_png_file, get_base_height(), get_scale(), get_planet_radius(), get_mode(), filename.toStdString(),
                                     get_height_scale()))
        {
            QMessageBox::information(this, "Success!", QString("Successfully created terragen file: ").append(filename), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(this, "Fail!", QString("Failed created terragen file: ").append(filename).append("\nSee logs for more information."), QMessageBox::Ok);
        }
    }
}

void CentralWidget::valid_heightmap_loaded(QString filename)
{
    enable_terragen_form_elements(true);
    m_heightmap_form_elements[HEIGHTMAP_FILE]->setContent(filename);
    // Bit depth
    {
        DecodedGreyScalePNGFile::GrayScaleMode mode (m_decoded_png_file->getMode());
        if(mode == DecodedGreyScalePNGFile::GrayScaleMode::_8_BIT )
            m_heightmap_form_elements[BIT_DEPTH]->setContent(QString::number(8));
        else // 16 bit
            m_heightmap_form_elements[BIT_DEPTH]->setContent(QString::number(16));
    }
    m_heightmap_form_elements[POINTS_X]->setContent(QString::number(m_decoded_png_file->width()));
    m_heightmap_form_elements[POINTS_Y]->setContent(QString::number(m_decoded_png_file->height()));
    m_heightmap_form_elements[MIN_HEIGHT]->setContent(QString::number(m_decoded_png_file->min()->getHeight()));
    m_heightmap_form_elements[MAX_HEIGHT]->setContent(QString::number(m_decoded_png_file->max()->getHeight()));
}

void CentralWidget::invalid_heightmap_loaded()
{
    enable_terragen_form_elements(false);
    QMessageBox::critical(this, "Error", "Failed to load the selected heightmap file. See logs for more information", QMessageBox::Ok);

    // Remove all content
    for(std::pair<HeightMapFormElements, FormRow *> form_element : m_heightmap_form_elements)
        form_element.second->clearContent();
}

bool CentralWidget::is_set(TerragenFormElements element)
{
    return !get_content(element).isEmpty();
}

QString CentralWidget::get_content(TerragenFormElements element)
{
    return m_terragen_form_elements[element]->getContent();
}

#define DEFAULT_BASE_HEIGHT 0
int CentralWidget::get_base_height()
{
    if(is_set(TerragenFormElements::BASE_HEIGHT))
       return get_content(TerragenFormElements::BASE_HEIGHT).toInt();

    return DEFAULT_BASE_HEIGHT;
}

#define DEFAULT_SCALE 30.0f
float CentralWidget::get_scale()
{
    if(is_set(TerragenFormElements::ACTUAL_SIZE))
       return (get_content(TerragenFormElements::ACTUAL_SIZE).toFloat()/m_decoded_png_file->width());

    return DEFAULT_SCALE;
}

#define DEFAULT_PLANET_RADIUS 6370.0f
float CentralWidget::get_planet_radius()
{
    if(is_set(TerragenFormElements::PLANET_RADIUS))
       return get_content(TerragenFormElements::PLANET_RADIUS).toFloat();

    return DEFAULT_PLANET_RADIUS;
}

#define DEFAULT_MODE 0
int CentralWidget::get_mode()
{
    if(is_set(TerragenFormElements::MODE))
       return get_content(TerragenFormElements::MODE).toInt();

    return DEFAULT_MODE;
}

#define DEFAULT_HEIGHT_SCALE 1.0F
float CentralWidget::get_height_scale()
{
    if(is_set(TerragenFormElements::HEIGHT_SCALE))
       return get_content(TerragenFormElements::HEIGHT_SCALE).toFloat();

    return DEFAULT_HEIGHT_SCALE;
}

