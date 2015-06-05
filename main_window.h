#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class CentralWidget;
class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
    ~MainWindow();

private:
    void init_layout();

    CentralWidget * m_central_widget;
};

#endif // MAIN_WINDOW_H
