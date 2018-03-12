#include "pnt.h"

Pnt::Pnt(QString id, QString name, Role role, QString model,
    int flightnb, int maxfreq)
{
    m_id = id;
    m_name = name;
    m_role = role;
    m_acftmodel = model;
    m_flightnb = flightnb;
    m_maxfreq = maxfreq;
}

QString Pnt::role2str( Pnt::Role role )
{
    QString r;
    if ( role == Role::cpt ) {
        r = "cpt";
    } else if ( role == Role::fe ) {
        r = "fe";
    } else if ( role == Role::fo ) {
        r = "fo";
    }
    return r;
}
