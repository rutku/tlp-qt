#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //"/etc/default/tlp";
    file.setFileName("/home/rutku/Belgeler/tlp");
    loadMarkedLines();
    readConfig();
    prepareGui();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about()
{
    qDebug()<<"Hakkında";
}

void MainWindow::quit()
{
    qDebug()<<"Çıkış";
}

void MainWindow::loadMarkedLines()
{
    markedLines<<"TLP_ENABLE"<<"DISK_IDLE_SECS_ON_AC"<<"DISK_IDLE_SECS_ON_BAT"
              <<"MAX_LOST_WORK_SECS_ON_AC"<<"MAX_LOST_WORK_SECS_ON_BAT"
             <<"CPU_SCALING_GOVERNOR_ON_AC"<<"CPU_SCALING_GOVERNOR_ON_BAT"
            <<"CPU_SCALING_MIN_FREQ_ON_AC"<<"CPU_SCALING_MAX_FREQ_ON_AC"
           <<"CPU_SCALING_MIN_FREQ_ON_BAT"<<"CPU_SCALING_MAX_FREQ_ON_BAT"
          <<"CPU_MIN_PERF_ON_AC"<<"CPU_MAX_PERF_ON_AC"<<"CPU_MIN_PERF_ON_BAT"
         <<"CPU_MAX_PERF_ON_BAT"<<"CPU_BOOST_ON_AC"<<"CPU_BOOST_ON_BAT"
        <<"SCHED_POWERSAVE_ON_AC"<<"SCHED_POWERSAVE_ON_BAT"<<"NMI_WATCHDOG"
       <<"PHC_CONTROLS"<<"ENERGY_PERF_POLICY_ON_AC"<<"ENERGY_PERF_POLICY_ON_BAT"
      <<"DISK_DEVICES"<<"DISK_APM_LEVEL_ON_AC"<<"DISK_APM_LEVEL_ON_BAT"
     <<"DISK_SPINDOWN_TIMEOUT_ON_AC"<<"DISK_SPINDOWN_TIMEOUT_ON_BAT"
     <<"DISK_IOSCHED"<<"SATA_LINKPWR_ON_AC"<<"SATA_LINKPWR_ON_BAT"<<"PCIE_ASPM_ON_AC"
    <<"PCIE_ASPM_ON_BAT"<<"RADEON_POWER_PROFILE_ON_AC"<<"RADEON_POWER_PROFILE_ON_BAT"
    <<"RADEON_DPM_STATE_ON_AC"<<"RADEON_DPM_STATE_ON_BAT"<<"RADEON_DPM_PERF_LEVEL_ON_AC"
    <<"RADEON_DPM_PERF_LEVEL_ON_BAT"<<"WIFI_PWR_ON_AC"<<"WIFI_PWR_ON_BAT"<<"WOL_DISABLE"
    <<"SOUND_POWER_SAVE_ON_AC"<<"SOUND_POWER_SAVE_ON_BAT"<<"SOUND_POWER_SAVE_CONTROLLER"
    <<"BAY_POWEROFF_ON_BAT"<<"BAY_DEVICE"<<"RUNTIME_PM_ON_AC"<<"RUNTIME_PM_ON_BAT"
    <<"RUNTIME_PM_ALL"<<"RUNTIME_PM_BLACKLIST"<<"RUNTIME_PM_DRIVER_BLACKLIST"
    <<"USB_AUTOSUSPEND"<<"USB_BLACKLIST"<<"USB_DRIVER_BLACKLIST"<<"USB_BLACKLIST_WWAN"
    <<"USB_WHITELIST"<<"USB_AUTOSUSPEND_DISABLE_ON_SHUTDOWN"<<"RESTORE_DEVICE_STATE_ON_STARTUP"
    <<"DEVICES_TO_DISABLE_ON_STARTUP"<<"DEVICES_TO_ENABLE_ON_STARTUP"<<"DEVICES_TO_DISABLE_ON_SHUTDOWN"
    <<"DEVICES_TO_ENABLE_ON_SHUTDOWN"<<"DEVICES_TO_ENABLE_ON_AC"<<"DEVICES_TO_DISABLE_ON_BAT"
    <<"DEVICES_TO_DISABLE_ON_BAT_NOT_IN_USE"<<"DEVICES_TO_DISABLE_ON_LAN_CONNECT"<<"DEVICES_TO_DISABLE_ON_WIFI_CONNECT"
    <<"DEVICES_TO_DISABLE_ON_WWAN_CONNECT"<<"DEVICES_TO_ENABLE_ON_LAN_DISCONNECT"<<"DEVICES_TO_ENABLE_ON_WIFI_DISCONNECT"
    <<"DEVICES_TO_ENABLE_ON_WWAN_DISCONNECT"<<"DEVICES_TO_ENABLE_ON_DOCK"<<"DEVICES_TO_DISABLE_ON_DOCK"
    <<"DEVICES_TO_ENABLE_ON_UNDOCK"<<"DEVICES_TO_DISABLE_ON_UNDOCK"<<"START_CHARGE_THRESH_BAT0"
    <<"STOP_CHARGE_THRESH_BAT0"<<"START_CHARGE_THRESH_BAT1"<<"STOP_CHARGE_THRESH_BAT1";

    for (int i = 0; i < markedLines.size(); ++i) {
        values.insert(markedLines.at(i),"");
        valueActive.insert(markedLines.at(i),false);
    }
}

void MainWindow::readConfig()
{

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        data.append(line);
        for (int i = 0; i < markedLines.size(); ++i) {
            QString word = markedLines.at(i);
            bool isThere = line.contains(word);
            if (isThere) {
                if (line.at(0)!='#')
                    valueActive[word]=true;

                QStringList splitLine = line.split("=");
                QString text = splitLine.at(1);
                values[word]=text.remove(QChar('"'),Qt::CaseInsensitive);

            }

        }
    }
    file.close();
}

void MainWindow::on_btn_save_clicked()
{
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < markedLines.size(); ++j) {
            QString word = markedLines.at(j);
            if (data.at(i).contains(word)) {
                QStringList splitLine=data.at(i).split("=");
                QString orgDefine= splitLine.at(0);
                QString orgValue = splitLine.at(1);

                if (orgDefine.at(0) =='#') {
                    if (valueActive[word]) {
                        orgDefine.remove('#');
                    }

                    QString tmpValue=values[word];
                    if (orgValue.indexOf(QChar('"'))>-1) {
                        tmpValue.prepend('"');
                        tmpValue.append('"');
                    }
                    orgValue = tmpValue;
                    QString newValue = QString("%1=%2").arg(orgDefine)
                            .arg(orgValue);
                    data.removeAt(i);
                    data.insert(i,newValue);

                }else
                {
                    if (!valueActive[word]) {
                        orgDefine.prepend('#');
                    }

                    QString tmpValue=values[word];
                    if (orgValue.indexOf(QChar('"'))>-1) {
                        tmpValue.prepend('"');
                        tmpValue.append('"');
                    }
                    orgValue = tmpValue;
                    QString newValue = QString("%1=%2").arg(orgDefine)
                            .arg(orgValue);
                    data.removeAt(i);
                    data.insert(i,newValue);
                }
            }
        }
    }

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for (int i = 0; i < data.size(); ++i) {
        out << data.at(i)<< "\n";
    }
    file.close();
}

void MainWindow::setActivate(bool b, QString value)
{
    if (b)
        valueActive[value]=true;
    else
        valueActive[value]=false;
    prepareGui();
}

