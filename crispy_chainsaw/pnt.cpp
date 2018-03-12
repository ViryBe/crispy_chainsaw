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

Pnt::operator PntDb() const
{
    PntDb pdb;
    pdb.id = m_id;
    pdb.name = m_name;
    pdb.role = role2str(m_role);
    pdb.acft_modelname = m_acftmodel;
    pdb.flightnb = m_flightnb;
    pdb.maxfreq = m_maxfreq;
    return pdb;
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
