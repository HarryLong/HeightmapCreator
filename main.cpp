#include <QApplication>
#include <QDesktopWidget>

#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow main_window;
    main_window.resize(main_window.sizeHint());
    main_window.showMaximized();
    return app.exec();
}
