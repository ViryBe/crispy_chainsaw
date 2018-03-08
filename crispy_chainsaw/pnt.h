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

    Pnt( QString n, QString c, Role r, int f = -1 );

    /** Creates a pnt from the data taken from the database
     * @param p pnt structure, dump of the database */
    Pnt( PntDb p );

    /** Converts a role to string */
    static QString role2str( Pnt::Role );
    int getFlightTime( int month );
    int getTT();
    bool addWorkday( const QDate, const Workday::WorkDayStatus );

private:
    QString m_name;
    QString m_code;
    Role m_role;
    int m_maxfreq;
};

#endif     // PNT_H