void MainWindow::prepareGui()
{
    if (values["TLP_ENABLE"]!="0")
    {
        ui->cb_tlp_active->setChecked(true);
    }
    else
    {
        ui->cb_tlp_active->setChecked(false);
    }
    if (values["DISK_IDLE_SECS_ON_AC"]!="0")
    {
        ui->checkBox_74->setChecked(true);
    }
    else
    {
        ui->checkBox_74->setChecked(false);
    }
    if (values["DISK_IDLE_SECS_ON_BAT"]!="0")
    {
        ui->checkBox_80->setChecked(true);
    }
    else
    {
        ui->checkBox_80->setChecked(false);
    }
    ui->spinBox_9->setValue(values["MAX_LOST_WORK_SECS_ON_AC"].toInt(0));
    ui->spinBox_10->setValue(values["MAX_LOST_WORK_SECS_ON_BAT"].toInt(0));


    if (valueActive["CPU_SCALING_GOVERNOR_ON_AC"])
    {
        ui->comboBox->setEnabled(true);
        ui->cb_cpu_scaling_governor_on_ac->setChecked(true);
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(values["CPU_SCALING_GOVERNOR_ON_AC"]));
    }
    else
    {
        ui->comboBox->setEnabled(false);
        ui->cb_cpu_scaling_governor_on_ac->setChecked(false);
    }

    if (valueActive["CPU_SCALING_GOVERNOR_ON_BAT"])
    {
        ui->comboBox_2->setEnabled(true);
        ui->checkBox_2->setChecked(true);
        ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(values["CPU_SCALING_GOVERNOR_ON_BAT"]));
    }
    else
    {
        ui->comboBox_2->setEnabled(false);
        ui->checkBox_2->setChecked(false);
    }

    if (valueActive["CPU_SCALING_MIN_FREQ_ON_AC"])
    {
        ui->spinBox->setEnabled(true);
        ui->checkBox_3->setChecked(true);
        ui->spinBox->setValue(values["CPU_SCALING_MIN_FREQ_ON_AC"].toInt(0));
    }
    else
    {
        ui->spinBox->setEnabled(false);
        ui->checkBox_3->setChecked(false);
    }


    if (valueActive["CPU_SCALING_MAX_FREQ_ON_AC"])
    {
        ui->spinBox_2->setEnabled(true);
        ui->checkBox_4->setChecked(true);
        ui->spinBox_2->setValue(values["CPU_SCALING_MAX_FREQ_ON_AC"].toInt(0));

    }
    else
    {
        ui->spinBox_2->setEnabled(false);
        ui->checkBox_4->setChecked(false);
    }

    if (valueActive["CPU_SCALING_MIN_FREQ_ON_BAT"])
    {
        ui->spinBox_3->setEnabled(true);
        ui->checkBox_5->setChecked(true);
        ui->spinBox_3->setValue(values["CPU_SCALING_MIN_FREQ_ON_BAT"].toInt(0));

    }
    else
    {
        ui->spinBox_3->setEnabled(false);
        ui->checkBox_5->setChecked(false);
    }

    if (valueActive["CPU_SCALING_MAX_FREQ_ON_BAT"])
    {
        ui->spinBox_4->setEnabled(true);
        ui->checkBox_6->setChecked(true);
        ui->spinBox_4->setValue(values["CPU_SCALING_MAX_FREQ_ON_BAT"].toInt(0));
    }
    else
    {
        ui->spinBox_4->setEnabled(false);
        ui->checkBox_6->setChecked(false);
    }

    if (valueActive["CPU_MIN_PERF_ON_AC"])
    {
        ui->spinBox_5->setEnabled(true);
        ui->checkBox_7->setChecked(true);
        ui->spinBox_5->setValue(values["CPU_MIN_PERF_ON_AC"].toInt(0));

    }
    else
    {
        ui->spinBox_5->setEnabled(false);
        ui->checkBox_7->setChecked(false);
    }

    if (valueActive["CPU_MAX_PERF_ON_AC"])
    {
        ui->spinBox_6->setEnabled(true);
        ui->checkBox_8->setChecked(true);
        ui->spinBox_6->setValue(values["CPU_MAX_PERF_ON_AC"].toInt(0));

    }
    else
    {
        ui->spinBox_6->setEnabled(false);
        ui->checkBox_8->setChecked(false);
    }

    if (valueActive["CPU_MIN_PERF_ON_BAT"])
    {
        ui->spinBox_8->setEnabled(true);
        ui->checkBox_77->setChecked(true);
        ui->spinBox_8->setValue(values["CPU_MIN_PERF_ON_BAT"].toInt(0));

    }
    else
    {
        ui->spinBox_8->setEnabled(false);
        ui->checkBox_77->setChecked(false);
    }

    if (valueActive["CPU_MAX_PERF_ON_BAT"])
    {
        ui->spinBox_7->setEnabled(true);
        ui->checkBox_9->setChecked(true);
        ui->spinBox_7->setValue(values["CPU_MAX_PERF_ON_BAT"].toInt(0));

    }
    else
    {
        ui->spinBox_7->setEnabled(false);
        ui->checkBox_9->setChecked(false);
    }

    if (valueActive["CPU_BOOST_ON_AC"])
    {
        ui->checkBox->setEnabled(true);
        ui->checkBox_10->setChecked(true);
        if (values["CPU_BOOST_ON_AC"]=="0") {
            ui->checkBox->setChecked(false);
            ui->checkBox->setText("disable");
        }else
        {
            ui->checkBox->setChecked(true);
            ui->checkBox->setText("allow");
        }

    }
    else
    {
        ui->checkBox->setEnabled(false);
        ui->checkBox_10->setChecked(false);
    }

    if (valueActive["CPU_BOOST_ON_BAT"])
    {
        ui->checkBox_18->setEnabled(true);
        ui->checkBox_11->setChecked(true);
        if (values["CPU_BOOST_ON_BAT"]=="0") {
            ui->checkBox_18->setChecked(false);
            ui->checkBox_18->setText("disable");
        }else
        {
            ui->checkBox_18->setChecked(true);
            ui->checkBox_18->setText("allow");
        }
    }
    else
    {
        ui->checkBox_18->setEnabled(false);
        ui->checkBox_11->setChecked(false);
    }

    if (valueActive["SCHED_POWERSAVE_ON_AC"])
    {
        ui->checkBox_19->setEnabled(true);
        ui->checkBox_12->setChecked(true);
        if (values["SCHED_POWERSAVE_ON_AC"]=="0") {
            ui->checkBox_19->setChecked(false);
            ui->checkBox_19->setText("disable");
        }else
        {
            ui->checkBox_19->setChecked(true);
            ui->checkBox_19->setText("allow");
        }
    }
    else
    {
        ui->checkBox_19->setEnabled(false);
        ui->checkBox_12->setChecked(false);
    }

    if (valueActive["SCHED_POWERSAVE_ON_BAT"])
    {
        ui->checkBox_20->setEnabled(true);
        ui->checkBox_13->setChecked(true);

        if (values["SCHED_POWERSAVE_ON_BAT"]=="0") {
            ui->checkBox_20->setChecked(false);
            ui->checkBox_20->setText("disable");
        }else
        {
            ui->checkBox_20->setChecked(true);
            ui->checkBox_20->setText("allow");
        }
    }
    else
    {
        ui->checkBox_20->setEnabled(false);
        ui->checkBox_13->setChecked(false);
    }

    if (valueActive["NMI_WATCHDOG"])
    {
        ui->checkBox_21->setEnabled(true);
        ui->checkBox_14->setChecked(true);
        if (values["NMI_WATCHDOG"]=="0") {
            ui->checkBox_21->setChecked(false);
            ui->checkBox_21->setText("disable");
        }else
        {
            ui->checkBox_21->setChecked(true);
            ui->checkBox_21->setText("enable");
        }
    }
    else
    {
        ui->checkBox_21->setEnabled(false);
        ui->checkBox_14->setChecked(false);
    }

    if (valueActive["PHC_CONTROLS"])
    {
        ui->lineEdit->setEnabled(true);
        ui->checkBox_15->setChecked(true);
        ui->lineEdit->setText(values["PHC_CONTROLS"]);
    }
    else
    {
        ui->lineEdit->setEnabled(false);
        ui->checkBox_15->setChecked(false);
    }

    if (valueActive["ENERGY_PERF_POLICY_ON_AC"])
    {
        ui->comboBox_3->setEnabled(true);
        ui->checkBox_16->setChecked(true);
        ui->comboBox_3->setCurrentIndex(ui->comboBox_3->findText(values["ENERGY_PERF_POLICY_ON_AC"]));
    }
    else
    {
        ui->comboBox_3->setEnabled(false);
        ui->checkBox_16->setChecked(false);
    }

    if (valueActive["ENERGY_PERF_POLICY_ON_BAT"])
    {
        ui->comboBox_4->setEnabled(true);
        ui->checkBox_17->setChecked(true);
        ui->comboBox_4->setCurrentIndex(ui->comboBox_4->findText(values["ENERGY_PERF_POLICY_ON_BAT"]));
    }
    else
    {
        ui->comboBox_4->setEnabled(false);
        ui->checkBox_17->setChecked(false);
    }

    if (valueActive["DISK_DEVICES"])
    {
        ui->comboBox_6->setEnabled(true);
        ui->checkBox_22->setChecked(true);

        QString val = values["DISK_DEVICES"];
        int index = ui->comboBox_6->findText(val);
        if (index > -1)
            ui->comboBox_6->setCurrentIndex(index);
        else
        {
            ui->comboBox_6->addItem(val);
            ui->comboBox_6->setCurrentIndex(ui->comboBox_6->count()-1);
        }

    }
    else
    {
        ui->comboBox_6->setEnabled(false);
        ui->checkBox_22->setChecked(false);
    }

    if (valueActive["DISK_APM_LEVEL_ON_AC"])
    {
        ui->comboBox_7->setEnabled(true);
        ui->checkBox_23->setChecked(true);

        QString val = values["DISK_APM_LEVEL_ON_AC"];
        int index = ui->comboBox_7->findText(val);
        if (index > -1)
            ui->comboBox_7->setCurrentIndex(index);
        else
        {
            ui->comboBox_7->addItem(val);
            ui->comboBox_7->setCurrentIndex(ui->comboBox_7->count()-1);
        }


    }
    else
    {
        ui->comboBox_7->setEnabled(false);
        ui->checkBox_23->setChecked(false);
    }

    if (valueActive["DISK_APM_LEVEL_ON_BAT"])
    {
        ui->comboBox_8->setEnabled(true);
        ui->checkBox_24->setChecked(true);

        QString val = values["DISK_APM_LEVEL_ON_BAT"];
        int index = ui->comboBox_8->findText(val);
        if (index > -1)
            ui->comboBox_8->setCurrentIndex(index);
        else
        {
            ui->comboBox_8->addItem(val);
            ui->comboBox_8->setCurrentIndex(ui->comboBox_8->count()-1);
        }

    }
    else
    {
        ui->comboBox_8->setEnabled(false);
        ui->checkBox_24->setChecked(false);
    }

    if (valueActive["DISK_SPINDOWN_TIMEOUT_ON_AC"])
    {
        ui->comboBox_9->setEnabled(true);
        ui->checkBox_25->setChecked(true);

        QString val = values["DISK_SPINDOWN_TIMEOUT_ON_AC"];
        int index = ui->comboBox_9->findText(val);
        if (index > -1)
            ui->comboBox_9->setCurrentIndex(index);
        else
        {
            ui->comboBox_9->addItem(val);
            ui->comboBox_9->setCurrentIndex(ui->comboBox_9->count()-1);
        }

    }
    else
    {
        ui->comboBox_9->setEnabled(false);
        ui->checkBox_25->setChecked(false);
    }

    if (valueActive["DISK_SPINDOWN_TIMEOUT_ON_BAT"])
    {
        ui->comboBox_10->setEnabled(true);
        ui->checkBox_26->setChecked(true);

        QString val = values["DISK_SPINDOWN_TIMEOUT_ON_BAT"];
        int index = ui->comboBox_10->findText(val);
        if (index > -1)
            ui->comboBox_10->setCurrentIndex(index);
        else
        {
            ui->comboBox_10->addItem(val);
            ui->comboBox_10->setCurrentIndex(ui->comboBox_10->count()-1);
        }
    }
    else
    {
        ui->comboBox_10->setEnabled(false);
        ui->checkBox_26->setChecked(false);
    }

    if (valueActive["DISK_IOSCHED"])
    {
        ui->comboBox_5->setEnabled(true);
        ui->checkBox_27->setChecked(true);

        QString val = values["DISK_IOSCHED"];
        int index = ui->comboBox_5->findText(val);
        if (index > -1)
            ui->comboBox_5->setCurrentIndex(index);
        else
        {
            ui->comboBox_5->addItem(val);
            ui->comboBox_5->setCurrentIndex(ui->comboBox_5->count()-1);
        }
    }
    else
    {
        ui->comboBox_5->setEnabled(false);
        ui->checkBox_27->setChecked(false);
    }

    if (valueActive["SATA_LINKPWR_ON_AC"])
    {
        ui->comboBox_11->setEnabled(true);
        ui->checkBox_28->setChecked(true);

        QString val = values["SATA_LINKPWR_ON_AC"];
        int index = ui->comboBox_11->findText(val);
        if (index > -1)
            ui->comboBox_11->setCurrentIndex(index);
        else
        {
            ui->comboBox_11->addItem(val);
            ui->comboBox_11->setCurrentIndex(ui->comboBox_11->count()-1);
        }
    }
    else
    {
        ui->comboBox_11->setEnabled(false);
        ui->checkBox_28->setChecked(false);
    }

    if (valueActive["SATA_LINKPWR_ON_BAT"])
    {
        ui->comboBox_12->setEnabled(true);
        ui->checkBox_29->setChecked(true);

        QString val = values["SATA_LINKPWR_ON_BAT"];
        int index = ui->comboBox_12->findText(val);
        if (index > -1)
            ui->comboBox_12->setCurrentIndex(index);
        else
        {
            ui->comboBox_12->addItem(val);
            ui->comboBox_12->setCurrentIndex(ui->comboBox_12->count()-1);
        }
    }
    else
    {
        ui->comboBox_12->setEnabled(false);
        ui->checkBox_29->setChecked(false);
    }

    if (valueActive["PCIE_ASPM_ON_AC"])
    {
        ui->comboBox_13->setEnabled(true);
        ui->checkBox_30->setChecked(true);

        QString val = values["PCIE_ASPM_ON_AC"];
        int index = ui->comboBox_13->findText(val);
        if (index > -1)
            ui->comboBox_13->setCurrentIndex(index);
        else
        {
            ui->comboBox_13->addItem(val);
            ui->comboBox_13->setCurrentIndex(ui->comboBox_13->count()-1);
        }
    }
    else
    {
        ui->comboBox_13->setEnabled(false);
        ui->checkBox_30->setChecked(false);
    }

    if (valueActive["PCIE_ASPM_ON_BAT"])
    {
        ui->comboBox_14->setEnabled(true);
        ui->checkBox_31->setChecked(true);

        QString val = values["PCIE_ASPM_ON_BAT"];
        int index = ui->comboBox_14->findText(val);
        if (index > -1)
            ui->comboBox_14->setCurrentIndex(index);
        else
        {
            ui->comboBox_14->addItem(val);
            ui->comboBox_14->setCurrentIndex(ui->comboBox_14->count()-1);
        }
    }
    else
    {
        ui->comboBox_14->setEnabled(false);
        ui->checkBox_31->setChecked(false);
    }

    if (valueActive["RUNTIME_PM_ON_AC"])
    {
        ui->checkBox_54->setEnabled(true);
        ui->checkBox_53->setChecked(true);
        if (values["RUNTIME_PM_ON_AC"]=="on") {
            ui->checkBox_54->setChecked(false);
            ui->checkBox_54->setText("disable");
        }else
        {
            ui->checkBox_54->setChecked(true);
            ui->checkBox_54->setText("enable");
        }


    }
    else
    {
        ui->checkBox_54->setEnabled(false);
        ui->checkBox_53->setChecked(false);
    }

    if (valueActive["RUNTIME_PM_ON_BAT"])
    {
        ui->checkBox_79->setEnabled(true);
        ui->checkBox_78->setChecked(true);

        if (values["RUNTIME_PM_ON_BAT"]=="on") {
            ui->checkBox_79->setChecked(false);
            ui->checkBox_79->setText("disable");
        }else
        {
            ui->checkBox_79->setChecked(true);
            ui->checkBox_79->setText("enable");
        }
    }
    else
    {
        ui->checkBox_79->setEnabled(false);
        ui->checkBox_78->setChecked(false);
    }

    if (valueActive["RUNTIME_PM_ALL"])
    {
        ui->checkBox_56->setEnabled(true);
        ui->checkBox_55->setChecked(true);

        if (values["RUNTIME_PM_ON_BAT"]=="0") {
            ui->checkBox_56->setChecked(false);
            ui->checkBox_56->setText("disable");
        }else
        {
            ui->checkBox_56->setChecked(true);
            ui->checkBox_56->setText("enable");
        }
    }
    else
    {
        ui->checkBox_56->setEnabled(false);
        ui->checkBox_55->setChecked(false);
    }

    if (valueActive["RUNTIME_PM_BLACKLIST"])
    {
        ui->lineEdit_2->setEnabled(true);
        ui->checkBox_57->setChecked(true);
        ui->lineEdit_2->setText(values["RUNTIME_PM_BLACKLIST"]);
    }
    else
    {
        ui->lineEdit_2->setEnabled(false);
        ui->checkBox_57->setChecked(false);
    }

    if (valueActive["RUNTIME_PM_DRIVER_BLACKLIST"])
    {
        ui->lineEdit_3->setEnabled(true);
        ui->checkBox_58->setChecked(true);
        ui->lineEdit_3->setText(values["RUNTIME_PM_DRIVER_BLACKLIST"]);
    }
    else
    {
        ui->lineEdit_3->setEnabled(false);
        ui->checkBox_58->setChecked(false);
    }

    if (valueActive["RADEON_POWER_PROFILE_ON_AC"])
    {
        ui->comboBox_15->setEnabled(true);
        ui->checkBox_32->setChecked(true);
        ui->comboBox_15->setCurrentIndex(ui->comboBox_15->findText(values["RADEON_POWER_PROFILE_ON_AC"]));

    }
    else
    {
        ui->comboBox_15->setEnabled(false);
        ui->checkBox_32->setChecked(false);
    }

    if (valueActive["RADEON_POWER_PROFILE_ON_BAT"])
    {
        ui->comboBox_16->setEnabled(true);
        ui->checkBox_33->setChecked(true);
        ui->comboBox_16->setCurrentIndex(ui->comboBox_16->findText(values["RADEON_POWER_PROFILE_ON_BAT"]));

    }
    else
    {
        ui->comboBox_16->setEnabled(false);
        ui->checkBox_33->setChecked(false);
    }

    if (valueActive["RADEON_DPM_STATE_ON_AC"])
    {
        ui->comboBox_17->setEnabled(true);
        ui->checkBox_34->setChecked(true);
        ui->comboBox_17->setCurrentIndex(ui->comboBox_17->findText(values["RADEON_DPM_STATE_ON_AC"]));

    }
    else
    {
        ui->comboBox_17->setEnabled(false);
        ui->checkBox_34->setChecked(false);
    }

    if (valueActive["RADEON_DPM_STATE_ON_BAT"])
    {
        ui->comboBox_18->setEnabled(true);
        ui->checkBox_35->setChecked(true);
        ui->comboBox_18->setCurrentIndex(ui->comboBox_18->findText(values["RADEON_DPM_STATE_ON_BAT"]));

    }
    else
    {
        ui->comboBox_18->setEnabled(false);
        ui->checkBox_35->setChecked(false);
    }

    if (valueActive["RADEON_DPM_PERF_LEVEL_ON_AC"])
    {
        ui->comboBox_19->setEnabled(true);
        ui->checkBox_36->setChecked(true);
        ui->comboBox_19->setCurrentIndex(ui->comboBox_19->findText(values["RADEON_DPM_PERF_LEVEL_ON_AC"]));

    }
    else
    {
        ui->comboBox_19->setEnabled(false);
        ui->checkBox_36->setChecked(false);
    }

    if (valueActive["RADEON_DPM_PERF_LEVEL_ON_BAT"])
    {
        ui->comboBox_20->setEnabled(true);
        ui->checkBox_37->setChecked(true);
        ui->comboBox_20->setCurrentIndex(ui->comboBox_20->findText(values["RADEON_DPM_PERF_LEVEL_ON_BAT"]));

    }
    else
    {
        ui->comboBox_20->setEnabled(false);
        ui->checkBox_37->setChecked(false);
    }

    if (valueActive["WIFI_PWR_ON_AC"])
    {
        ui->checkBox_39->setEnabled(true);
        ui->checkBox_38->setChecked(true);

        if (values["WIFI_PWR_ON_AC"]=="1") {
            ui->checkBox_39->setChecked(false);
            ui->checkBox_39->setText("disable");
        }else
        {
            ui->checkBox_39->setChecked(true);
            ui->checkBox_39->setText("enable");
        }
    }
    else
    {
        ui->checkBox_39->setEnabled(false);
        ui->checkBox_38->setChecked(false);
    }

    if (valueActive["WIFI_PWR_ON_BAT"])
    {
        ui->checkBox_41->setEnabled(true);
        ui->checkBox_40->setChecked(true);

        if (values["WIFI_PWR_ON_BAT"]=="1") {
            ui->checkBox_41->setChecked(false);
            ui->checkBox_41->setText("disable");
        }else
        {
            ui->checkBox_41->setChecked(true);
            ui->checkBox_41->setText("enable");
        }
    }
    else
    {
        ui->checkBox_41->setEnabled(false);
        ui->checkBox_40->setChecked(false);
    }

    if (valueActive["WOL_DISABLE"])
    {
        ui->checkBox_43->setEnabled(true);
        ui->checkBox_42->setChecked(true);

        if (values["WOL_DISABLE"]=="N") {
            ui->checkBox_43->setChecked(false);
            ui->checkBox_43->setText("No");
        }else
        {
            ui->checkBox_43->setChecked(true);
            ui->checkBox_43->setText("Yes");
        }
    }
    else
    {
        ui->checkBox_43->setEnabled(false);
        ui->checkBox_42->setChecked(false);
    }

    if (valueActive["SOUND_POWER_SAVE_ON_AC"])
    {
        ui->checkBox_45->setEnabled(true);
        ui->checkBox_44->setChecked(true);

        if (values["SOUND_POWER_SAVE_ON_AC"]=="0") {
            ui->checkBox_45->setChecked(false);
            ui->checkBox_45->setText("Disable");
        }else
        {
            ui->checkBox_45->setChecked(true);
            ui->checkBox_45->setText("Enable");
        }
    }
    else
    {
        ui->checkBox_45->setEnabled(false);
        ui->checkBox_44->setChecked(false);
    }

    if (valueActive["SOUND_POWER_SAVE_ON_BAT"])
    {
        ui->checkBox_47->setEnabled(true);
        ui->checkBox_46->setChecked(true);

        if (values["SOUND_POWER_SAVE_ON_BAT"]=="0") {
            ui->checkBox_47->setChecked(false);
            ui->checkBox_47->setText("Disable");
        }else
        {
            ui->checkBox_47->setChecked(true);
            ui->checkBox_47->setText("Enable");
        }
    }
    else
    {
        ui->checkBox_47->setEnabled(false);
        ui->checkBox_46->setChecked(false);
    }

    if (valueActive["SOUND_POWER_SAVE_CONTROLLER"])
    {
        ui->checkBox_49->setEnabled(true);
        ui->checkBox_48->setChecked(true);

        if (values["SOUND_POWER_SAVE_CONTROLLER"]=="N") {
            ui->checkBox_49->setChecked(false);
            ui->checkBox_49->setText("No");
        }else
        {
            ui->checkBox_49->setChecked(true);
            ui->checkBox_49->setText("Yes");
        }
    }
    else
    {
        ui->checkBox_49->setEnabled(false);
        ui->checkBox_48->setChecked(false);
    }

    if (valueActive["BAY_POWEROFF_ON_BAT"])
    {
        ui->checkBox_51->setEnabled(true);
        ui->checkBox_50->setChecked(true);

        if (values["BAY_POWEROFF_ON_BAT"]=="0") {
            ui->checkBox_51->setChecked(false);
            ui->checkBox_51->setText("Disable");
        }else
        {
            ui->checkBox_51->setChecked(true);
            ui->checkBox_51->setText("Enable");
        }
    }
    else
    {
        ui->checkBox_51->setEnabled(false);
        ui->checkBox_50->setChecked(false);
    }

    if (valueActive["BAY_DEVICE"])
    {
        ui->comboBox_21->setEnabled(true);
        ui->checkBox_52->setChecked(true);

        QString val = values["BAY_DEVICE"];
        int index = ui->comboBox_21->findText(val);
        if (index > -1)
            ui->comboBox_21->setCurrentIndex(index);
        else
        {
            ui->comboBox_21->addItem(val);
            ui->comboBox_21->setCurrentIndex(ui->comboBox_21->count()-1);
        }
    }
    else
    {
        ui->comboBox_21->setEnabled(false);
        ui->checkBox_52->setChecked(false);
    }

    if (valueActive["USB_AUTOSUSPEND"])
    {
        ui->checkBox_60->setEnabled(true);
        ui->checkBox_59->setChecked(true);

        if (values["USB_AUTOSUSPEND"]=="0") {
            ui->checkBox_60->setChecked(false);
            ui->checkBox_60->setText("Disable");
        }else
        {
            ui->checkBox_60->setChecked(true);
            ui->checkBox_60->setText("Enable");
        }
    }
    else
    {
        ui->checkBox_60->setEnabled(false);
        ui->checkBox_59->setChecked(false);
    }

    if (valueActive["USB_BLACKLIST"])
    {
        ui->lineEdit_4->setEnabled(true);
        ui->checkBox_61->setChecked(true);
        ui->lineEdit_4->setText(values["USB_BLACKLIST"]);
    }
    else
    {
        ui->lineEdit_4->setEnabled(false);
        ui->checkBox_61->setChecked(false);
    }

    if (valueActive["USB_DRIVER_BLACKLIST"])
    {
        ui->comboBox_22->setEnabled(true);
        ui->checkBox_62->setChecked(true);

        QString val = values["USB_DRIVER_BLACKLIST"];
        int index = ui->comboBox_22->findText(val);
        if (index > -1)
            ui->comboBox_22->setCurrentIndex(index);
        else
        {
            ui->comboBox_22->addItem(val);
            ui->comboBox_22->setCurrentIndex(ui->comboBox_22->count()-1);
        }
    }
    else
    {
        ui->comboBox_22->setEnabled(false);
        ui->checkBox_62->setChecked(false);
    }

    if (valueActive["USB_BLACKLIST_WWAN"])
    {
        ui->checkBox_64->setEnabled(true);
        ui->checkBox_63->setChecked(true);

        if (values["USB_BLACKLIST_WWAN"]=="0") {
            ui->checkBox_60->setChecked(false);
            ui->checkBox_60->setText("Don't exclude");
        }else
        {
            ui->checkBox_60->setChecked(true);
            ui->checkBox_60->setText("Exclude");
        }
    }
    else
    {
        ui->checkBox_64->setEnabled(false);
        ui->checkBox_63->setChecked(false);
    }

    if (valueActive["USB_WHITELIST"])
    {
        ui->lineEdit_5->setEnabled(true);
        ui->checkBox_65->setChecked(true);
        ui->lineEdit_5->setText(values["USB_WHITELIST"]);
    }
    else
    {
        ui->lineEdit_5->setEnabled(false);
        ui->checkBox_65->setChecked(false);
    }

    if (valueActive["USB_AUTOSUSPEND_DISABLE_ON_SHUTDOWN"])
    {
        ui->checkBox_66->setEnabled(true);
        ui->checkBox_67->setChecked(true);

        if (values["USB_AUTOSUSPEND_DISABLE_ON_SHUTDOWN"]=="0") {
            ui->checkBox_66->setChecked(false);
            ui->checkBox_66->setText("Disable");
        }else
        {
            ui->checkBox_66->setChecked(true);
            ui->checkBox_66->setText("Enable");
        }
    }
    else
    {
        ui->checkBox_66->setEnabled(false);
        ui->checkBox_67->setChecked(false);
    }

    if (valueActive["RESTORE_DEVICE_STATE_ON_STARTUP"])
    {
        ui->checkBox_69->setEnabled(true);
        ui->checkBox_68->setChecked(true);

        if (values["RESTORE_DEVICE_STATE_ON_STARTUP"]=="0") {
            ui->checkBox_69->setChecked(false);
            ui->checkBox_69->setText("Disable");
        }else
        {
            ui->checkBox_69->setChecked(true);
            ui->checkBox_69->setText("Enable");
        }
    }
    else
    {
        ui->checkBox_69->setEnabled(false);
        ui->checkBox_68->setChecked(false);
    }

    if (valueActive["DEVICES_TO_DISABLE_ON_STARTUP"])
    {
        ui->lineEdit_6->setEnabled(true);
        ui->checkBox_70->setChecked(true);
        ui->lineEdit_6->setText(values["DEVICES_TO_DISABLE_ON_STARTUP"]);
    }
    else
    {
        ui->lineEdit_6->setEnabled(false);
        ui->checkBox_70->setChecked(false);
    }

    if (valueActive["DEVICES_TO_ENABLE_ON_STARTUP"])
    {
        ui->lineEdit_7->setEnabled(true);
        ui->checkBox_71->setChecked(true);
        ui->lineEdit_7->setText(values["DEVICES_TO_ENABLE_ON_STARTUP"]);

    }
    else
    {
        ui->lineEdit_7->setEnabled(false);
        ui->checkBox_71->setChecked(false);
    }

    if (valueActive["DEVICES_TO_DISABLE_ON_SHUTDOWN"])
    {
        ui->lineEdit_8->setEnabled(true);
        ui->checkBox_72->setChecked(true);
        ui->lineEdit_8->setText(values["DEVICES_TO_DISABLE_ON_SHUTDOWN"]);

    }
    else
    {
        ui->lineEdit_8->setEnabled(false);
        ui->checkBox_72->setChecked(false);
    }

    if (valueActive["DEVICES_TO_ENABLE_ON_SHUTDOWN"])
    {
        ui->lineEdit_9->setEnabled(true);
        ui->checkBox_73->setChecked(true);
        ui->lineEdit_9->setText(values["DEVICES_TO_ENABLE_ON_SHUTDOWN"]);

    }
    else
    {
        ui->lineEdit_9->setEnabled(false);
        ui->checkBox_73->setChecked(false);
    }

    if (valueActive["DEVICES_TO_ENABLE_ON_AC"])
    {
        ui->lineEdit_11->setEnabled(true);
        ui->checkBox_75->setChecked(true);
        ui->lineEdit_11->setText(values["DEVICES_TO_ENABLE_ON_AC"]);
    }
    else
    {
        ui->lineEdit_11->setEnabled(false);
        ui->checkBox_75->setChecked(false);
    }

    if (valueActive["DEVICES_TO_DISABLE_ON_BAT"])
    {
        ui->lineEdit_12->setEnabled(true);
        ui->checkBox_76->setChecked(true);
        ui->lineEdit_12->setText(values["DEVICES_TO_DISABLE_ON_BAT"]);

    }
    else
    {
        ui->lineEdit_12->setEnabled(false);
        ui->checkBox_76->setChecked(false);
    }

    if (valueActive["DEVICES_TO_DISABLE_ON_BAT_NOT_IN_USE"])
    {
        ui->lineEdit_25->setEnabled(true);
        ui->checkBox_154->setChecked(true);
        ui->lineEdit_25->setText(values["DEVICES_TO_DISABLE_ON_BAT_NOT_IN_USE"]);

    }
    else
    {
        ui->lineEdit_25->setEnabled(false);
        ui->checkBox_154->setChecked(false);
    }

    if (valueActive["DEVICES_TO_DISABLE_ON_LAN_CONNECT"])
    {
        ui->lineEdit_26->setEnabled(true);
        ui->checkBox_155->setChecked(true);
        ui->lineEdit_26->setText(values["DEVICES_TO_DISABLE_ON_LAN_CONNECT"]);
    }
    else
    {
        ui->lineEdit_26->setEnabled(false);
        ui->checkBox_155->setChecked(false);
    }

    if (valueActive["DEVICES_TO_DISABLE_ON_WIFI_CONNECT"])
    {
        ui->lineEdit_27->setEnabled(true);
        ui->checkBox_156->setChecked(true);
        ui->lineEdit_27->setText(values["DEVICES_TO_DISABLE_ON_WIFI_CONNECT"]);

    }
    else
    {
        ui->lineEdit_27->setEnabled(false);
        ui->checkBox_156->setChecked(false);
    }

    if (valueActive["DEVICES_TO_DISABLE_ON_WWAN_CONNECT"])
    {
        ui->lineEdit_28->setEnabled(true);
        ui->checkBox_157->setChecked(true);
        ui->lineEdit_28->setText(values["DEVICES_TO_DISABLE_ON_WWAN_CONNECT"]);

    }
    else
    {
        ui->lineEdit_28->setEnabled(false);
        ui->checkBox_157->setChecked(false);
    }

    if (valueActive["DEVICES_TO_ENABLE_ON_LAN_DISCONNECT"])
    {
        ui->lineEdit_29->setEnabled(true);
        ui->checkBox_158->setChecked(true);
        ui->lineEdit_29->setText(values["DEVICES_TO_ENABLE_ON_LAN_DISCONNECT"]);
    }
    else
    {
        ui->lineEdit_29->setEnabled(false);
        ui->checkBox_158->setChecked(false);
    }

    if (valueActive["DEVICES_TO_ENABLE_ON_WIFI_DISCONNECT"])
    {
        ui->lineEdit_47->setEnabled(true);
        ui->checkBox_241->setChecked(true);
        ui->lineEdit_47->setText(values["DEVICES_TO_ENABLE_ON_WIFI_DISCONNECT"]);
    }
    else
    {
        ui->lineEdit_47->setEnabled(false);
        ui->checkBox_241->setChecked(false);
    }

    if (valueActive["DEVICES_TO_ENABLE_ON_WWAN_DISCONNECT"])
    {
        ui->lineEdit_48->setEnabled(true);
        ui->checkBox_242->setChecked(true);
        ui->lineEdit_48->setText(values["DEVICES_TO_ENABLE_ON_WWAN_DISCONNECT"]);

    }
    else
    {
        ui->lineEdit_48->setEnabled(false);
        ui->checkBox_242->setChecked(false);
    }

    if (valueActive["DEVICES_TO_ENABLE_ON_DOCK"])
    {
        ui->lineEdit_49->setEnabled(true);
        ui->checkBox_243->setChecked(true);
        ui->lineEdit_49->setText(values["DEVICES_TO_ENABLE_ON_DOCK"]);

    }
    else
    {
        ui->lineEdit_49->setEnabled(false);
        ui->checkBox_243->setChecked(false);
    }

    if (valueActive["DEVICES_TO_DISABLE_ON_DOCK"])
    {
        ui->lineEdit_70->setEnabled(true);
        ui->checkBox_329->setChecked(true);
        ui->lineEdit_70->setText(values["DEVICES_TO_DISABLE_ON_DOCK"]);

    }
    else
    {
        ui->lineEdit_70->setEnabled(false);
        ui->checkBox_329->setChecked(false);
    }

    if (valueActive["DEVICES_TO_ENABLE_ON_UNDOCK"])
    {
        ui->lineEdit_72->setEnabled(true);
        ui->checkBox_331->setChecked(true);
        ui->lineEdit_72->setText(values["DEVICES_TO_ENABLE_ON_UNDOCK"]);

    }
    else
    {
        ui->lineEdit_72->setEnabled(false);
        ui->checkBox_331->setChecked(false);
    }

    if (valueActive["DEVICES_TO_DISABLE_ON_UNDOCK"])
    {
        ui->lineEdit_71->setEnabled(true);
        ui->checkBox_330->setChecked(true);
        ui->lineEdit_71->setText(values["DEVICES_TO_DISABLE_ON_UNDOCK"]);

    }
    else
    {
        ui->lineEdit_71->setEnabled(false);
        ui->checkBox_330->setChecked(false);
    }
    if (valueActive["START_CHARGE_THRESH_BAT0"])
    {
        ui->spinBox_11->setEnabled(true);
        ui->checkBox_81->setChecked(true);
        ui->spinBox_11->setValue(values["START_CHARGE_THRESH_BAT0"].toInt(0));
    }
    else
    {
        ui->spinBox_11->setEnabled(false);
        ui->checkBox_81->setChecked(false);
    }
    if (valueActive["STOP_CHARGE_THRESH_BAT0"])
    {
        ui->spinBox_12->setEnabled(true);
        ui->checkBox_82->setChecked(true);
        ui->spinBox_12->setValue(values["STOP_CHARGE_THRESH_BAT0"].toInt(0));
    }
    else
    {
        ui->spinBox_12->setEnabled(false);
        ui->checkBox_82->setChecked(false);
    }
    if (valueActive["START_CHARGE_THRESH_BAT1"])
    {
        ui->spinBox_13->setEnabled(true);
        ui->checkBox_83->setChecked(true);
        ui->spinBox_13->setValue(values["START_CHARGE_THRESH_BAT1"].toInt(0));
    }
    else
    {
        ui->spinBox_13->setEnabled(false);
        ui->checkBox_83->setChecked(false);
    }
    if (valueActive["STOP_CHARGE_THRESH_BAT1"])
    {
        ui->spinBox_14->setEnabled(true);
        ui->checkBox_84->setChecked(true);
        ui->spinBox_14->setValue(values["STOP_CHARGE_THRESH_BAT1"].toInt(0));
    }
    else
    {
        ui->spinBox_14->setEnabled(false);
        ui->checkBox_84->setChecked(false);
    }
}



