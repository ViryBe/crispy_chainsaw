#ifndef PNT_H
#define PNT_H

#include <QString>

enum Role {CPT, FO, FE};

class Pnt
{
public:
    Pnt(QString name, QString code, Role r, int freq_max = -1);

private:
    QString m_name;
    QString m_code;
    Role m_role;
    int m_maxfreq;
};

#endif // PNT_H
