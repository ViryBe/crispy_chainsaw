#include "newplane.h"
#include "ui_newplane.h"

newPlane::newPlane( QWidget* parent )
    : QDialog( parent ), ui( new Ui::newPlane )
{
    ui->setupUi( this );
}

newPlane::~newPlane() { delete ui; }

void newPlane::on_buttonBox_accepted()
{
    QString immat = ui->codePlaneEdit->text();
    QString function;
    qDebug( immat.toLatin1() );     // ok
    if ( ui->B727->isChecked() ) {
        function = "B727";
    } else {
        function = "B737";
    }
    qDebug( function.toLatin1() );     // ok
    // add in bdd (id, name, function)
    // refresh list. Le tri par nom est effectué de façon automatique
    // open new Plane added
    close();
}

void newPlane::updateInformation(
    const QString& idPlane, const QString& function )
{
    ui->codePlaneEdit->setText( idPlane );
    if ( function == "B737" ) {
        ui->B737->setChecked( true );
    } else
        ui->B727->setChecked( true );
}

void newPlane::on_buttonBox_rejected() { close(); }
