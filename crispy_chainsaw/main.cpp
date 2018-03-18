#include "mainwindow.h"
#include "schedule.h"
#include "db.h"
#include <QApplication>
#include <QDebug>
#include <QMainWindow>

int main( int argc, char* argv[] )
{
    ScheduleInstance::test();
    QApplication a(argc, argv);
    return true;
}
