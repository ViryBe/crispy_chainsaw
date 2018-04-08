#include "db.h"


void DbManager::init( const QString& path )
{
    m_db = QSqlDatabase::addDatabase( "QSQLITE" );
    m_db.setDatabaseName( path );

    if ( !m_db.open() ) {
        qDebug() << "error opening db: " << path;
    } else {
        qDebug() << "using database: " << path;
    }
}

void DbManager::addPnt( PntDb pdb )
{
    QSqlQuery query( m_db );
    QString qustr =
        "INSERT INTO Pnt "
        "(id, name, role, acft_modelname, maxfreq) VALUES "
        "(:id, :name, :role, :amod, :mf)";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare addPnt: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":id", pdb.id.toLower() );
    query.bindValue( ":name", pdb.name.toLower() );
    query.bindValue( ":role", pdb.role.toLower() );
    query.bindValue( ":mf", pdb.maxfreq );
    query.bindValue( ":amod", pdb.acft_modelname.toLower() );
    if ( query.exec() ) {
    } else {
        qDebug() << "exec addPnt: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
}

void DbManager::modifyPnt( PntDb pdb )
{
    QSqlQuery query( m_db );
    QString qustr = "UPDATE Pnt SET "
                    "(name, role, acft_modelname, maxfreq) = "
                    "(:name, :role, :amod, :mf) WHERE "
                    "id = :id";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare modify: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":id", pdb.id.toLower() );
    query.bindValue( ":name", pdb.name.toLower() );
    query.bindValue( ":role", pdb.role.toLower() );
    query.bindValue( ":mf", pdb.maxfreq );
    query.bindValue( ":amod", pdb.acft_modelname.toLower() );
    if ( query.exec() ) {
    } else {
        qDebug() << "exec modifyPilot: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
}

void DbManager::updatePnt( PntDb pdb )
{
    QSqlQuery query( m_db );
    QString qustr = "SELECT COUNT(id) FROM Pnt WHERE id = :id";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare updatePnt: " << query.lastError();
    }
    query.bindValue( ":id", pdb.id.toLower() );
    if ( query.exec() ) {
        query.first();
        if ( query.value( 0 ).toInt() == 0 ) {
            addPnt( pdb );
        } else {
            modifyPnt( pdb );
        }
    } else {
        qDebug() << "exec updatePnt: " << query.lastError();
    }
}

void DbManager::deletePnt( QString pid )
{
    QSqlQuery query( m_db );
    QString qustr = "DELETE FROM Pnt WHERE id = :id";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare deletePnt: " << query.lastError();
    }
    query.bindValue( ":id", pid.toLower() );
    if ( query.exec() ) {
    } else
        qDebug() << "exec deletePnt: " << query.lastError();
}

void DbManager::addWorkday(
    const QDate& date, const QString& st, const QString& pntid )
{
    QString strdate = date.toString( kDATEFMT );
    QSqlQuery query( m_db );
    QString qustr = "INSERT INTO Workday (date, status, pntid) VALUES "
                    "(:date, :status, :pntid)";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare addWorkday: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":date", strdate );
    query.bindValue( ":status", st.toLower() );
    query.bindValue( ":pntid", pntid.toLower() );
    if ( query.exec() ) {
    } else {
        qDebug() << "exec addWorkday: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
}

void DbManager::addWorkday( const WorkdayDb& wd )
{
    addWorkday( wd.workdate, wd.status, wd.pntid );
}

void DbManager::deleteWorkday( QDate date, QString pntid )
{
    QSqlQuery query( m_db );
    QString qustr = "DELETE FROM Workday WHERE "
                    "workdate LIKE :date AND "
                    "pntid LIKE :id";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare deleteWorkday: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":date", date.toString( kDATEFMT ) );
    query.bindValue( ":id", pntid );
    if ( query.exec() ) {
    } else {
        qDebug() << "exec deleteWorkday: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
}

