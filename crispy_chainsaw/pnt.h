#ifndef PNT_H
#define PNT_H

#include <QString>
#include "db.h"
#include "workday.h"

class Pnt
{
public:
    enum class Role {cpt, fo, fe};

    Pnt(QString name, QString code, Role r, int freq_max = -1);
    static QString role2str(Pnt::Role);
    int getFlightTime(int month);
    int getTT();
    bool addWorkday(const QDate, const Workday::WorkDayStatus);

private:
    QString m_name;
    QString m_code;
    Role m_role;
    int m_maxfreq;
};

#endif // PNT_H
