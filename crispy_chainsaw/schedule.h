#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "db.h"
#include <QDate>
#include <algorithm>
#include <vector>

void loadSchedule(
    QDate = QDate::currentDate(), QDate = QDate::currentDate().addDays( 15 ) );
void createSchedule( QDate, QDate );

/** # Definition
 * The aim of the schedule is to provide a crew for each flight. To lighten
 * the object, a schedule concerns *only one* aircraft model and *only one*
 * role among those available for the aircraft model.
 *
 * # Model used
 * The schedule is modelled by a constraint satisfaction problem.
 *
 * ## Description of the model
 * This model works chronogically on the flights, it attaches crew members to
 * each flight.
 * * Variables: flight number, e.g. if a plane has three flights per day,
 *   the first variable is the first flight of the first day and the fifth
 *   variable is the 2nd flight of the 2nd day.
 * * Values: the afore mentioned variables take as value the id of a
 *   part of the crew, e.g. if the first variable of the schedule concerning
 *   aircraft model `x` and captains, `v1 = aa` means that the captain
 *   identified by the id `aa` will be on the first flight of the first day.
 * * Domain: the domain of each variable is the set of adequate personnel
 *   (we mean having the good role) whose status on the considered day is
 *   neither `office` nor `off`.
 * * Constraints: mainly, a crew members cannot do more than one flight per
 *   day, and some crew members have a maximum frequency of flight per month.
 *   We are looking for more.
 *
 * Ideally, the flights should be equally balanced among crew members. In
 * order to do that, the lists (or vectors) containing crew members will be
 * sorted according to their number of flights after each attachment. This way,
 * the csp solver will always consider first the members having the fewer hours
 * of flight.
 */
class ScheduleInstance
{
public:
    /** Creates a schedule spanning over one week.
     * @param m model of the aircraft concerned by this schedule
     * @param r role concerned by the schedule
     * @param db date of the beginning of the schedule */
    ScheduleInstance( const AcftModelDb& m, QString r,
                      QDate db = QDate::currentDate() );

    /** Schedules minimal number of consecutive weeks such that the two dates
     * given as arg are scheduled.
     * @param m aircraft model of the schedule
     * @param r role of the schedule
     * @param b beginning date
     * @param e end date */
    static void schedule( const AcftModelDb& m, QString r, QDate b, QDate e);

    /** Updates database
     * @param dbm database manager */
    void updateDb( DbManager dbm );

    /** Prints the deduced schedule to stdout */
    void print();

    /** Get rest contraints compliancy status
     * @returns true iff rest contraints are matched */
    bool getRestCompliancy();

    /** Rebuilds the schedule from a specified date
     * @param m model of aircraft concerned
     * @param r role concerned
     * @param date from which to recompute */
    static void recomputeFrom( const AcftModelDb& m, QString r, QDate f );

    /** Test, creates a schedule from dummydb */
    static bool test();

private:
    // Misc data
    AcftModelDb mModel;
    QString mRole;
    QDate mStartDate;
    bool mRestCompliancy; ///< Asserts whether rest contraints are matched

    struct workRegister
    {
        int flights = 0;
        int serviceDays = 0;

        struct prevFlightTime {
            float month = 0.;
            float year = 0.;
        };

        prevFlightTime mPrevFlightTime;

        bool operator<( const workRegister& wr );
        bool check();            ///< Check time limits constraints
        void addFlight();        ///< Adds a flight to register
        void removeFlight();     ///< Removes a flight from register
    };

    // Data for the csp solver
    enum class Status { unknown, solution, impossible };     ///< Status of csp
    int n;     ///< Number of variables in the problem, i.e. number of flights
    bool consistent;     ///< Is the schedule consistent?
    std::vector<QString>
        v;     ///< Values of the variables v[0] is a pseudo var
    std::vector<std::vector<QString>> domain;     ///< Domain of each variable
    std::vector<std::vector<QString>> current_domain;
    std::map<QString, workRegister>
        workload; ///< Maps pntid to number of flights newly attributed

    /** Calls tree search methods to solve the *binary* constraint satisfaction
     * problem, i.e. the creation of the schedule. Works in place, modifying
     * the [v] vector. For more information on the algorithms used, please
     * see *Hybrid Algorithms for the Constraint Satisfaction Problem*, Patrick
     * Prosser*.
     * @param n the number of variables to instantiate
     * @param status the initial status of the problem */
    void bcssp( int, Status );

    /** Check for constraints, true  iff no constraint violated by neither
     * var i nor var j */
    bool check( int i, int j );

    /** Checks for rest constraints. Triggered post computation
     * @returns true if complies to constraints */
    bool checkRest();

    /** Backtrack tree search method, label for forward step, i.e.
     * tries to find an instatiation for variable [i]
     * @param i the variable to be instantiated
     * @returns the new current variable */
    int bt_label( int i );
    /** Backtrack unlabel, performs backtracking from v[i] to v[h], called
     * when consistent is false and all values for variable i has been tested.
     * @returns the new current variable */
    int bt_unlabel( int );

    /** Modifies order of values in the domain (since domains are
     * implemented as lists) to favour instantiation of variables
     * @param v number of the variable whose domain has to be sorted */
    void sort_domains( int v);
};

#endif     // SCHEDULE_H
