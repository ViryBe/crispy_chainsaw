#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDate>

void loadSchedule(QDate = QDate::currentDate(), QDate =
        QDate::currentDate().addDays(15));
void createSchedule(QDate, QDate);

#endif // SCHEDULE_H