void MainWindow::setCheckBoxValue(bool b, QString value, QString t, QString f)
{
    if (b)
        values[value]=t;
    else
        values[value]=f;

}


void MainWindow::on_cb_tlp_active_clicked()
{
    setCheckBoxValue(ui->cb_tlp_active->isChecked(),"TLP_ENABLE","1","0");
}

void MainWindow::on_cb_cpu_scaling_governor_on_ac_clicked()
{
    setActivate(ui->cb_cpu_scaling_governor_on_ac->isChecked(),"CPU_SCALING_GOVERNOR_ON_AC");
}

void MainWindow::on_checkBox_2_clicked()
{
    setActivate(ui->checkBox_2->isChecked(),"CPU_SCALING_GOVERNOR_ON_BAT");
}

void MainWindow::on_checkBox_3_clicked()
{
    setActivate(ui->checkBox_3->isChecked(),"CPU_SCALING_MIN_FREQ_ON_AC");
}

void MainWindow::on_checkBox_4_clicked()
{
    setActivate(ui->checkBox_4->isChecked(),"CPU_SCALING_MAX_FREQ_ON_AC");
}

void MainWindow::on_checkBox_5_clicked()
{
    setActivate(ui->checkBox_5->isChecked(),"CPU_SCALING_MIN_FREQ_ON_BAT");
}

