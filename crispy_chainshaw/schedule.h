#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDate>
#include <pnt.h>

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
    // New empty schedule
    ScheduleInstance();
    // New schedule computed for the given flights
    ScheduleInstance(const std::vector<Flight>&);
    // New schedule based on an already existing schedule and vars to instantiate
    ScheduleInstance(const ScheduleInstance&, const std::vector<Flight>&);

    // If a variable is already instantiated, it is replaced by the new one
    void simpleUnion(const ScheduleInstance&);

    // Returns an instance mapping conflicting vars to conflicting values
    ScheduleInstance consistent();
private:
    // Internal map
    std::map<Flight, Pnt> schedule;

    // Asserts whether the two variables, with their value violate a constraint
    // It might be necessary to expand to n-ary constraints...
    bool violate(Flight, Pnt, Flight, Pnt);

    // Constraint backjumping algorithm
    void cbj(std::vector<Pnt>, ScheduleInstance);
};

#endif // SCHEDULE_H
