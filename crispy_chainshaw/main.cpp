#include "mainwindow.h"
#include "db.h"
#include <QApplication>
#include <QDebug>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    DbManager db = DbManager("C:/Users/clrco/Documents/Projets/crispy_chainsaw/dummydata/dummy.db");
    qDebug() << (db.test() ? "database tested succesfully" : "database testing failure");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
