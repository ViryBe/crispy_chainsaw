#include "modifyflight.h"
#include "ui_modifyflight.h"

ModifyFlight::ModifyFlight(QDate dateSend, QString plane, QWidget *parent) :
    QDialog(parent), ui(new Ui::ModifyFlight), appareil(plane)
{

    date = dateSend;
    ui->setupUi(this);
    std::vector<WorkdayDb> wdb = gMANAGER.getWorkdays(appareil, date, ui->vol->currentText());
    qDebug() << wdb[0].lapse;
    QTime time = (wdb.size() >0)? QTime(wdb[0].lapse) : QTime(2,30);
    ui->dateEdit->setDate(dateSend);
    ui->time->setTime(time);
    if (dateSend.currentDate() > dateSend){
        ui->time->setEnabled(false);
        ui->vol->setEnabled(false);
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
        ui->vol->setEnabled(false);
        ui->time->setEnabled(false);
    }
    else {
        ui->vol->setEnabled(true);
        ui->time->setEnabled(true);
    }
}

void ModifyFlight::on_dateEdit_userDateChanged(const QDate &date)
{
    std::vector<WorkdayDb> wdb = gMANAGER.getWorkdays(appareil, date, ui->vol->currentText());
    QTime time = (wdb.size() >0)? QTime(wdb[0].lapse) : QTime(2,30);
    ui->time->setTime(time);
    if (date > date.currentDate()){
        ui->time->setEnabled(false);
        ui->vol->setEnabled(false);
        ui->pasEffectue->setChecked(true);
        ui->pasEffectue->setEnabled(false);
    }
    else {
        ui->vol->setEnabled(true);
        ui->time->setEnabled(true);
        ui->pasEffectue->setChecked(false);
        ui->pasEffectue->setEnabled(true);
    }
}

void ModifyFlight::on_buttonBox_accepted()
{
    auto date = ui->dateEdit->date();
    auto vol = ui->vol->currentText();
    auto time = ui->time->time();
    gMANAGER.editFlightLapse(date, appareil, vol, time);
}
