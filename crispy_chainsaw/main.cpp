#include "db.h"
#include "mainwindow.h"
#include "schedule.h"
#include <QApplication>
#include <QDebug>
#include <QMainWindow>

DbManager* _MANAGER;

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );
    QString path = QCoreApplication::applicationDirPath() + "/dummy.db";
    qDebug() << path;
    _MANAGER = new DbManager( path );
    MainWindow w;
    w.show();
    delete _MANAGER;
    return a.exec();
}
