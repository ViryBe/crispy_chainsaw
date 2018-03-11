#include "mainwindow.h"


MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent ), ui( new Ui::MainWindow )
{
    ui->setupUi( this );
    ui->pilotList->clear();
    auto pntsIds = _MANAGER.getPnts();
    for (auto id:pntsIds){
        ui->pilotList->addItem(id);
    }
    ui->pilotList->setCurrentRow(0);
    auto idPilot = ui->pilotList->currentItem()->text();
    refresh_pilot_information(idPilot);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pilotAdd_clicked()
{
    newPilot NewPilot;
    NewPilot.setModal( true );
    NewPilot.exec();
}


void MainWindow::on_pilotList_currentTextChanged( const QString& currentText )
{
    qDebug( currentText.toLatin1() );     // ok
    refresh_pilot_information(currentText);
}


void MainWindow::on_refreshButton_clicked()
{
    QDate dateFrom = ui->dateFrom->date();
    QDate dateTo = ui->dateTo->date();
    // TODO : calculer nb jours repos, vol, ...
    QString flightDays, homeDays, standByDays, officeDays;
    ui->flightDays->setText( flightDays );
    ui->homeDays->setText( homeDays );
    ui->standByDays->setText( standByDays );
    ui->officeDays->setText( officeDays );
}

void MainWindow::on_pilotManage_clicked()
{
    QString idPilot = ui->pilotList->currentItem()->text();
    auto pilotInfo = _MANAGER.getPnt(idPilot);
    QString namePilot = "toto";
    QString function = pilotInfo.role;
    int frequence = pilotInfo.freq_max;
    qDebug( idPilot.toLatin1() );     // ok

    // Création de la nouvelle boite de dialogue pour modifier les infos
    newPilot NewPilot;
    NewPilot.setModal( true );
    NewPilot.updateInformation( idPilot, namePilot, function, frequence );
    NewPilot.exec();
}

void MainWindow::on_planeManage_clicked()
{
    QString idPlane = ui->planeList->currentItem()->text();
    // TODO : Chercher dans la base de données les infos pilotes pour les mettre
    // dans namePilot et function
    QString function = "B727";
    qDebug( idPlane.toLatin1() );     // ok

    // Création de la nouvelle boite de dialogue pour modifier les infos
    newPlane NewPlane;
    NewPlane.setModal( true );
    NewPlane.updateInformation( idPlane, function );
    NewPlane.exec();
}

void MainWindow::on_planeAdd_clicked()
{
    // Création de la nouvelle boite de dialogue pour modifier les infos
    newPlane NewPlane;
    NewPlane.setModal( true );
    NewPlane.exec();
}


void MainWindow::on_validerB737_clicked()
{
    QDate dateFrom = ui->dateFromB737->date();
    QDate dateTo = ui->dateToB737->date();
}

void MainWindow::refresh_pilot_days(QDate dateFrom, QDate dateTo)
{
    //refresh the days of work of the pilot
}

void MainWindow::refresh_pilot_information(const QString& idPilot)
{
 auto pilotInfo = _MANAGER.getPnt(idPilot);
 ui->codePilotBDD->setText(pilotInfo.id);
 //set the date from today to + 15 days
 QDate date = date.currentDate();
 ui->dateFrom->setDate(date);
 ui->dateTo->setDate(date.addDays(15));
 refresh_pilot_days(date, date.addDays(15));
 ui->limitationVol->setValue(pilotInfo.freq_max);
 qDebug() << pilotInfo.role << pilotInfo.acft_modelname;
}

void MainWindow::on_dateFrom_userDateChanged(const QDate &date)
{
    ui->dateTo->setDate(date.addDays(15));
}
