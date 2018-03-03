#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "pnt.h"
#include "acftmodel.h"
#include "db.h"
#include <QDate>
#include <vector>
#include <algorithm>

void loadSchedule(QDate = QDate::currentDate(), QDate =
        QDate::currentDate().addDays(15));
void createSchedule(QDate, QDate);

/** Flight requirement, to be entered in schedule */
struct Flight {
    QDate date; ///< Date of the flight
    AcftModel model; ///< Model of aircraft concerned
    int position; ///< Position of flight during day (1st, 2nd, etc.)
};

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
    /** Creates a schedule defined by the dates of beginning and end.
     * @param m model of the aircraft concerned by this schedule
     * @param r role concerned by the schedule
     * @param db date of the beginning of the schedule
     * @param de date of the end of the schedule */
    ScheduleInstance(const AcftModel& m, const Pnt::Role r,
                     const QDate db, const QDate de);

    /** Creates a 15 days schedule defined by the dates of beginning.
     * @param m model of the aircraft concerned by this schedule
     * @param r role concerned by the schedule
     * @param db date of the beginning of the schedule */
    ScheduleInstance(const AcftModel& m, const Pnt::Role r,
                     const QDate db);

    /** Schedules the flights given as parameter
     * @param m model of aircraft
     * @param r role concerned
     * @param f flights to schedule */
    ScheduleInstance(const AcftModel& m, const Pnt::Role r,
                     const std::vector<Flight>& f);
    /** Completes an already existing schedule with new flights. Already
     * existing flights are not modified, an error is raised if the already
     * existing schedule is not consistent.
     * @param s schedule to complete
     * @param f flights to schedule */
    ScheduleInstance(const ScheduleInstance& s, const std::vector<Flight>& f);

    /** Updates database
     * @param d database manager */
    void updateDb(DbManager d);

    /** Prints the deduced schedule to stdout */
    void print();

    /** Test, creates a schedule from dummydb */
    static bool test();

private:
    // Misc data
    AcftModel m_model;
    Pnt::Role m_role;
    QDate m_startdate;

    // Data for the csp solver
    enum class Status {unknown, solution, impossible}; ///< Status of csp
    int n; ///< Number of variables in the problem, i.e. number of flights
    bool consistent; ///< Is the schedule consistent?
    std::vector<QString> v; ///< Values of the variables v[0] is a pseudo var
    std::vector<std::vector<QString>> domain; ///< Domain of each variable
    std::vector<std::vector<QString>> current_domain;

    /** Calls tree search methods to solve the *binary* constraint satisfaction
     * problem, i.e. the creation of the schedule. Works in place, modifying
     * the [v] vector. For more information on the algorithms used, please
     * see *Hybrid Algorithms for the Constraint Satisfaction Problem*, Patrick
     * Prosser.
     * @param n the number of variables to instantiate
     * @param status the initial status of the problem */
    void bcssp(int, Status);

    /** Check for constraints, true  iff no constraint violated by neither
     * var i nor var j */
    bool check(int i, int j);

    /** Backtrack tree search method, label for forward step, i.e.
     * tries to find an instatiation for variable [i]
     * @param i the variable to be instantiated
     * @returns the new current variable */
    int bt_label(int i);
    /** Backtrack unlabel, performs backtracking from v[i] to v[h], called
     * when consistent is false and all values for variable i has been tested.
     * @returns the new current variable */
    int bt_unlabel(int);
};

#endif // SCHEDULE_H
