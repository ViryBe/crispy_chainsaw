#include "mainwindow.h"
#include "db.h"
#include <QApplication>
#include <QDebug>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    DbManager::test();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
