#include "modifyflight.h"
#include "ui_modifyflight.h"

ModifyFlight::ModifyFlight(QDate dateSend, QString plane, QWidget *parent) :
    QDialog(parent), ui(new Ui::ModifyFlight), appareil(plane)
{
    QTime time(2,30);
    ui->setupUi(this);
    ui->dateEdit->setDate(dateSend);
    ui->time->setTime(time);
}

ModifyFlight::~ModifyFlight()
{
    delete ui;
}
