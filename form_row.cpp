#include "form_row.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QBoxLayout>

FormRow::FormRow(QString label, bool button, QString button_text, QWidget * parent, Qt::WindowFlags f) :
    QWidget(parent,f), m_button(NULL)
{
    m_label = new QLabel(label, this);

    m_line_edit = new QLineEdit(this);
    m_line_edit->setEnabled(false);

    if(button)
        m_button = new QPushButton(button_text, this);

    init_layout();
}

FormRow::~FormRow()
{

}

QPushButton * FormRow::getButton()
{
    return m_button;
}

void FormRow::setContent(QString content)
{
    m_line_edit->setText(content);
}

void FormRow::clearContent()
{
    m_line_edit->setText("");
}

QString FormRow::getContent()
{
    return m_line_edit->text().trimmed();
}

void FormRow::init_layout()
{
    QHBoxLayout * layout (new QHBoxLayout);

    layout->addWidget(m_label,3, Qt::AlignRight);
    layout->addWidget(m_line_edit,5);
    // Button or padding
    if(m_button)
        layout->addWidget(m_button, 2, Qt::AlignLeft);
    else
        layout->addWidget(new QLabel(""),2, Qt::AlignLeft);

    setLayout(layout);
}

void FormRow::setEditable(bool enable)
{
    m_line_edit->setEnabled(enable);
}
