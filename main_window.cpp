#include "main_window.h"
#include "central_widget.h"

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), m_central_widget(new CentralWidget(this))
{
    init_layout();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init_layout()
{
    setCentralWidget(m_central_widget);
}
