#include "schedule.h"

ScheduleInstance::ScheduleInstance(
        const AcftModel& _model, const Pnt::Role _role,
        const QDate dbeg, const QDate dend) {

    m_model = _model;
    m_role = _role;

    // Number of variables = freq * number of days
    n = m_model.getFreqMax() * (int) dbeg.daysTo(dend);

    // Init memory and csp related var
    domain.resize(n + 1);
    current_domain.resize(n + 1);
    QDate today = dbeg;
    for (int i = 1 ; i <= n ; i++) {
        // One day more each freq flights
        today.addDays((i - 1) % m_model.getFreqMax());
        std::vector<QString> crewmem =
                _MANAGER.getIdlePnts(m_model.getName(), Pnt::role2str(m_role),
                                 today);

        domain[i].resize(crewmem.size());
        domain[i] = crewmem;
        current_domain[i].resize(crewmem.size());
        current_domain[i] = crewmem;
	}
    v.resize(n + 1);

    // create schedule
    bcssp(n, Status::unknown);
}

ScheduleInstance::ScheduleInstance(
        const AcftModel& _model, const Pnt::Role _role,
        const QDate dbeg)
{
    ScheduleInstance(_model, _role, dbeg, dbeg.addDays(15));
}

int ScheduleInstance::bt_label(int i)
{
    qDebug() << "bt_label";
	consistent = false;
	auto cd_copy = current_domain[i];
    for (unsigned int j = 0 ; j < cd_copy.size() && !consistent ; j++) {
		v[i] = cd_copy[j];
		consistent = true;
		for (int h = 1 ; h < i && consistent ; h++) {
			consistent = check(i, h);
			if (!consistent) {
				current_domain[i].erase(std::remove(current_domain[i].begin(),
							current_domain[i].end(), v[i]));
			}
		}
	}
	return consistent ? (i + 1) : i;
}

int ScheduleInstance::bt_unlabel(int i)
{
    qDebug() << "bt_unlabel";
	int h = i - 1;
	current_domain[i] = domain[i];

	if (current_domain[h].size() > 0) {
		auto it =
			std::find(current_domain[h].begin(), current_domain[h].end(), v[h]);
		current_domain[h].erase(it);
	}
	consistent = current_domain[h].size() > 0;
	return h;
}

void ScheduleInstance::bcssp(int n, Status status)
{
    consistent = true;
	int i = 1;
	while (status == Status::unknown){
		if (consistent) {
			i = bt_label(i);
		}
		else {
			i = bt_unlabel(i);
		}
		if (i > n) {
			status = Status::solution;
		}
        else if(i == 0) {
            status = Status::impossible;
            qDebug () << "impossible";
		}
	}
}

bool ScheduleInstance::check(int i, int j)
{
    if ( // If two flights happen the same day...
            (int) ( (i - 1) / m_model.getFreqMax() ) ==
            (int) ( (j - 1) / m_model.getFreqMax() )
            ) {
        // ...ensure pilots are different
        return v[i] != v[j];
    }
    return true;
}

void ScheduleInstance::updateDb(DbManager dbm)
{
    // For each variable, update related workday
    for (int i = 1 ; i <= n ; i++) {
        QDate date = m_startdate.addDays(
                    (int) ( (i - 1) / m_model.getFreqMax() ) );
        QString flightno = "v" + ( (i - 1) % m_model.getFreqMax() + 1 );
        QString pntid = v[i];

        dbm.addWorkday(date, flightno, pntid);
    }
}

void ScheduleInstance::print()
{
    int day;
    int flight_no;
    for (int i = 1 ; i <= n ; i++) {
        day = 1 + (int) ( (i - 1) / m_model.getFreqMax() );
        flight_no = (i - 1) % m_model.getFreqMax();

        qDebug() << "day: " << day << ";"
                 << "flight number: " << flight_no << ";"
                 << "pnt: " << v[i];
    }
}

bool ScheduleInstance::test()
{
    Pnt::Role role = Pnt::Role::cpt;
    AcftModel mod = AcftModel("a", 2, 2);

    ScheduleInstance si = ScheduleInstance(
                mod, role, QDate::currentDate(),
                QDate::currentDate().addDays(2));
    si.print();
    return true;
}
