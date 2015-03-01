#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadMarkedLines();
    readConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    <<"DEVICES_TO_ENABLE_ON_UNDOCK"<<"DEVICES_TO_DISABLE_ON_UNDOCK";

    for (int i = 0; i < markedLines.size(); ++i) {
        values.insert(markedLines.at(i),"");
        valueActive.insert(markedLines.at(i),false);
        //qDebug()<<markedLines.at(i);
    }
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
        for (int i = 0; i < markedLines.size(); ++i) {
            QString word = markedLines.at(i);
            bool isThere = line.contains(word);
            if (isThere) {
                if (line.at(0)!='#')
                    valueActive[word]=true;
            }

        }
    }
}

void MainWindow::setActivate(bool b, QString value)
{
    if (b)
        values[value]="1";
    else
        values[value]="0";

}



void MainWindow::on_cb_tlp_active_clicked()
{
    setActivate(ui->cb_tlp_active->isChecked(),"TLP_ENABLE");
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (ui->checkBox->isChecked()) {
        values["CPU_SCALING_GOVERNOR_ON_AC"]=arg1;
    }
}

void MainWindow::on_checkBox_clicked()
{
    setActivate(ui->checkBox->isChecked(),"CPU_SCALING_GOVERNOR_ON_AC");
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
