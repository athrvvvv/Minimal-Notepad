#include "mainwindow.h"
#include "version_check.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    prompt_version_update::version_update();
    return app.exec();
}
