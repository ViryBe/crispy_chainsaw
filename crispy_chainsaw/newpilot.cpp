#include "newpilot.h"
#include "ui_newpilot.h"
#include "db.h"

newPilot::newPilot( QWidget* parent )
    : QDialog( parent ), ui( new Ui::newPilot )
{
    ui->setupUi( this );
}

newPilot::~newPilot() { delete ui; }

void newPilot::on_buttonBox_accepted()
{
    QString code = ui->codePilotEdit->text();
    code.toStdString();
    QString name = ui->namePilotEdit->text();
    name.toStdString();
    QString function;
    int frequence = 0;
    qDebug( code.toLatin1() + "\n" + name.toLatin1() );     // ok
    if ( ui->B727Cdt->isChecked() ) {
        function = "B727Cdt";
    } else if ( ui->B737Cdt->isChecked() ) {
        function = "B737Cdt";
    } else if ( ui->B727FE->isChecked() ) {
        function = "B727FE";
    } else if ( ui->B727FO->isChecked() ) {
        function = "B727FO";
    } else if ( ui->B737FO->isChecked() ) {
        function = "B737FO";
    }
    frequence = ui->frequenceSpin->value();

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
