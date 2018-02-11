#ifndef WORKDAY_H
#define WORKDAY_H

#include <QDateTime>


class Workday
{
public:
    /// Type used to describe the day of a pilot
    enum class WorkDayStatus {OFF, STANDBY, OFFICE, V1, V2, V3};

    Workday(const QDate, const WorkDayStatus);
    WorkDayStatus getStatus();

private:
    QDateTime m_date;
    WorkDayStatus m_status;
};

#endif // WORKDAY_H
