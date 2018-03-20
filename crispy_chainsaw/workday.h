#ifndef WORKDAY_H
#define WORKDAY_H

#include "db.h"
#include <QDateTime>


class Workday
{
public:
    Workday( const QString& i, const QDate& d, const QString& s );
    Workday( const WorkdayDb& );
    QString getStatus();

private:
    /// Type used to describe the day of a pilot
    enum class WorkDayStatus { off, standby, office, v1, v2, v3 };
    /// Converts a string to a WorkDayStatus
    static WorkDayStatus str2wds( const QString& );
    /// Converts a WorkDayStatus to a string
    static QString wds2str( const WorkDayStatus& );

    QString m_pntid;
    QDate m_date;
    WorkDayStatus m_status;
};

#endif     // WORKDAY_H