void MainWindow::on_checkBox_6_clicked()
{
    setActivate(ui->checkBox_6->isChecked(),"CPU_SCALING_MAX_FREQ_ON_BAT");
}

void MainWindow::on_checkBox_7_clicked()
{
    setActivate(ui->checkBox_7->isChecked(),"CPU_MIN_PERF_ON_AC");
}

void MainWindow::on_checkBox_8_clicked()
{
    setActivate(ui->checkBox_8->isChecked(),"CPU_MAX_PERF_ON_AC");
}

void MainWindow::on_checkBox_9_clicked()
{
    setActivate(ui->checkBox_9->isChecked(),"CPU_MAX_PERF_ON_BAT");
}

void MainWindow::on_checkBox_77_clicked()
{
    setActivate(ui->checkBox_77->isChecked(),"CPU_MIN_PERF_ON_BAT");
}

void MainWindow::on_checkBox_10_clicked()
{
    setActivate(ui->checkBox_10->isChecked(),"CPU_BOOST_ON_AC");
}

void MainWindow::on_checkBox_11_clicked()
{
    setActivate(ui->checkBox_11->isChecked(),"CPU_BOOST_ON_BAT");
}

void MainWindow::on_checkBox_12_clicked()
{
    setActivate(ui->checkBox_12->isChecked(),"SCHED_POWERSAVE_ON_AC");
}

