#include "mainwindow.h"
#include "db.h"
#include <QApplication>
#include <QDebug>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    DbManager db = DbManager("/home/gabriel/workspace/vcs/crispy_chainsaw/dummydata/dummy.db");
    db.test();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
