#include "pnt.h"

Pnt::Pnt(QString name, QString code, Role r, int freq_max)
    : m_name{name}, m_code {code}, m_role{r} ,m_maxfreq {freq_max}
{}

/*
int Pnt::getFlightTime(int month)
{
    return _MANAGER.getFlightTimePilot(m_code, month);
}
*/
