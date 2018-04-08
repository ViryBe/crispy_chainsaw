#include "db.h"
#include "mainwindow.h"
#include "schedule.h"
#include <QApplication>
#include <QDebug>
#include <QMainWindow>

DbManager gMANAGER{};


int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    const QString path = QCoreApplication::applicationDirPath() + "/dummy.db";
    gMANAGER.init( path );

    ScheduleInstance::test();
    gMANAGER.createScheduleView( "testview", QDate(2018, 10, 10),
                                 QDate( 2018, 10, 12 ));
    MainWindow w;
    w.show();

    return a.exec();
}