std::vector<WorkdayDb> DbManager::getWorkdays( QString pntid,
        QDate from, QDate to, QString status)
{
    std::vector<WorkdayDb> rslt;
    QSqlQuery query( m_db );
    QString qustr = "SELECT workdate, status, pntid, forced FROM "
            "Workday INNER JOIN Pnt ON Workday.pntid = Pnt.id WHERE "
            "pntid LIKE :pid AND "
            "status LIKE :st AND "
            "workdate >= :from AND workdate <= :to";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getWorkdays: " <<  query.lastError();
    }
    query.bindValue( ":pid", pntid);
    query.bindValue( ":st", status);
    query.bindValue( ":from", from);
    query.bindValue( ":to", to);
    if ( query.exec() ) {
        while ( query.next() ) {
            WorkdayDb wd;
            wd.workdate = QDate::fromString(query.value(0).toString(), kDATEFMT);
            wd.pntid = query.value(1).toString().toLower();
            wd.status = query.value(2).toString().toUpper();
            wd.forced = query.value(3).toBool();
            rslt.push_back(wd);
        }
    } else {
        qDebug() << "getWorkdayserr: " << query.lastError();
    }
    return rslt;
}

bool DbManager::workForced( const QDate& date, const QString& model,
    const QString& role, const QString& status )
{
    int nrslt = 0;
    QSqlQuery query( m_db );
    QString qustr = "SELECT COUNT(Pnt.id) FROM Pnt INNER JOIN Workday ON "
                    "Pnt.id = Workday.pntid WHERE "
                    "Workday.forced = 1 AND "
                    "Workday.workdate LIKE :date AND "
                    "Workday.status LIKE :status AND "
                    "Pnt.role LIKE :role AND "
                    "Pnt.acft_modelname LIKE :mod";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare workForced: " << query.lastError();
    }
    query.bindValue( ":date", date.toString( kDATEFMT ) );
    query.bindValue( ":status", status.toLower() );
    query.bindValue( ":role", role.toLower() );
    query.bindValue( ":mod", model.toLower() );
    if ( query.exec() ) {
        query.first();
        nrslt = query.value( 0 ).toInt();
    } else {
        qDebug() << "exec workForced: " << query.lastError();
    }
    return nrslt > 0;
}

QDate DbManager::getLastScheduledDay()
{
    QDate lastday;
    QSqlQuery query( m_db );
    QString qustr = "SELECT MAX(workdate) FROM Workday WHERE forced = 0";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getlastschedule: " << query.lastError();
    }
    if ( query.exec() ) {
        query.first();
        lastday = QDate::fromString( query.value( 0 ).toString(), kDATEFMT );
    } else {
        qDebug() << "exec getlastschedule: " << query.lastError();
    }
    return lastday;
}

std::vector<WorkdayDb> DbManager::getAutomaticallySetWorkdays(
    QDate from, QDate to, QString role, QString amod )
{
    std::vector<WorkdayDb> workdays;
    QSqlQuery query( m_db );
    QString qustr = "SELECT (workdate, status, pntid) FROM Workday, Pnt WHERE "
                    "pntid = Pnt.id AND "
                    "role LIKE :role AND "
                    "acft_modelname LIKE :mod AND "
                    "workdate <= :to AND "
                    "workdate >= :from AND "
                    "forced = 0";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getautosetwdays: " << query.lastError();
    }
    query.bindValue( ":role", role.toLower() );
    query.bindValue( ":mod", amod.toLower() );
    query.bindValue( ":from", from.toString( kDATEFMT ) );
    query.bindValue( ":to", to.toString( kDATEFMT ) );
    if ( query.exec() ) {
        while ( query.next() ) {
            WorkdayDb wd;
            wd.pntid = query.value( 2 ).toString().toUpper();
            wd.workdate = query.value( 0 ).toDate();
            wd.status = query.value( 1 ).toString().toLower();
            workdays.push_back( wd );
        }
    } else {
        qDebug() << "exec getautosetwd: " << query.lastError();
    }
    return workdays;
}

