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
        QString see_status(const QDate, const QString);
        int getFlightTimePilot(const QString, int);

        // Get PNTs according to diverse criteria
        std::vector<QString> getAvailablePnts(const QDate& day,
                                              const QString& role,
                                              const QString& model);
        std::vector<QString> getPnts(const QString& acft_model);
        std::vector<QString> getPnts(const QString& acft_model,
                                     const QString& role);
        bool test();

    private:
        QSqlDatabase m_db;
};

static DbManager _MANAGER = DbManager("");
#endif
