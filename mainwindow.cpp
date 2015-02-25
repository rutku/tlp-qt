#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readConfig()
{
    //QFile file("/etc/default/tlp");
    QFile file("/home/rutku/Belgeler/tlp");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;

         QTextStream in(&file);
         while (!in.atEnd()) {
             QString line = in.readLine();
             data.append(line);
             //qDebug()<<line;
         }

}
