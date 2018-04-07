#ifndef PNT_H
#define PNT_H

#include "db.h"
#include "workday.h"
#include <QString>

class Pnt
{
public:
    /** Creates a pnt
     * @param i identifier, two letters string,
     * @param n full name of the pnt
     * @param r role of the pnt in a crew
     * @param a aircraft model to which the pnt is assigned
     * @param m max frequency of flights per months (zero if no limit) */
    Pnt( QString i, QString n, QString r, QString a, int m = 0 );

    /** Creates a pnt from the data taken from the database
     * @param p pnt structure, dump of the database */
    Pnt( PntDb p );

    /** Allows conversion from Pnt to PntDb */
    explicit operator PntDb() const;

    /** Writes or update pnt into database */
    void toDb();

private:
    /** Available roles in the company
     * * captain
     * * first office
     * * flight engineer */
    enum class Role { cpt, fo, fe };

    QString m_id;
    QString m_name;
    Role m_role;
    QString m_acftmodel;
    int m_maxfreq;

    /** Converts a role to string */
    static QString role2str( Pnt::Role );

    /** Converts a string to a role */
    static Role str2role( QString s );


    friend QDebug& operator<<(QDebug&, Pnt);
};

#endif     // PNT_H
