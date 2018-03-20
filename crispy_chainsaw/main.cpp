#include "mainwindow.h"
#include "schedule.h"
#include "db.h"
#include <QApplication>
#include <QDebug>
#include <QMainWindow>

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );
    MainWindow w;
    w.show();

    return a.exec();
}
