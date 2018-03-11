#include "pnt.h"

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
