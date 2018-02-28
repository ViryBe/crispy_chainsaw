#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDate>
#include "pnt.h"
#include "acftmodel.h"
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

/** Instance of a schedule. A schedule concerns only one model and only one
 * role among the crew needed for the aircraft (by this we mean that there
 * is no constraint between the different member of the crew). */
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

private:
    // Misc data
    AcftModel m_model;
    Pnt::Role m_role;

    // Data for the csp solver
    enum class Status {unknown, solution, impossible}; /// Status of csp
    int n; /// Number of variables in the problem, i.e. number of flights
    bool consistent; /// Is the schedule consistent?
    std::vector<QString> v; /// Values of the variables v[0] is a pseudo var
    std::vector<std::vector<QString>> domain; /// Domain of each variable
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
