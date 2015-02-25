#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTranslator translator;
    translator.load("en");
    a.installTranslator(&translator);
    w.show();

    return a.exec();
}
