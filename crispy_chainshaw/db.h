#ifndef DB_H
#define DB_H

#include <QtSql>
#include <QString>
#include <iostream>

/// Interacts with the database
class DbManager
{
    public:
        DbManager(const QString&);
        void add_pilot(const QString&, const QString&, const int);
        void add_workday(const QString&, const QString&);
        QString see_status(QDate, QString);
        int getFlightTimePilot(QString, int);

    private:
        QSqlDatabase m_db;
};

static DbManager _MANAGER = DbManager("");
#endif
