#ifndef WORKDAY_H
#define WORKDAY_H

#include <QDateTime>


class Workday
{
public:
    /// Type used to describe the day of a pilot
    enum class WorkDayStatus {off, standby, office, v1, v2, v3};
    /// Converts a string to a WorkDayStatus
    WorkDayStatus str2wds(const QString&);
    /// Converts a WorkDayStatus to a string
    QString wds2str(const WorkDayStatus&);

    Workday(const QDate, const WorkDayStatus);
    WorkDayStatus getStatus();

private:
    QDate m_date;
    WorkDayStatus m_status;
};

#endif // WORKDAY_H
