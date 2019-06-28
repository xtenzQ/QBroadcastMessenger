#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Resource init
    Q_INIT_RESOURCE(resources);
    QFont amazingFont("Consolas", 8, QFont::Monospace, true);
    QApplication::setFont(amazingFont);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
