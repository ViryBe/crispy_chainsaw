#ifndef PNT_H
#define PNT_H

#include "db.h"
#include "workday.h"
#include <QString>

class Pnt
{
public:
    /** Available roles in the company
     * * captain
     * * first office
     * * flight engineer */
    enum class Role { cpt, fo, fe };

    /** Creates a pnt
     * @param i identifier, two letters string,
     * @param n full name of the pnt
     * @param r role of the pnt in a crew
     * @param a aircraft model to which the pnt is assigned
     * @param f number of flights so far
     * @param m max frequency of flights per months (zero if no limit) */
    Pnt( QString i, QString n, Role r, QString a, int f = 0, int m = 0 );

    /** Creates a pnt from the data taken from the database
     * @param p pnt structure, dump of the database */
    Pnt( PntDb p );

    /** Converts a role to string */
    static QString role2str( Pnt::Role );

private:
    QString m_id;
    QString m_name;
    Role m_role;
    QString m_acftmodel;
    int m_flightnb;
    int m_maxfreq;
};

#endif     // PNT_H
