#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::on_btn_close_clicked()
{
    close();
}

void About::on_label_11_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link,QUrl::TolerantMode));
}

void About::on_label_12_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link,QUrl::TolerantMode));

}
