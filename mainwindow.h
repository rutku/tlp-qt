#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QMap>
#include <QListView>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_cb_tlp_active_clicked();

    void on_cb_cpu_scaling_governor_on_ac_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_5_clicked();

    void on_checkBox_6_clicked();

    void on_checkBox_7_clicked();

    void on_checkBox_8_clicked();

    void on_checkBox_9_clicked();

    void on_checkBox_77_clicked();

    void on_checkBox_10_clicked();

    void on_checkBox_11_clicked();

    void on_checkBox_12_clicked();

    void on_checkBox_13_clicked();

    void on_checkBox_14_clicked();

    void on_checkBox_15_clicked();

    void on_checkBox_16_clicked();

    void on_checkBox_17_clicked();

    void on_checkBox_22_clicked();

    void on_checkBox_23_clicked();

    void on_checkBox_24_clicked();

    void on_checkBox_25_clicked();

    void on_checkBox_26_clicked();

    void on_checkBox_27_clicked();

    void on_checkBox_28_clicked();

    void on_checkBox_29_clicked();

    void on_checkBox_30_clicked();

    void on_checkBox_31_clicked();

    void on_checkBox_53_clicked();

    void on_checkBox_55_clicked();

    void on_checkBox_57_clicked();

    void on_checkBox_78_clicked();

    void on_checkBox_58_clicked();

    void on_checkBox_32_clicked();

    void on_checkBox_33_clicked();

    void on_checkBox_34_clicked();

    void on_checkBox_35_clicked();

    void on_checkBox_36_clicked();

    void on_checkBox_37_clicked();

    void on_checkBox_38_clicked();

    void on_checkBox_40_clicked();

    void on_checkBox_42_clicked();

    void on_checkBox_44_clicked();

    void on_checkBox_46_clicked();

    void on_checkBox_48_clicked();

    void on_checkBox_50_clicked();

    void on_checkBox_52_clicked();

    void on_checkBox_59_clicked();

    void on_checkBox_61_clicked();

    void on_checkBox_62_clicked();

    void on_checkBox_63_clicked();

    void on_checkBox_65_clicked();

    void on_checkBox_67_clicked();

    void on_checkBox_68_clicked();

    void on_checkBox_70_clicked();

    void on_checkBox_71_clicked();

    void on_checkBox_72_clicked();

    void on_checkBox_73_clicked();

    void on_checkBox_75_clicked();

    void on_checkBox_76_clicked();

    void on_checkBox_154_clicked();

    void on_checkBox_155_clicked();

    void on_checkBox_156_clicked();

    void on_checkBox_157_clicked();

    void on_checkBox_158_clicked();

    void on_checkBox_241_clicked();

    void on_checkBox_242_clicked();

    void on_checkBox_243_clicked();

    void on_checkBox_329_clicked();

    void on_checkBox_331_clicked();

    void on_checkBox_330_clicked();

    void on_checkBox_69_clicked();

private:
    Ui::MainWindow *ui;
    QStringList data;
    QStringList markedLines;
    QMap<QString,QString> values;
    QMap<QString,double> valueActive;
    QListView* pView = new QListView();
    QStandardItemModel* pModel = new QStandardItemModel();
    void loadMarkedLines();
    void readConfig();
    void prepareGui();
    void setActivate(bool b,QString value);
};

#endif // MAINWINDOW_H
