#include "modifyflight.h"
#include "ui_modifyflight.h"

ModifyFlight::ModifyFlight(QDate dateSend, QString plane, QWidget *parent) :
    QDialog(parent), ui(new Ui::ModifyFlight), appareil(plane)
{
    QTime time(2,30);
    ui->setupUi(this);
    ui->dateEdit->setDate(dateSend);
    ui->time->setTime(time);
    if (dateSend.currentDate() > dateSend){
        ui->time->setEnabled(false);
        ui->vol->setEnabled(false);
        ui->time->setEnabled(false);
        ui->pasEffectue->setChecked(true);
    }
}

ModifyFlight::~ModifyFlight()
{
    delete ui;
}


void ModifyFlight::on_pasEffectue_stateChanged(int arg1)
{
    if (ui->pasEffectue->isChecked()){
        ui->time->setEnabled(false);
        ui->vol->setEnabled(false);
        ui->time->setEnabled(false);
    }
    else {
        ui->time->setEnabled(true);
        ui->vol->setEnabled(true);
        ui->time->setEnabled(true);
    }
}

void ModifyFlight::on_dateEdit_userDateChanged(const QDate &date)
{
    if (date > date.currentDate()){
        ui->time->setEnabled(false);
        ui->vol->setEnabled(false);
        ui->time->setEnabled(false);
        ui->pasEffectue->setChecked(true);
        ui->pasEffectue->setEnabled(false);
    }
    else {
        ui->time->setEnabled(true);
        ui->vol->setEnabled(true);
        ui->time->setEnabled(true);
        ui->pasEffectue->setChecked(false);
        ui->pasEffectue->setEnabled(true);
    }
}
