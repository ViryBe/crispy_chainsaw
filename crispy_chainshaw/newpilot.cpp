#include "newpilot.h"
#include "ui_newpilot.h"

newPilot::newPilot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newPilot)
{
    ui->setupUi(this);
}

newPilot::~newPilot()
{
    delete ui;
}
