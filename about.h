#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QDesktopServices>
#include <QUrl>
namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private slots:
    void on_btn_close_clicked();

    void on_label_11_linkActivated(const QString &link);

    void on_label_12_linkActivated(const QString &link);

private:
    Ui::About *ui;
};

#endif // ABOUT_H
