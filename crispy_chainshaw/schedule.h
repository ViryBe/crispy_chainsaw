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

    // We will manipulate ids... much simpler
    int id;

    // Equivalent to the domain of the variables
    std::vector<Pnt> getAvailablePilots();

    Flight& operator=(Flight o);
private:
    QDate date;
    int flight_number;
};

// Instance of the csp, maps flights to pilots
class ScheduleInstance
{
public:
    // New empty schedule computed from dates
    ScheduleInstance(const QDate, const QDate);
    // New schedule computed for the given flights
    ScheduleInstance(const std::vector<Flight>&);
    // New schedule based on an already existing schedule and vars to instantiate
    ScheduleInstance(const ScheduleInstance&, const std::vector<Flight>&);

private:
    // Status of the current instance
    enum class Status {unknown, solution, impossible};
    int n; // Number of variables in the problem
    bool consistent; // Is the schedule consistent?
    std::vector<std::string> v; // Values of the variables v[0] is a pseudo var
    std::vector<std::vector<std::string>> domain; // Domain of each variable
    std::vector<std::vector<std::string>> current_domain;

    // Fills schedule performing binary constraint problem resolution
    void bcssp(int, Status);

    /* Check for constraints, true  iff no constraint violated by neither
     * var i nor var j */
    bool check(int i, int j);

    // Tree search methods
    int bt_label(int);
    int bt_unlabel(int);
};

#endif // SCHEDULE_H
