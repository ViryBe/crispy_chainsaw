#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newpilot.h"
#include "newplane.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //TODO : add the list of pilots in pilotList
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pilotAdd_clicked()
{
    newPilot NewPilot;
    NewPilot.setModal(true);
    NewPilot.exec();
}


void MainWindow::on_pilotList_currentTextChanged(const QString &currentText)
{
    qDebug(currentText.toLatin1()); //ok
    //faire la requete dans la bdd avec idPilote = currentText
    //remplir les champs correspondant dans la 2eme fenetre
}


void MainWindow::on_refreshButton_clicked()
{
    QDate dateFrom = ui->dateFrom->date();
    QDate dateTo = ui->dateTo->date();
    //TODO : calculer nb jours repos, vol, ...
    QString flightDays, homeDays, standByDays, officeDays;
    ui->flightDays->setText(flightDays);
    ui->homeDays->setText(homeDays);
    ui->standByDays->setText(standByDays);
    ui->officeDays->setText(officeDays);

}

void MainWindow::on_pilotManage_clicked()
{
    QString idPilot = ui->pilotList->currentItem()->text();
    //TODO : Chercher dans la base de données les infos pilotes pour les mettre dans namePilot et function
    QString namePilot = "toto";
    QString function = "B727FE";
    int frequence = 6;
    qDebug(idPilot.toLatin1()); //ok

    // Création de la nouvelle boite de dialogue pour modifier les infos
    newPilot NewPilot;
    NewPilot.setModal(true);
    NewPilot.updateInformation(idPilot,namePilot, function, frequence);
    NewPilot.exec();
}

void MainWindow::on_planeManage_clicked()
{
    QString idPlane = ui->planeList->currentItem()->text();
    //TODO : Chercher dans la base de données les infos pilotes pour les mettre dans namePilot et function
    QString function = "B727";
    qDebug(idPlane.toLatin1()); //ok

    // Création de la nouvelle boite de dialogue pour modifier les infos
    newPlane NewPlane;
    NewPlane.setModal(true);
    NewPlane.updateInformation(idPlane, function);
    NewPlane.exec();
}

void MainWindow::on_planeAdd_clicked()
{
    // Création de la nouvelle boite de dialogue pour modifier les infos
    newPlane NewPlane;
    NewPlane.setModal(true);
    NewPlane.exec();
}