void MainWindow::on_checkBox_13_clicked()
{
    setActivate(ui->checkBox_13->isChecked(),"SCHED_POWERSAVE_ON_BAT");
}

void MainWindow::on_checkBox_14_clicked()
{
    setActivate(ui->checkBox_14->isChecked(),"NMI_WATCHDOG");
}

void MainWindow::on_checkBox_15_clicked()
{
    setActivate(ui->checkBox_15->isChecked(),"PHC_CONTROLS");
}

void MainWindow::on_checkBox_16_clicked()
{
    setActivate(ui->checkBox_16->isChecked(),"ENERGY_PERF_POLICY_ON_AC");
}

void MainWindow::on_checkBox_17_clicked()
{
    setActivate(ui->checkBox_17->isChecked(),"ENERGY_PERF_POLICY_ON_BAT");
}

void MainWindow::on_checkBox_22_clicked()
{
    setActivate(ui->checkBox_22->isChecked(),"DISK_DEVICES");
}

void MainWindow::on_checkBox_23_clicked()
{
    setActivate(ui->checkBox_23->isChecked(),"DISK_APM_LEVEL_ON_AC");
}

void MainWindow::on_checkBox_24_clicked()
{
    setActivate(ui->checkBox_24->isChecked(),"DISK_APM_LEVEL_ON_BAT");
}

