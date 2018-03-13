#include "mainwindow.h"


MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent ), ui( new Ui::MainWindow )
{
    ui->setupUi( this );
    ui->pilotList->clear();
    refresh_pilot_list();
    ui->pilotList->setCurrentRow(0);
    auto idPilot = ui->pilotList->currentItem()->text();
    refresh_pilot_information(idPilot.toLower());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::refresh_pilot_list()
{
    auto pntsIds = _MANAGER.getPnts();
    for (auto id:pntsIds){
        ui->pilotList->addItem(id.toUpper());
    }
}

void MainWindow::on_pilotAdd_clicked()
{
    newPilot NewPilot;
    NewPilot.setModal( true );
    NewPilot.exec();
    refresh_pilot_list();
}


void MainWindow::on_pilotList_currentTextChanged( const QString& currentText )
{
    refresh_pilot_information(currentText.toLower());
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
    auto pilotInfo = _MANAGER.getPnt(idPilot.toLower());
    QString namePilot = pilotInfo.name;
    QString role = pilotInfo.role;
    QString acft = pilotInfo.acft_modelname;
    int frequence = pilotInfo.maxfreq;

    // Création de la nouvelle boite de dialogue pour modifier les infos
    newPilot NewPilot;
    NewPilot.setModal( true );
    NewPilot.updateInformation( idPilot, namePilot, acft, role, frequence );
    NewPilot.exec();

    refresh_pilot_information(idPilot);
}

void MainWindow::on_planeManage_clicked()
{
    QString idPlane, namePlane;
    newPlane NewPlane;
    NewPlane.setModal( true );
    NewPlane.updateInformation(idPlane, namePlane);
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
 ui->pilotNameBDD->setText(pilotInfo.name);
 //set the date from today to + 15 days
 QDate date = date.currentDate();
 ui->dateFrom->setDate(date);
 ui->dateTo->setDate(date.addDays(15));
 refresh_pilot_days(date, date.addDays(15));
 ui->limitationVol->setValue(pilotInfo.maxfreq);
 if (pilotInfo.acft_modelname == "b727"){
     if (pilotInfo.role == "cpt")
         ui->B727Cdt->setChecked(true);
     else if (pilotInfo.role == "fo")
         ui->B727FO->setChecked(true);
     else
         ui->B727FE->setChecked(true);
 }
 else if (pilotInfo.role == "cpt")
     ui->B737Cdt->setChecked(true);
 else
     ui->B737FO->setChecked(true);
 qDebug() << pilotInfo.role << pilotInfo.acft_modelname;
}

void MainWindow::change_pilot_function()
{

}

void MainWindow::on_dateFrom_userDateChanged(const QDate &date)
{
    ui->dateTo->setDate(date.addDays(15));
}

void MainWindow::on_pilotDelete_clicked()
{

}