QString DbManager::getWorkingPnt( const QDate& date, const QString& model,
    const QString& role, const QString& status )
{
    QString pntid;
    QSqlQuery query( m_db );
    QString qustr = "SELECT Pnt.id FROM Pnt INNER JOIN Workday ON "
                    "Pnt.id = Workday.pntid WHERE "
                    "Workday.workdate LIKE :date AND "
                    "Workday.status LIKE :status AND "
                    "Pnt.role LIKE :role AND "
                    "Pnt.acft_modelname LIKE :mod";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getWorkingPnt: " << query.lastError();
    }
    query.bindValue( ":date", date.toString( kDATEFMT ) );
    query.bindValue( ":status", status.toLower() );
    query.bindValue( ":role", role.toLower() );
    query.bindValue( ":mod", model.toLower() );
    if ( query.exec() ) {
        query.first();
        pntid = QString( query.value( 0 ).toString() );
    } else {
        qDebug() << "exec getWorkingPnt: " << query.lastError();
    }
    return pntid;
}

QString DbManager::statusOfPnt( QDate date, QString pntid )
{
    QString res = "";
    QSqlQuery query( m_db );
    QString qustr = "SELECT Workday.status FROM Workday INNER JOIN Pnt ON "
                    "Workday.pntid = Pnt.id WHERE "
                    "Pnt.id = :pntid AND Workday.workdate = :date";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare statusOfPnt: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":pntid", pntid.toLower() );
    query.bindValue( ":date", QString( date.toString( kDATEFMT ) ) );
    if ( query.exec() ) {
        // Result should be unique
        query.first();
        res = query.value( 0 ).toString();
    } else {
        qDebug() << "exec statusOfPnt: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    return res;
}

int DbManager::cardInactiveDays( QString id, QDate begin, QDate end )
{
    int card = 0;
    int numberofdays = begin.daysTo( end );
    QSqlQuery query( m_db );
    QString qustr = "SELECT COUNT(workdate) FROM "
                    "Workday INNER JOIN Pnt ON Pnt.id = Workday.pntid WHERE "
                    "Pnt.id LIKE :pntid AND "
                    "Workday.workdate BETWEEN :db AND :de";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare cardInactiveDays: " << query.lastError();
    }
    query.bindValue( ":pntid", id.toLower() );
    query.bindValue( ":db", begin.toString( kDATEFMT ) );
    query.bindValue( ":de", end.toString( kDATEFMT ) );
    if ( query.exec() ) {
        query.first();
        int nwd = query.value( 0 ).toInt();
        card = numberofdays - nwd;
    } else {
        qDebug() << "exec cardInactiveDays: " << query.lastError();
    }
    return card;
}

PntDb DbManager::getPnt( QString pntid )
{
    PntDb pnt;
    QSqlQuery query( m_db );
    QString qustr = "SELECT id, name, role, maxfreq, acft_modelname "
                    "FROM Pnt WHERE id = :id";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getPnt: " << query.lastError()
                 << "\n request: " << qustr;
    }
    query.bindValue( ":id", pntid.toLower() );
    if ( query.exec() ) {
        query.first();
        pnt.id = query.value( 0 ).toString().toUpper();
        pnt.name = capitalizeFirstLetters( query.value( 1 ).toString() );
        pnt.role = query.value( 2 ).toString().toLower();
        pnt.maxfreq = query.value( 3 ).toInt();
        pnt.acft_modelname = query.value( 4 ).toString();
    } else {
        qDebug() << "exec getPnt: " << query.lastError();
    }
    return pnt;
}

std::vector<QString> DbManager::getPnts( QString model, QString role )
{
    std::vector<QString> pnts;
    QSqlQuery query( m_db );
    QString qustr = "SELECT id FROM Pnt WHERE "
                    "acft_modelname LIKE :amod AND "
                    "role LIKE :role";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getPnts: " << query.lastError();
    }
    query.bindValue( ":amod", model );
    query.bindValue( ":role", role );
    if ( query.exec() ) {
        while ( query.next() ) {
            pnts.push_back( QString( query.value( 0 ).toString() ).toUpper() );
        }
    } else {
        qDebug() << "exec getPnts: " << query.lastError();
    }
    return pnts;
}