void MainWindow::on_checkBox_25_clicked()
{
    setActivate(ui->checkBox_25->isChecked(),"DISK_SPINDOWN_TIMEOUT_ON_AC");
}

void MainWindow::on_checkBox_26_clicked()
{
    setActivate(ui->checkBox_26->isChecked(),"DISK_SPINDOWN_TIMEOUT_ON_BAT");
}

void MainWindow::on_checkBox_27_clicked()
{
    setActivate(ui->checkBox_27->isChecked(),"DISK_IOSCHED");
}

void MainWindow::on_checkBox_28_clicked()
{
    setActivate(ui->checkBox_28->isChecked(),"SATA_LINKPWR_ON_AC");
}

void MainWindow::on_checkBox_29_clicked()
{
    setActivate(ui->checkBox_29->isChecked(),"SATA_LINKPWR_ON_BAT");
}

void MainWindow::on_checkBox_30_clicked()
{
    setActivate(ui->checkBox_30->isChecked(),"PCIE_ASPM_ON_AC");
}

void MainWindow::on_checkBox_31_clicked()
{
    setActivate(ui->checkBox_31->isChecked(),"PCIE_ASPM_ON_BAT");
}

void MainWindow::on_checkBox_53_clicked()
{
    setActivate(ui->checkBox_53->isChecked(),"RUNTIME_PM_ON_AC");
}

void MainWindow::on_checkBox_55_clicked()
{
    setActivate(ui->checkBox_55->isChecked(),"RUNTIME_PM_ALL");
}

void MainWindow::on_checkBox_57_clicked()
{
    setActivate(ui->checkBox_57->isChecked(),"RUNTIME_PM_BLACKLIST");
}

void MainWindow::on_checkBox_78_clicked()
{
    setActivate(ui->checkBox_78->isChecked(),"RUNTIME_PM_ON_BAT");
}

void MainWindow::on_checkBox_58_clicked()
{
    setActivate(ui->checkBox_58->isChecked(),"RUNTIME_PM_DRIVER_BLACKLIST");
}

void MainWindow::on_checkBox_32_clicked()
{
    setActivate(ui->checkBox_32->isChecked(),"RADEON_POWER_PROFILE_ON_AC");
}

void MainWindow::on_checkBox_33_clicked()
{
    setActivate(ui->checkBox_33->isChecked(),"RADEON_POWER_PROFILE_ON_BAT");
}

void MainWindow::on_checkBox_34_clicked()
{
    setActivate(ui->checkBox_34->isChecked(),"RADEON_DPM_STATE_ON_AC");
}

void MainWindow::on_checkBox_35_clicked()
{
    setActivate(ui->checkBox_35->isChecked(),"RADEON_DPM_STATE_ON_BAT");
}

void MainWindow::on_checkBox_36_clicked()
{
    setActivate(ui->checkBox_36->isChecked(),"RADEON_DPM_PERF_LEVEL_ON_AC");
}

void MainWindow::on_checkBox_37_clicked()
{
    setActivate(ui->checkBox_37->isChecked(),"RADEON_DPM_PERF_LEVEL_ON_BAT");
}

void MainWindow::on_checkBox_38_clicked()
{
    setActivate(ui->checkBox_38->isChecked(),"WIFI_PWR_ON_AC");
}

void MainWindow::on_checkBox_40_clicked()
{
    setActivate(ui->checkBox_40->isChecked(),"WIFI_PWR_ON_BAT");
}

void MainWindow::on_checkBox_42_clicked()
{
    setActivate(ui->checkBox_42->isChecked(),"WOL_DISABLE");
}

void MainWindow::on_checkBox_44_clicked()
{
    setActivate(ui->checkBox_44->isChecked(),"SOUND_POWER_SAVE_ON_AC");
}

void MainWindow::on_checkBox_46_clicked()
{
    setActivate(ui->checkBox_46->isChecked(),"SOUND_POWER_SAVE_ON_BAT");
}

void MainWindow::on_checkBox_48_clicked()
{
    setActivate(ui->checkBox_48->isChecked(),"SOUND_POWER_SAVE_CONTROLLER");
}

void MainWindow::on_checkBox_50_clicked()
{
    setActivate(ui->checkBox_50->isChecked(),"BAY_POWEROFF_ON_BAT");
}

void MainWindow::on_checkBox_52_clicked()
{
    setActivate(ui->checkBox_52->isChecked(),"BAY_DEVICE");
}

void MainWindow::on_checkBox_59_clicked()
{
    setActivate(ui->checkBox_59->isChecked(),"USB_AUTOSUSPEND");
}

void MainWindow::on_checkBox_61_clicked()
{
    setActivate(ui->checkBox_61->isChecked(),"USB_BLACKLIST");
}

void MainWindow::on_checkBox_62_clicked()
{
    setActivate(ui->checkBox_62->isChecked(),"USB_DRIVER_BLACKLIST");
}

