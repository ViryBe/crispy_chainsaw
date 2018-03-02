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
    /** Creates a dbmanager managing a sqlite file
     * @param s sqlite filepath */
    DbManager(const QString& s);

    /** Adds a pilot in the database
     * @param i id of the pilot (two characters)
     * @param r role of the pilot
     * @param f max frequency of flights per day. Zero means no maximum */
    void addPilot(const QString& i, const QString& r, const int f=0);

    /** Adds a workday in the database
     * @param d date of the day
     * @param s status of the day (e.g. off, v1, etc.)
     * @param i id of the pilot concerned */
    void addWorkday(const QDate& d, const QString& s, const QString& i);

    /** Retrieves status of pnt on one day
     * @param d date of the day
     * @param i id (two characters) of the pnt
     * @return the status as a string (e.g. off, v1, etc.) */
    QString statusOfPnt(const QDate d, const QString i);
    int getFlightTimePilot(const QString, int);

    /** Retreives all pnts able to be in the crew of a specified aircraft
     * @param m model of aircraft
     * @returns pnt ids */
    std::vector<QString> getPnts(const QString& m);

    /** Retrieves people of role [r] able to manage model [m]
     * @param m model of aircraft
     * @param r role asked (captain, first officer of flight engineer)
     * @returns pnt ids */
    std::vector<QString> getPnts(const QString& m, const QString& r);

    /** Retrieves pnts with a given status on a given day of a certain model
     * and having a certain role in the crew (ideal to fill the schedule!)
     * @param m aircraft model
     * @param r role of pnt in the crew
     * @param d date considered
     * @param s status wanted */
    std::vector<QString> getPnts(const QString& m, const QString& r,
                                 const QDate& d, const QString& s);

    /** A test function using see_status
     * @returns true if tests succeed */
    bool test();

private:
    QSqlDatabase m_db;
};

/** Main manager for all the program */
static DbManager _MANAGER = DbManager("");
#endif