std::vector<QString>
DbManager::getPnts( QDate date, QString status, QString model, QString role )
{
    std::vector<QString> pnts;
    QSqlQuery query( m_db );
    QString qustr = "SELECT Pnt.id FROM Pnt, Acft_model, Workday WHERE "
                    "Pnt.acft_modelname = Acft_model.name AND "
                    "Workday.pntid = Pnt.id AND "
                    "Workday.workdate LIKE :date AND "
                    "Workday.status LIKE :status AND "
                    "Pnt.role LIKE :role AND "
                    "Acft_model.name LIKE :amod";

    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getPnts: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":role", role.toLower() );
    query.bindValue( ":amod", model.toLower() );
    query.bindValue( ":status", status.toLower() );
    query.bindValue( ":date", date.toString( kDATEFMT ) );
    if ( query.exec() ) {
        while ( query.next() ) {
            pnts.push_back( QString( query.value( 0 ).toString() ).toUpper() );
        }
    } else {
        qDebug() << "exec getPnts: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    return pnts;
}

std::vector<QString> DbManager::getIdlePnts(
    const QString& m, const QString& r, const QDate& d )
{
    std::vector<QString> pnts;
    QSqlQuery query( m_db );
    QString qustr = "SELECT id FROM Pnt WHERE "
                    "role LIKE :role AND acft_modelname LIKE :mod AND "
                    "id NOT IN ("
                    "SELECT DISTINCT Pnt.id FROM Pnt INNER JOIN Workday ON "
                    "Pnt.id = Workday.pntid WHERE "
                    "Workday.workdate LIKE :date)";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getIdlePnts: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":date", d.toString( kDATEFMT ) );
    query.bindValue( ":role", r.toLower() );
    query.bindValue( ":mod", m.toLower() );
    if ( query.exec() ) {
        while ( query.next() ) {
            pnts.push_back( QString( query.value( 0 ).toString() ).toUpper() );
        }
    } else {
        qDebug() << "exec getIdlePnts: " << query.lastError()
                 << "\nrequest: " << qustr;
    }
    return pnts;
}

AcftModelDb DbManager::getAcftModel( const QString& name )
{
    AcftModelDb acftmod;
    QSqlQuery query( m_db );
    QString qustr =
        "SELECT (name, maxfreq, crew, nop, ntot) FROM Acft_model WHERE "
        "name LIKE :n";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getAcftModel: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":n", name );
    if ( query.exec() ) {
        query.first();

        acftmod.name = query.value( 0 ).toString();
        acftmod.maxfreq = query.value( 1 ).toInt();
        acftmod.crew = query.value( 2 ).toInt();
        acftmod.nop = query.value( 3 ).toInt();
        acftmod.ntot = query.value( 4 ).toInt();
    } else {
        qDebug() << "exec getAcftModel: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    return acftmod;
}

bool DbManager::test()
{
    bool success = true;
    QDate dummydate = QDate( 2018, 2, 10 );
    QString dummyid = "ag";
    QString exp_status = "off";
    QString obtained_status = statusOfPnt( dummydate, dummyid );
    success &= obtained_status == exp_status;
    qDebug() << "Obtained status: " + obtained_status;

    QString dummymodel = "a";
    std::vector<QString> dummy_pnts_moda = getPnts( dummymodel );
    for ( auto const& pm : dummy_pnts_moda ) {
        success &= pm == QString( "ag" ) || pm == QString( "cr" );
    }
    return success;
}

QString DbManager::capitalizeFirstLetters( QString name )
{
    QStringList parts = name.split( " " );
    QString res = "";
    for ( QString word : parts ) {
        res += " ";
        std::string sword = word.toStdString();
        std::string cword = "";
        cword.push_back( toupper( sword[ 0 ] ) );
        if ( sword.size() > 1 ) {
            for ( char c : sword.substr( 1 ) ) {
                cword.push_back( c );
            }
        }
        res += QString::fromStdString( cword );
    }
    return res;
}
