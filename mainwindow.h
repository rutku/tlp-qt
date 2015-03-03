#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QMap>
#include "about.h"

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
    void about();
    void quit();
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

    void on_checkBox_81_clicked();

    void on_checkBox_82_clicked();

    void on_checkBox_83_clicked();

    void on_checkBox_84_clicked();

    void on_checkBox_74_clicked();

    void on_checkBox_80_clicked();

    void on_checkBox_clicked();

    void on_checkBox_18_clicked();

    void on_checkBox_19_clicked();

    void on_checkBox_20_clicked();

    void on_checkBox_21_clicked();

    void on_checkBox_54_clicked();

    void on_checkBox_79_clicked();

    void on_checkBox_56_clicked();

    void on_checkBox_39_clicked();

    void on_checkBox_41_clicked();

    void on_checkBox_43_clicked();

    void on_checkBox_45_clicked();

    void on_checkBox_47_clicked();

    void on_checkBox_49_clicked();

    void on_checkBox_51_clicked();

    void on_checkBox_60_clicked();

    void on_checkBox_64_clicked();

    void on_checkBox_66_clicked();

    void on_spinBox_9_editingFinished();

    void on_spinBox_10_editingFinished();

    void on_spinBox_editingFinished();

    void on_spinBox_2_editingFinished();

    void on_spinBox_3_editingFinished();

    void on_spinBox_4_editingFinished();

    void on_spinBox_5_editingFinished();

    void on_spinBox_6_editingFinished();

    void on_spinBox_8_editingFinished();

    void on_spinBox_7_editingFinished();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_4_editingFinished();

    void on_lineEdit_5_editingFinished();

    void on_lineEdit_6_editingFinished();

    void on_lineEdit_7_editingFinished();

    void on_lineEdit_8_editingFinished();

    void on_lineEdit_9_editingFinished();

    void on_lineEdit_11_editingFinished();

    void on_lineEdit_12_editingFinished();

    void on_lineEdit_25_editingFinished();

    void on_lineEdit_26_editingFinished();

    void on_lineEdit_27_editingFinished();

    void on_lineEdit_28_editingFinished();

    void on_lineEdit_29_editingFinished();

    void on_lineEdit_47_editingFinished();

    void on_lineEdit_48_editingFinished();

    void on_lineEdit_49_editingFinished();

    void on_lineEdit_70_editingFinished();

    void on_lineEdit_72_editingFinished();

    void on_lineEdit_71_editingFinished();

    void on_spinBox_11_editingFinished();

    void on_spinBox_12_editingFinished();

    void on_spinBox_13_editingFinished();

    void on_spinBox_14_editingFinished();

    void on_btn_save_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_comboBox_6_editTextChanged(const QString &arg1);

    void on_comboBox_7_editTextChanged(const QString &arg1);

    void on_comboBox_8_editTextChanged(const QString &arg1);

    void on_comboBox_9_editTextChanged(const QString &arg1);

    void on_comboBox_10_editTextChanged(const QString &arg1);

    void on_comboBox_5_currentIndexChanged(const QString &arg1);

    void on_comboBox_11_currentIndexChanged(const QString &arg1);

    void on_comboBox_12_currentIndexChanged(const QString &arg1);

    void on_comboBox_13_currentIndexChanged(const QString &arg1);

    void on_comboBox_14_currentIndexChanged(const QString &arg1);

    void on_comboBox_15_currentIndexChanged(const QString &arg1);

    void on_comboBox_16_currentIndexChanged(const QString &arg1);

    void on_comboBox_17_currentIndexChanged(const QString &arg1);

    void on_comboBox_18_currentIndexChanged(const QString &arg1);

    void on_comboBox_19_currentIndexChanged(const QString &arg1);

    void on_comboBox_20_currentIndexChanged(const QString &arg1);

    void on_comboBox_21_editTextChanged(const QString &arg1);

    void on_comboBox_22_editTextChanged(const QString &arg1);

    void on_actionAbout_triggered();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    About ab;
    QStringList data;
    QStringList markedLines;
    QMap<QString,QString> values;
    QMap<QString,double> valueActive;
    QFile file;
    void loadMarkedLines();
    void readConfig();
    void prepareGui();
    void setActivate(bool b,QString value);
    void setCheckBoxValue(bool b,QString value,QString t,QString f);
};

#endif // MAINWINDOW_H
