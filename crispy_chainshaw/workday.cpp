#include "workday.h"

Workday::WorkDayStatus str2wds(const QString& s)
{
    Workday::WorkDayStatus res = Workday::WorkDayStatus::OFF;
    if (s == "off") { res = Workday::WorkDayStatus::OFF; }
    else if (s == "office") { res = Workday::WorkDayStatus::OFFICE; }
    else if (s == "standby") { res = Workday::WorkDayStatus::STANDBY; }
    else if (s == "v1") { res = Workday::WorkDayStatus::V1; }
    else if (s == "v2") { res = Workday::WorkDayStatus::V2; }
    else if (s == "v3") { res = Workday::WorkDayStatus::V3; }
    else { qDebug("invalid string not a workdaystatus"); }
    return res;
}

QString wds2str(const Workday::WorkDayStatus& wds)
{
    QString res = "";
    if (wds == Workday::WorkDayStatus::OFF) {res="off";}
    else if (wds == Workday::WorkDayStatus::OFFICE) {res="office";}
    else if (wds == Workday::WorkDayStatus::STANDBY){res="standby";}
    else if (wds == Workday::WorkDayStatus::V1){res="v1";}
    else if (wds == Workday::WorkDayStatus::V2){res="v2";}
    else if (wds == Workday::WorkDayStatus::V3){res="v3";}
    else {qDebug("invalid wds");}

    return res;
}

Workday::Workday(const QDate date, const Workday::WorkDayStatus status)
{
}
