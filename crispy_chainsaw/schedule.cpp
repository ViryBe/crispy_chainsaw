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
        today.addDays(i % m_model.getFreqMax()); // One day more each freq flights
        std::vector<QString> crewmem =
                _MANAGER.getAvailablePnts(today, Pnt::role2str(m_role),
                                          m_model.getName());

        domain[i].resize(crewmem.size());
        domain[i] = crewmem;
        current_domain[i].resize(crewmem.size());
        current_domain[i] = crewmem;
	}
    v.resize(n + 1);
}

int ScheduleInstance::bt_label(int i)
{
	consistent = false;
	auto cd_copy = current_domain[i];
    for (int j = 0 ; j < (int) cd_copy.size() && !consistent ; j++) {
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
	consistent=true;
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
		else if( i == 0){
			status =Status::impossible;
		}
	}
}

bool ScheduleInstance::check(int i, int j)
{
    if (i % m_model.getFreqMax() == j % m_model.getFreqMax()) {
        // A crew member cannot do two flights the same day
        return v[i] != v[j];
    }
    return true;
}
