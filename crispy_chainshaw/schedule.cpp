#include "schedule.h"

ScheduleInstance::ScheduleInstance() {
	domain.resize(_nvar + 1);
    current_domain.resize(n + 1);
	for (int i = 1 ; i <= _nval ; i++) {
		domain[i].resize(4);
		domain[i] = std::vector<int> {1, 2, 3, 4};
		current_domain[i].resize(4);
		current_domain[i] = std::vector<int> {1, 2, 3, 4};
	}
	v.resize(_nvar + 1);
}

void ScheduleInstance::print() {
    for (int i = 1 ; i <= n ; i++) {
		std::cout << v[i];
	}
	std::cout << "\n";
}

int ScheduleInstance::bt_label(int i)
{
	consistent = false;
	auto cd_copy = current_domain[i];
	for (int j = 0 ; j < cd_copy.size() && !consistent ; j++) {
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
