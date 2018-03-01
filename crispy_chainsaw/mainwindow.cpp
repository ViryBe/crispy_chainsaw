#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newpilot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_pilotSee_clicked()
{
    QString idPilot = ui->pilotList->currentItem()->text();
    //TODO : Chercher dans la base de données les infos pilotes pour les mettre dans namePilot et function
    QString namePilot = "toto";
    QString function = "B727FE";
    qDebug(idPilot.toLatin1()); //ok

    // Création de la nouvelle boite de dialogue pour modifier les infos
    newPilot NewPilot;
    NewPilot.setModal(true);
    NewPilot.updateInformation(idPilot,namePilot, function);
    NewPilot.exec();
}
