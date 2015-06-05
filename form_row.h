#ifndef FORM_ROW_H
#define FORM_ROW_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class FormRow : public QWidget
{
public:
    FormRow(QString label, bool button = false, QString button_text = QString::null, QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~FormRow();
    QPushButton * getButton();
    QString getContent();

public slots:
     void setEditable(bool enable);
     void setContent(QString content);
     void clearContent();

private:
    void init_layout();

    QLabel * m_label;
    QLineEdit * m_line_edit;
    QPushButton * m_button;
};

#endif // FORM_ROW_H
