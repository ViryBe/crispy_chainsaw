#include "pnt.h"

Pnt::Pnt(QString name, QString code, Role r, int freq_max)
    : m_name{name}, m_code {code}, m_role{r} ,m_maxfreq {freq_max}
{}

QString Pnt::role2str(Pnt::Role role)
{
    QString r;
    if (role == Role::cpt) {
        r = "cpt";
    }
    else if (role == Role::fe) {
        r = "fe";
    }
    else if (role == Role::fo) {
        r = "fo";
    }
    return r;
}

/*
int Pnt::getFlightTime(int month)
{
    return _MANAGER.getFlightTimePilot(m_code, month);
}
*/