void MainWindow::on_checkBox_63_clicked()
{
    setActivate(ui->checkBox_63->isChecked(),"USB_BLACKLIST_WWAN");
}

void MainWindow::on_checkBox_65_clicked()
{
    setActivate(ui->checkBox_65->isChecked(),"USB_WHITELIST");
}

void MainWindow::on_checkBox_67_clicked()
{
    setActivate(ui->checkBox_67->isChecked(),"USB_AUTOSUSPEND_DISABLE_ON_SHUTDOWN");
}

void MainWindow::on_checkBox_68_clicked()
{
    setActivate(ui->checkBox_68->isChecked(),"RESTORE_DEVICE_STATE_ON_STARTUP");
}

void MainWindow::on_checkBox_70_clicked()
{
    setActivate(ui->checkBox_70->isChecked(),"DEVICES_TO_DISABLE_ON_STARTUP");
}

void MainWindow::on_checkBox_71_clicked()
{
    setActivate(ui->checkBox_71->isChecked(),"DEVICES_TO_ENABLE_ON_STARTUP");
}

void MainWindow::on_checkBox_72_clicked()
{
    setActivate(ui->checkBox_72->isChecked(),"DEVICES_TO_DISABLE_ON_SHUTDOWN");
}

void MainWindow::on_checkBox_73_clicked()
{
    setActivate(ui->checkBox_73->isChecked(),"DEVICES_TO_ENABLE_ON_SHUTDOWN");
}

void MainWindow::on_checkBox_75_clicked()
{
    setActivate(ui->checkBox_75->isChecked(),"DEVICES_TO_ENABLE_ON_AC");
}

void MainWindow::on_checkBox_76_clicked()
{
    setActivate(ui->checkBox_76->isChecked(),"DEVICES_TO_DISABLE_ON_BAT");
}

void MainWindow::on_checkBox_154_clicked()
{
    setActivate(ui->checkBox_154->isChecked(),"DEVICES_TO_DISABLE_ON_BAT_NOT_IN_USE");
}

void MainWindow::on_checkBox_155_clicked()
{
    setActivate(ui->checkBox_155->isChecked(),"DEVICES_TO_DISABLE_ON_LAN_CONNECT");
}

void MainWindow::on_checkBox_156_clicked()
{
    setActivate(ui->checkBox_156->isChecked(),"DEVICES_TO_DISABLE_ON_WIFI_CONNECT");
}

void MainWindow::on_checkBox_157_clicked()
{
    setActivate(ui->checkBox_157->isChecked(),"DEVICES_TO_DISABLE_ON_WWAN_CONNECT");
}

void MainWindow::on_checkBox_158_clicked()
{
    setActivate(ui->checkBox_158->isChecked(),"DEVICES_TO_ENABLE_ON_LAN_DISCONNECT");
}

void MainWindow::on_checkBox_241_clicked()
{
    setActivate(ui->checkBox_241->isChecked(),"DEVICES_TO_ENABLE_ON_WIFI_DISCONNECT");
}

void MainWindow::on_checkBox_242_clicked()
{
    setActivate(ui->checkBox_242->isChecked(),"DEVICES_TO_ENABLE_ON_WWAN_DISCONNECT");
}

void MainWindow::on_checkBox_243_clicked()
{
    setActivate(ui->checkBox_243->isChecked(),"DEVICES_TO_ENABLE_ON_DOCK");
}

void MainWindow::on_checkBox_329_clicked()
{
    setActivate(ui->checkBox_329->isChecked(),"DEVICES_TO_DISABLE_ON_DOCK");
}

void MainWindow::on_checkBox_331_clicked()
{
    setActivate(ui->checkBox_331->isChecked(),"DEVICES_TO_ENABLE_ON_UNDOCK");
}

void MainWindow::on_checkBox_330_clicked()
{
    setActivate(ui->checkBox_330->isChecked(),"DEVICES_TO_DISABLE_ON_UNDOCK");
}

void MainWindow::on_checkBox_69_clicked()
{
    setCheckBoxValue(ui->checkBox_69->isChecked(),"RESTORE_DEVICE_STATE_ON_STARTUP","1","0");
}

void MainWindow::on_checkBox_81_clicked()
{
    setActivate(ui->checkBox_81->isChecked(),"START_CHARGE_THRESH_BAT0");
}

void MainWindow::on_checkBox_82_clicked()
{
    setActivate(ui->checkBox_82->isChecked(),"STOP_CHARGE_THRESH_BAT0");
}

void MainWindow::on_checkBox_83_clicked()
{
    setActivate(ui->checkBox_83->isChecked(),"START_CHARGE_THRESH_BAT1");
}

void MainWindow::on_checkBox_84_clicked()
{
    setActivate(ui->checkBox_84->isChecked(),"STOP_CHARGE_THRESH_BAT1");
}

void MainWindow::on_checkBox_74_clicked()
{
    setCheckBoxValue(ui->checkBox_74->isChecked(),"DISK_IDLE_SECS_ON_AC","2","0");
}

void MainWindow::on_checkBox_80_clicked()
{
    setCheckBoxValue(ui->checkBox_80->isChecked(),"DISK_IDLE_SECS_ON_BAT","2","0");
}

void MainWindow::on_checkBox_clicked()
{
    setCheckBoxValue(ui->checkBox->isChecked(),"CPU_BOOST_ON_AC","1","0");
}

void MainWindow::on_checkBox_18_clicked()
{
    setCheckBoxValue(ui->checkBox_18->isChecked(),"CPU_BOOST_ON_BAT","1","0");
}

void MainWindow::on_checkBox_19_clicked()
{
    setCheckBoxValue(ui->checkBox_19->isChecked(),"SCHED_POWERSAVE_ON_AC","1","0");
}

void MainWindow::on_checkBox_20_clicked()
{
    setCheckBoxValue(ui->checkBox_20->isChecked(),"SCHED_POWERSAVE_ON_BAT","1","0");
}

void MainWindow::on_checkBox_21_clicked()
{
    setCheckBoxValue(ui->checkBox_21->isChecked(),"NMI_WATCHDOG","1","0");
}

void MainWindow::on_checkBox_54_clicked()
{
    setCheckBoxValue(ui->checkBox_54->isChecked(),"RUNTIME_PM_ON_AC","auto","on");
}

void MainWindow::on_checkBox_79_clicked()
{
    setCheckBoxValue(ui->checkBox_79->isChecked(),"RUNTIME_PM_ON_BAT","auto","on");
}

void MainWindow::on_checkBox_56_clicked()
{
    setCheckBoxValue(ui->checkBox_56->isChecked(),"RUNTIME_PM_ALL","1","0");
}

void MainWindow::on_checkBox_39_clicked()
{
    setCheckBoxValue(ui->checkBox_39->isChecked(),"WIFI_PWR_ON_AC","5","1");
}

void MainWindow::on_checkBox_41_clicked()
{
    setCheckBoxValue(ui->checkBox_41->isChecked(),"WIFI_PWR_ON_BAT","5","1");
}

void MainWindow::on_checkBox_43_clicked()
{
    setCheckBoxValue(ui->checkBox_43->isChecked(),"WOL_DISABLE","Y","N");
}

void MainWindow::on_checkBox_45_clicked()
{
    setCheckBoxValue(ui->checkBox_45->isChecked(),"SOUND_POWER_SAVE_ON_AC","1","0");
}

void MainWindow::on_checkBox_47_clicked()
{
    setCheckBoxValue(ui->checkBox_47->isChecked(),"SOUND_POWER_SAVE_ON_BAT","1","0");
}

void MainWindow::on_checkBox_49_clicked()
{
    setCheckBoxValue(ui->checkBox_49->isChecked(),"SOUND_POWER_SAVE_CONTROLLER","Y","N");
}

void MainWindow::on_checkBox_51_clicked()
{
    setCheckBoxValue(ui->checkBox_51->isChecked(),"BAY_POWEROFF_ON_BAT","1","0");
}

void MainWindow::on_checkBox_60_clicked()
{
    setCheckBoxValue(ui->checkBox_60->isChecked(),"USB_AUTOSUSPEND","1","0");
}

void MainWindow::on_checkBox_64_clicked()
{
    setCheckBoxValue(ui->checkBox_64->isChecked(),"USB_BLACKLIST_WWAN","1","0");
}

void MainWindow::on_checkBox_66_clicked()
{
    setCheckBoxValue(ui->checkBox_66->isChecked(),"USB_AUTOSUSPEND_DISABLE_ON_SHUTDOWN","1","0");
}

void MainWindow::on_spinBox_9_editingFinished()
{
    values["MAX_LOST_WORK_SECS_ON_AC"]=QString::number(ui->spinBox_9->value());
}

void MainWindow::on_spinBox_10_editingFinished()
{
    values["MAX_LOST_WORK_SECS_ON_BAT"]=QString::number(ui->spinBox_10->value());
}

void MainWindow::on_spinBox_editingFinished()
{
    values["CPU_SCALING_MIN_FREQ_ON_AC"]=QString::number(ui->spinBox->value());
}

void MainWindow::on_spinBox_2_editingFinished()
{
    values["CPU_SCALING_MAX_FREQ_ON_AC"]=QString::number(ui->spinBox_2->value());
}

