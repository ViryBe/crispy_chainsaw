#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDate>
#include "pnt.h"
#include <vector>
#include <algorithm>

void loadSchedule(QDate = QDate::currentDate(), QDate =
        QDate::currentDate().addDays(15));
void createSchedule(QDate, QDate);

// Variables of the csp
class Flight
{
public:
    Flight(QDate);

    // Equivalent to the domain of the variables
    std::vector<Pnt> getAvailablePilots();

    // Needed for map
    operator<=(const Flight& f2);
private:
    QDate date;
    int flight_number;
};

// Instance of the csp, maps flights to pilots
class ScheduleInstance
{
public:
    // New empty schedule computed from dates
    ScheduleInstance(QDate, QDate);
    // New schedule computed for the given flights
    ScheduleInstance(const std::vector<Flight>&);
    // New schedule based on an already existing schedule and vars to instantiate
    ScheduleInstance(const ScheduleInstance&, const std::vector<Flight>&);

    // Fills schedule performing binary constraint problem resolution
    void bcssp(int, Status);

private:
    // Status of the current instance
    enum class Status {unknown, solution, impossible};
    int n; // Number of variables in the problem
    bool consistent; // Is the schedule consistent?
    std::vector<Flight> v; // Values of the variables v[0] is a pseudo var
    std::vector<std::vector<Pnt>> domain; // Domain of each variable
    std::vector<std::vector<Pnt>> current_domain;

    /* Check for constraints, true  iff no constraint violated by neither
     * var i nor var j */
    bool check(int i, int j);

    // Tree search methods
    int bt_label(int);
    int bt_unlabel(int);
};

#endif // SCHEDULE_H
