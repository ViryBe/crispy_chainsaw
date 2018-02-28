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

void newPilot::on_buttonBox_accepted()
{
    QString code = ui -> codePilotEdit -> text();
    code.toStdString();
    QString name = ui -> namePilotEdit -> text();
    name.toStdString();
    QString function;
    qDebug(code.toLatin1() +"\n" +name.toLatin1()); //ok
    if (ui->B727Cdt->isChecked()){
        function = "B727Cdt";
    }
    else if (ui->B737Cdt->isChecked()){
        function = "B737Cdt";
    }
    else if (ui->B727FE->isChecked()){
        function = "B72FE";
    }
    else if (ui->B727FO->isChecked()){
        function = "B72FO";
    }
    else if (ui->B737FO->isChecked()){
        function = "B73FO";
    }
    qDebug(function.toLatin1());

}
