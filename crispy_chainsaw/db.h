#ifndef DB_H
#define DB_H

#include <QtSql>
#include <QString>
#include <iostream>

/** Representation of the pnt in the database */
struct PntDb {
    QString id; ///< Unique id based on pnt's name
    QString role; ///< Role of the crew member (e.g. cpt for captain)
    int freq_max; ///< Maximum number of flights per month
    int acft_modelid; ///< Id of aircraft for which crew member is qualified
};

/** Representation of an aircraft model in the database */
struct AcftModelDb {
    QString name; ///< Name of the model, also identifier
    int freq_max; ///< Maximum number of flights per day for this model
    int nop; ///< Number of operational models owned by the company
    int ntot; ///< Total number of aircrafts of this model owned by the comp
    int crew; ///< Number of people needed to form a crew
};

/** Representation of a day of a pnt in the database */
struct WorkdayDb {
    QString workdate; ///< Date of the day
    QString status; ///< Which work (e.g. simulator, office, v1, etc.)
    QString pntid; ///< Pnt concerned
};

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

    /** Same as above but takes directly a Workday structure */
    void addWorkday(const WorkdayDb&);

    /** Retrieves status of pnt on one day
     * @param d date of the day
     * @param i id (two characters) of the pnt
     * @return the status as a string (e.g. off, v1, etc.) */
    QString statusOfPnt(const QDate d, const QString i);
    int getFlightTimePilot(const QString, int);

    /** Retrieve all pnt ids from database */
    std::vector<QString> getPnts();

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

    /** Retrieves members without workday
     * @param m model concerned
     * @param r role concerned
     * @param d date of the day */
    std::vector<QString> getIdlePnts(const QString& m, const QString& r,
                                     const QDate& d);

    /** Get all data on an aircraft model
     * @param n name of the model */
    AcftModelDb getAcftModel(const QString& n);

    /** A test function using see_status
     * @returns true if tests succeed */
    bool test();

private:
    QSqlDatabase m_db;
};

/** Main manager for all the program */
extern DbManager _MANAGER;
#endif
