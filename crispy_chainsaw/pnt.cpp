#include "pnt.h"

Pnt::Pnt( QString id, QString name, QString role, QString model, int flightnb,
    int maxfreq )
{
    m_id = id;
    m_name = name;
    m_role = str2role( role );
    m_acftmodel = model;
    m_flightnb = flightnb;
    m_maxfreq = maxfreq;
}

/* Does not work properly yet (or I don't know how to make it work) since
 * conversion needs a constructor in the 'to' type (this is the 'from' type). */
Pnt::operator PntDb() const
{
    PntDb pdb;
    pdb.id = m_id;
    pdb.name = m_name;
    pdb.role = role2str( m_role );
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

Pnt::Role Pnt::str2role( QString role )
{
    Role r;
    if ( role == "cpt" ) {
        r = Role::cpt;
    } else if ( role == "fo" ) {
        r = Role::fo;
    } else if ( role == "fe" ) {
        r = Role::fe;
    } else {
        throw "invalid role";
    }
    return r;
}

void Pnt::toDb()
{
    // PntDb pdb(*this);
    PntDb pdb = static_cast<PntDb>( *this );
    _MANAGER->updatePnt( pdb );
}
