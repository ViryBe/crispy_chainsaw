#include "newpilot.h"
#include "ui_newpilot.h"

newPilot::newPilot( QWidget* parent )
    : QDialog( parent ), ui( new Ui::newPilot )
{
    ui->setupUi( this );
}

newPilot::~newPilot() { delete ui; }

void newPilot::on_buttonBox_accepted()
{
    QString code = "", name = "", role = "", acftmodel = "";
    code = ui->codePilotEdit->text();
    name = ui->namePilotEdit->text();
    int frequence = 0;
    if ( ui->B727Cdt->isChecked() ) {
        acftmodel = "b727";
        role = "cpt";
    } else if ( ui->B737Cdt->isChecked() ) {
        acftmodel = "b737";
        role = "cpt";
    } else if ( ui->B727FE->isChecked() ) {
        acftmodel = "b727";
        role = "fe";
    } else if ( ui->B727FO->isChecked() ) {
        acftmodel = "b727";
        role = "fo";
    } else if ( ui->B737FO->isChecked() ) {
        acftmodel = "b737";
        role = "fo";;
    }
    frequence = ui->frequenceSpin->value();

    Pnt pnt = Pnt(code, name, role, acftmodel);

    // add in bdd (id, name, function)
    // refresh list. Le tri par nom est effectué de façon automatique
    // open new pilot added
}

void newPilot::updateInformation( const QString& idPilote,
    const QString& namePilot, const QString& acft, const QString& role, const int frequence )
{
    ui->codePilotEdit->setText( idPilote );
    ui->namePilotEdit->setText( namePilot );
    ui->frequenceSpin->setValue( frequence );
    if (acft == "b727"){
        if (role == "cpt")
            ui->B727Cdt->setChecked(true);
        else if (role == "fo")
            ui->B727FO->setChecked(true);
        else
            ui->B727FE->setChecked(true);
    }
    else if (role == "cpt")
        ui->B737Cdt->setChecked(true);
    else
        ui->B737FO->setChecked(true);

}
