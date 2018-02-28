#ifndef DB_H
#define DB_H

#include <QtSql>
#include <QString>
#include <iostream>

/** Manages all inputs and outputs with the database. The SQL schema is not
 * given anywhere, although it would be a good idea. */
class DbManager
{
public:
    /** Creates a dbmanager managing an sqlite file
     * @param s sqlite filepath */
    DbManager(const QString& s);
    void add_pilot(const QString&, const QString&, const int);
    void add_workday(const QString&, const QString&);
    QString see_status(const QDate, const QString);
    int getFlightTimePilot(const QString, int);

    // Get PNTs according to diverse criteria
    std::vector<QString> getAvailablePnts(const QDate& day,
                                          const QString& role,
                                          const QString& model);
    /** Retreives all pnts able to be in the crew of a specified aircraft
     * @param m model of aircraft
     * @returns pnt ids */
    std::vector<QString> getPnts(const QString& m);
    /** Retrieves people of role [r] able to manage model [m]
         * @param m model of aircraft
         * @param r role asked (captain, first officer of flight engineer)
         * @returns pnt ids */
    std::vector<QString> getPnts(const QString& m, const QString& r);

    /** A test function using see_status
         * @returns true if tests succeed */
    bool test();

private:
    QSqlDatabase m_db;

    /** Adds a workday in database for pnt of id [i], with status [s], on
     * date [d] */
    void addWorkday(const QString i, const QString s, const QString d);
};

/** Main manager for all the program */
static DbManager _MANAGER = DbManager("");
#endif
