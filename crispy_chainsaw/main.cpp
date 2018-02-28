#include "mainwindow.h"
#include "db.h"
#include <QApplication>
#include <QDebug>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    /*
    QDir qdir = QDir(""); //Current path
    qdir.cdUp();
    qDebug() << qdir.currentPath();
    if (qdir.cd(qdir.currentPath() + "/dummydata")) {
        QString fpath = qdir.currentPath() + "dummy.db";
        DbManager db = DbManager(fpath);
        qDebug() << (db.test() ?
                         "database tested succesfully" :
                         "database testing failure");
    }
    else {
        qDebug() << "database not tested, file path resolution failure";
    }
    */
    QString fpath = "/home/gabriel/workspace/vcs/"
            "crispy_chainsaw/dummydata/dummy.db";
    DbManager db = DbManager(fpath);
    qDebug() << (db.test() ?
                     "database tested succesfully" :
                     "database testing failure");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