void MainWindow::on_spinBox_3_editingFinished()
{
    values["CPU_SCALING_MIN_FREQ_ON_BAT"]=QString::number(ui->spinBox_3->value());
}

void MainWindow::on_spinBox_4_editingFinished()
{
    values["CPU_SCALING_MAX_FREQ_ON_BAT"]=QString::number(ui->spinBox_4->value());
}

void MainWindow::on_spinBox_5_editingFinished()
{
    values["CPU_MIN_PERF_ON_AC"]=QString::number(ui->spinBox_5->value());
}

void MainWindow::on_spinBox_6_editingFinished()
{
    values["CPU_MAX_PERF_ON_AC"]=QString::number(ui->spinBox_6->value());
}

void MainWindow::on_spinBox_8_editingFinished()
{
    values["CPU_MIN_PERF_ON_BAT"]=QString::number(ui->spinBox_8->value());
}

void MainWindow::on_spinBox_7_editingFinished()
{
    values["CPU_MAX_PERF_ON_BAT"]=QString::number(ui->spinBox_7->value());
}

void MainWindow::on_lineEdit_editingFinished()
{
    values["PHC_CONTROLS"]=ui->lineEdit->text();
}

void MainWindow::on_lineEdit_2_editingFinished()
{
    values["RUNTIME_PM_BLACKLIST"]=ui->lineEdit_2->text();
}

void MainWindow::on_lineEdit_3_editingFinished()
{
    values["RUNTIME_PM_DRIVER_BLACKLIST"]=ui->lineEdit_3->text();
}

void MainWindow::on_lineEdit_4_editingFinished()
{
    values["USB_BLACKLIST"]=ui->lineEdit_4->text();
}

void MainWindow::on_lineEdit_5_editingFinished()
{
    values["USB_WHITELIST"]=ui->lineEdit_5->text();
}

void MainWindow::on_lineEdit_6_editingFinished()
{
    values["DEVICES_TO_DISABLE_ON_STARTUP"]=ui->lineEdit_6->text();
}

void MainWindow::on_lineEdit_7_editingFinished()
{
    values["DEVICES_TO_ENABLE_ON_STARTUP"]=ui->lineEdit_7->text();
}

void MainWindow::on_lineEdit_8_editingFinished()
{
    values["DEVICES_TO_DISABLE_ON_SHUTDOWN"]=ui->lineEdit_8->text();
}

void MainWindow::on_lineEdit_9_editingFinished()
{
    values["DEVICES_TO_ENABLE_ON_SHUTDOWN"]=ui->lineEdit_9->text();
}

void MainWindow::on_lineEdit_11_editingFinished()
{
    values["DEVICES_TO_ENABLE_ON_AC"]=ui->lineEdit_11->text();
}

void MainWindow::on_lineEdit_12_editingFinished()
{
    values["DEVICES_TO_DISABLE_ON_BAT"]=ui->lineEdit_12->text();
}

void MainWindow::on_lineEdit_25_editingFinished()
{
    values["DEVICES_TO_DISABLE_ON_BAT_NOT_IN_USE"]=ui->lineEdit_25->text();
}

void MainWindow::on_lineEdit_26_editingFinished()
{
    values["DEVICES_TO_DISABLE_ON_LAN_CONNECT"]=ui->lineEdit_26->text();
}

void MainWindow::on_lineEdit_27_editingFinished()
{
    values["DEVICES_TO_DISABLE_ON_WIFI_CONNECT"]=ui->lineEdit_27->text();
}

void MainWindow::on_lineEdit_28_editingFinished()
{
    values["DEVICES_TO_DISABLE_ON_WWAN_CONNECT"]=ui->lineEdit_28->text();
}

void MainWindow::on_lineEdit_29_editingFinished()
{
    values["DEVICES_TO_ENABLE_ON_LAN_DISCONNECT"]=ui->lineEdit_29->text();
}

void MainWindow::on_lineEdit_47_editingFinished()
{
    values["DEVICES_TO_ENABLE_ON_WIFI_DISCONNECT"]=ui->lineEdit_47->text();
}

void MainWindow::on_lineEdit_48_editingFinished()
{
    values["DEVICES_TO_ENABLE_ON_WWAN_DISCONNECT"]=ui->lineEdit_48->text();
}

void MainWindow::on_lineEdit_49_editingFinished()
{
    values["DEVICES_TO_ENABLE_ON_DOCK"]=ui->lineEdit_49->text();
}

void MainWindow::on_lineEdit_70_editingFinished()
{
    values["DEVICES_TO_DISABLE_ON_DOCK"]=ui->lineEdit_70->text();
}

void MainWindow::on_lineEdit_72_editingFinished()
{
    values["DEVICES_TO_ENABLE_ON_UNDOCK"]=ui->lineEdit_72->text();
}

void MainWindow::on_lineEdit_71_editingFinished()
{
    values["DEVICES_TO_DISABLE_ON_UNDOCK"]=ui->lineEdit_71->text();
}

void MainWindow::on_spinBox_11_editingFinished()
{
    values["START_CHARGE_THRESH_BAT0"]=QString::number(ui->spinBox_11->value());
}

void MainWindow::on_spinBox_12_editingFinished()
{
    values["STOP_CHARGE_THRESH_BAT0"]=QString::number(ui->spinBox_12->value());
}

void MainWindow::on_spinBox_13_editingFinished()
{
    values["START_CHARGE_THRESH_BAT1"]=QString::number(ui->spinBox_13->value());
}

void MainWindow::on_spinBox_14_editingFinished()
{
    values["STOP_CHARGE_THRESH_BAT1"]=QString::number(ui->spinBox_13->value());
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    values["CPU_SCALING_GOVERNOR_ON_AC"]=arg1;
}

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    values["CPU_SCALING_GOVERNOR_ON_BAT"]=arg1;
}

void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    values["ENERGY_PERF_POLICY_ON_AC"]=arg1;
}

void MainWindow::on_comboBox_4_currentIndexChanged(const QString &arg1)
{
    values["ENERGY_PERF_POLICY_ON_BAT"]=arg1;
}

void MainWindow::on_comboBox_6_editTextChanged(const QString &arg1)
{
    values["DISK_DEVICES"]=arg1;
}

void MainWindow::on_comboBox_7_editTextChanged(const QString &arg1)
{
    values["DISK_APM_LEVEL_ON_AC"]=arg1;
}

void MainWindow::on_comboBox_8_editTextChanged(const QString &arg1)
{
    values["DISK_APM_LEVEL_ON_BAT"]=arg1;
}

void MainWindow::on_comboBox_9_editTextChanged(const QString &arg1)
{
    values["DISK_SPINDOWN_TIMEOUT_ON_AC"]=arg1;
}

void MainWindow::on_comboBox_10_editTextChanged(const QString &arg1)
{
    values["DISK_SPINDOWN_TIMEOUT_ON_BAT"]=arg1;
}

void MainWindow::on_comboBox_5_currentIndexChanged(const QString &arg1)
{
    values["DISK_IOSCHED"]=arg1;
}

void MainWindow::on_comboBox_11_currentIndexChanged(const QString &arg1)
{
    values["SATA_LINKPWR_ON_AC"]=arg1;
}

void MainWindow::on_comboBox_12_currentIndexChanged(const QString &arg1)
{
    values["SATA_LINKPWR_ON_BAT"]=arg1;
}

void MainWindow::on_comboBox_13_currentIndexChanged(const QString &arg1)
{
    values["PCIE_ASPM_ON_AC"]=arg1;
}

void MainWindow::on_comboBox_14_currentIndexChanged(const QString &arg1)
{
    values["PCIE_ASPM_ON_BAT"]=arg1;
}

void MainWindow::on_comboBox_15_currentIndexChanged(const QString &arg1)
{
    values["RADEON_POWER_PROFILE_ON_AC"]=arg1;
}

void MainWindow::on_comboBox_16_currentIndexChanged(const QString &arg1)
{
    values["RADEON_POWER_PROFILE_ON_BAT"]=arg1;
}

void MainWindow::on_comboBox_17_currentIndexChanged(const QString &arg1)
{
    values["RADEON_DPM_STATE_ON_AC"]=arg1;
}

void MainWindow::on_comboBox_18_currentIndexChanged(const QString &arg1)
{
    values["RADEON_DPM_STATE_ON_BAT"]=arg1;
}

void MainWindow::on_comboBox_19_currentIndexChanged(const QString &arg1)
{
    values["RADEON_DPM_PERF_LEVEL_ON_AC"]=arg1;
}

void MainWindow::on_comboBox_20_currentIndexChanged(const QString &arg1)
{
    values["RADEON_DPM_PERF_LEVEL_ON_BAT"]=arg1;
}

void MainWindow::on_comboBox_21_editTextChanged(const QString &arg1)
{
    values["BAY_DEVICE"]=arg1;
}

void MainWindow::on_comboBox_22_editTextChanged(const QString &arg1)
{
    values["USB_DRIVER_BLACKLIST"]=arg1;
}

void MainWindow::on_actionAbout_triggered()
{
    ab.exec();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}
