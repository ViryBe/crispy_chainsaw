#ifndef DB_H
#define DB_H

#include <QString>
#include <QtSql>
#include <iostream>
#include <regex>

const QString kSQLWILDCARD = "%";

/** Representation of the pnt in the database */
struct PntDb
{
    enum Role { eCpt, eFirstOfficer, eFlightEngineer };
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
    enum Status { eV1, eV2, eV3, eOffice, eOff, eStBy, eSimu };
    QDate workdate;          ///< Date of the day
    QString status;          ///< Which work (e.g. simulator, office, v1, etc.)
    QString pntid;           ///< Pnt concerned
    QTime lapse = QTime(0, 0);  ///< Duration of the workday
    bool forced = false;     ///< Whether workday has been added manually
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
     * @param i id of the pilot concerned
     * @param f manually (forced) workday
     * @param l lapse of the workday */
    void addWorkday( QDate d, QString s, QString i, bool f = false,
                     QTime l = QTime(0, 0));

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
    std::vector<WorkdayDb> getWorkdays(
        QString i, QDate f, QDate t, QString s = kSQLWILDCARD );

    /** Get a workday
     * @param m aircraft model,
     * @param d date
     * @param s status */
    std::vector<WorkdayDb> getWorkdays( QString m, QDate d, QString s);

    /** Asserts whether a flight has a crew assigned manually
     * @param d date of the flight
     * @param m model of the aircraft (defaults to sqlite wildcard)
     * @param r role needed (defaults to sqlite wildcard)
     * @param s status of the flight (defaults to sqlite wildcard)
     * @returns true iff a pnt matches the requirements */
    bool workForced( QDate d, QString m = kSQLWILDCARD,
                     QString r = kSQLWILDCARD, QString s = kSQLWILDCARD );

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
        QDate f, QDate t, QString r = kSQLWILDCARD, QString m = kSQLWILDCARD );

    /** Attach one workday for each pnt of the database on a date. Workdays are
     * added with status 'stby'.
     * @param d date
     * @param m aircraft model (default to wildcard)
     * @param r role (default to wildcard) */
    void fillWorkdays( QDate d, QString m = kSQLWILDCARD,
                       QString r = kSQLWILDCARD );

    /** Edit the duration of a flight
     * @param d date of the flight
     * @param m model of the aircraft assigned to the flight
     * @param s status of the flight
     * @param t duration of flight */
    void editFlightLapse(QDate d, QString m, QString s, QTime t);

    /** Returns id of pnts working at a role
     * @param d date of the flight
     * @param m model of aircraft on the flight
     * @param r role needed for the flight
     * @param s status of the flight (v1, v2, v3)
     * @returns id of matching pnt, throws an exception else */
    std::vector<QString> getWorkingPnt( QDate d, QString m, QString r,
            QString s );

    /** Retrieves status of pnt on one day
     * @param d date of the day
     * @param i id (two characters) of the pnt
     * @return the status as a string (e.g. off, v1, etc.) */
    QString statusOfPnt( QDate d, QString i );

    /** Counts number of days of work
     * @param i id of pnt
     * @param b begin date
     * @param e end date
     * @param j job requested */
    int cardWorkdays( QString i, QDate b, QDate e, QString j = kSQLWILDCARD );

    /** Count incative days between two dates
     * @param i identifier of the pnt
     * @param b beginning of the period
     * @param e end of the period
     * @returns number of days with neither flights nor office nor hollidays
     *          programmed */
    int cardInactiveDays( QString i, QDate b, QDate e );

    /** Retrieve all the info about a pnt
     * @param pntid identifier (string of two characters) */
    PntDb getPnt( QString pntid );

    /** Retrieve pnts given their job or their model of aircraft. Parameters
     * default to sqlite wildcard (kSQLWILDCARD).
     * @param m model of aircraft
     * @param r role required (captain, first officer, ...)
     * @returns all pnts matching the requirements */
    std::vector<QString> getPnts(
        QString m = kSQLWILDCARD, QString r = kSQLWILDCARD );

    /** Retrieves pnts with a given status on a given day of a certain model
     * and having a certain role in the crew (great to fill the schedule!)
     * All parameters have the sqlite wildcard as default, except date.
     * @param d date considered
     * @param s status wanted
     * @param m aircraft model
     * @param r role of pnt in the crew */
    std::vector<QString> getPnts( QDate d, QString s = kSQLWILDCARD,
        QString m = kSQLWILDCARD, QString r = kSQLWILDCARD );

    /** Retrieves members without workday or with workdays marked as stby
     * @param m model concerned
     * @param r role concerned
     * @param d date of the day */
    std::vector<QString> getIdlePnts(
            QDate d, QString m = kSQLWILDCARD, QString r = kSQLWILDCARD );

    /** Get all data on an aircraft model
     * @param n name of the model */
    AcftModelDb getAcftModel( QString n );

    /** Creates query strings to manipulate the view
     * @param v view name
     * @param b begin date
     * @param e end date
     * @param m aircraft model
     * @param r role queried */
    static QString scheduleViewQuery(QString v, QDate b, QDate e, QString m,
            QString r);

    /** Creates a view to fill a schedule table view
     * @param n name of the view
     * @param f date of beginning of view
     * @param t date of last day of view */
    void createScheduleView( QString n, QDate d, QDate t );

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

    /** Try to delete view with name v */
    void deleteView( QString v);

    void cleanSmallViews( QDate b, QDate e );
};

/** Main manager for all the program */
extern DbManager gMANAGER;
#endif
