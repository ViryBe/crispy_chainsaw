#ifndef DB_H
#define DB_H

#include <QString>
#include <QtSql>
#include <iostream>
#include <regex>

extern QString DATEFMT;

/** Representation of the pnt in the database */
struct PntDb
{
    QString id;       ///< Unique id based on pnt's name
    QString name;     ///< Name of the staff member
    QString role;     ///< Role of the crew member (e.g. cpt for captain)
    QString acft_modelname;     ///< Name of aircraft model which can be piloted
    int maxfreq = 0;            ///< Maximum number of flights per month
};

/** Representation of an aircraft model in the database */
struct AcftModelDb
{
    QString name;     ///< Name of the model, also identifier
    int maxfreq;      ///< Maximum number of flights per day for this model
    int nop;          ///< Number of operational models owned by the company
    int ntot;     ///< Total number of aircrafts of this model owned by the comp
    int crew;     ///< Number of people needed to form a crew
};

/** Representation of a day of a pnt in the database */
struct WorkdayDb
{
    QDate workdate;     ///< Date of the day
    QString status;     ///< Which work (e.g. simulator, office, v1, etc.)
    QString pntid;      ///< Pnt concerned
    int forced = 0;     ///< Whether workday has been added manually
};

/** Manages all inputs and outputs with the database. The SQL schema is not
 * given anywhere, although it would be a good idea. */
class DbManager
{
public:
    DbManager() = default;

    /** Creates a dbmanager managing a sqlite file
     * @param s sqlite filepath */
    void init( const QString& s );

    /** Updates (edit or create) pilot having same id as the PntDb structure
     * @param pdb pnt data to update, the id must be in the database */
    void updatePnt( PntDb pdb );

    /** Deletes pilot with id i
     * @param i id of the pilot to be deleted */
    void deletePnt( QString i );

    /** Adds a workday in the database
     * @param d date of the day
     * @param s status of the day (e.g. off, v1, etc.)
     * @param i id of the pilot concerned */
    void addWorkday( const QDate& d, const QString& s, const QString& i );

    /** Same as above but takes directly a Workday structure */
    void addWorkday( const WorkdayDb& );

    /** Deletes a workday from the database. Remains silent if workday does
     * not exist (not tested)
     * @param d date of the workday
     * @param i id of concerned pnt */
    void deleteWorkday( QDate d, QString i );

    /** Gather workdays of a pnt
     * @param i id of pnt
     * @param f begin date
     * @param t end date
     * @param s status wanted */
    std::vector<WorkdayDb> getWorkdays( QString i, QDate f, QDate t,
                                        QString s = "_" );

    /** Asserts whether a flight has a crew assigned manually
     * @param d date of the flight
     * @param m model of the aircraft
     * @param r role needed
     * @param s status of the flight
     * @returns true iff a pnt matches the requirements */
    bool workForced(
        const QDate& d, const QString& m, const QString& r, const QString& s );

    /** @returns date of the last day scheduled automatically */
    QDate getLastScheduledDay();

    /** Select all workdays written by the scheduler between two days
     * @param f from when to fetch days
     * @param t upper limit for days
     * @param r role concerned by the workday (defaults to sqlite wildcard)
     * @param m model of aircraft concerned by the model (defaults to sqlite
     *          wildcard)
     * @returns all days set automatically */
    std::vector<WorkdayDb> getAutomaticallySetWorkdays(
        QDate f, QDate t, QString r = "_", QString m = "_" );

    /** Returns id of pnt working on a specified flight
     * @param d date of the flight
     * @param m model of aircraft on the flight
     * @param r role needed for the flight
     * @param s status of the flight (v1, v2, v3)
     * @returns id of matching pnt, throws an exception else */
    QString getWorkingPnt(
        const QDate& d, const QString& m, const QString& r, const QString& s );

    /** Retrieves status of pnt on one day
     * @param d date of the day
     * @param i id (two characters) of the pnt
     * @return the status as a string (e.g. off, v1, etc.) */
    QString statusOfPnt( const QDate d, const QString i );

    /** Retrieve all pnt ids from database */
    std::vector<QString> getPnts();

    /** Retrieve all the info about a pnt
     * @param pntid identifier (string of two characters) */
    PntDb getPnt( QString pntid );

    /** Count incative days between two dates
     * @param i identifier of the pnt
     * @param b beginning of the period
     * @param e end of the period
     * @returns number of days with neither flights nor office nor hollidays
     *          programmed */
    int cardInactiveDays( QString i, QDate b, QDate e );

    /** Retreives all pnts able to be in the crew of a specified aircraft
     * @param m model of aircraft
     * @returns pnt ids */
    std::vector<QString> getPnts( const QString& m );

    /** Retrieves people of role [r] able to manage model [m]
     * @param m model of aircraft
     * @param r role asked (captain, first officer of flight engineer)
     * @returns pnt ids */
    std::vector<QString> getPnts( const QString& m, const QString& r );

    /** Retrieves pnts with a given status on a given day of a certain model
     * and having a certain role in the crew (great to fill the schedule!)
     * @param m aircraft model
     * @param r role of pnt in the crew
     * @param d date considered
     * @param s status wanted */
    std::vector<QString> getPnts(
        const QString& m, const QString& r, const QDate& d, const QString& s );

    /** Retrieves members without workday
     * @param m model concerned
     * @param r role concerned
     * @param d date of the day */
    std::vector<QString> getIdlePnts(
        const QString& m, const QString& r, const QDate& d );

    /** Get all data on an aircraft model
     * @param n name of the model */
    AcftModelDb getAcftModel( const QString& n );

    /** A test function using see_status
     * @returns true if tests succeed */
    bool test();

private:
    QSqlDatabase m_db;
    static QString capitalizeFirstLetters( QString s );

    /** Adds a pilot in the database
     * @param pdb pilot structure */
    void addPnt( PntDb pdb );

    void modifyPnt( PntDb pdb );
};

/** Main manager for all the program */
extern DbManager _MANAGER;
#endif
