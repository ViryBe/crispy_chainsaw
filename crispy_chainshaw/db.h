#ifndef DB_H
#define DB_H

#include <QtSql>
#include <QString>
#include <iostream>

/// Type used to describe the day of a pilot
enum class WorkDayStatus {OFF, STANDBY, OFFICE, V1, V2, V3};

/// Converts a string to a WorkDayStatus
WorkDayStatus str2wds(const QString&);

/// Converts a WorkDayStatus to a string
QString wds2str(const WorkDayStatus&);

/// Interacts with the database
class DbManager
{
    public:
        DbManager(const QString&);
        void add_pilot(const QString&, const QString&, const int);
        void add_acft_model(const QString&, int, int, int);
        void add_workday(const QString&, const WorkDayStatus&);
        WorkDayStatus see_status(QDateTime, QString);
        int getFlightTimePilot(QString, int);
    private:
        QSqlDatabase m_db;
};

static DbManager _MANAGER = DbManager("");

#endif
