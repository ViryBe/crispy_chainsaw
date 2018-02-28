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

void MainWindow::on_pilotManage_clicked()
{
    newPilot NewPilot;
    NewPilot.setModal(true);
    NewPilot.exec();
    //remplir les données de la nouvelle fenêtre avec les éléments existants et permettre la modification
}
