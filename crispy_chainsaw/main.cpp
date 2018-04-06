#include "db.h"
#include "mainwindow.h"
#include "schedule.h"
#include <QApplication>
#include <QDebug>
#include <QMainWindow>

DbManager _MANAGER{};


int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    const QString path = QCoreApplication::applicationDirPath() + "/dummy.db";
    _MANAGER.init( path );

    ScheduleInstance::test();
    MainWindow w;
    w.show();

    return a.exec();
}
