#include "db.h"

QString DATEFMT = "yyyy-MM-dd";

DbManager _MANAGER = DbManager(
    "/home/gabriel/workspace/vcs/crispy_chainsaw/dummydata/dummy.db" );

DbManager::DbManager( const QString& path )
{
    m_db = QSqlDatabase::addDatabase( "QSQLITE" );
    m_db.setDatabaseName( path );

    if ( !m_db.open() ) {
        qDebug() << "error opening db: " << path;
    } else {
        qDebug() << "using database: " << path;
    }
}

void DbManager::addPilot(
    const QString& name, const QString& role, int freq_max )
{
    QSqlQuery query( m_db );
    QString qustr = "INSERT INTO Pnt (name, role, freq_max) VALUES "
                    "(:name, :role, :freq_max)";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare addPilot: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":name", name );
    query.bindValue( ":role", role );
    query.bindValue( ":freq_max", freq_max );
    if ( query.exec() ) {
    } else {
        qDebug() << "exec addPilot: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
}

void DbManager::addWorkday(
    const QDate& date, const QString& st, const QString& pntid )
{
    QString strdate = date.toString( DATEFMT );
    QSqlQuery query( m_db );
    QString qustr = "INSERT INTO Workday (date, status, pntid) VALUES "
                    "(:date, :status, :pntid)";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare addWorkday: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":date", strdate );
    query.bindValue( ":status", st );
    query.bindValue( ":pntid", pntid );
    if ( query.exec() ) {
    } else {
        qDebug() << "exec addWorkday: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
}

void DbManager::addWorkday( const WorkdayDb& wd )
{
    QDate wdate = QDate::fromString( wd.workdate, DATEFMT );
    addWorkday( wdate, wd.status, wd.pntid );
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
    query.bindValue( ":pntid", pntid );
    query.bindValue( ":date", QString( date.toString( DATEFMT ) ) );
    if ( query.exec() ) {
        // Result should be unique
        while ( query.next() ) {
            res = query.value( 0 ).toString();
        }
    } else {
        qDebug() << "exec statusOfPnt: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    return res;
}

std::vector<QString> DbManager::getPnts()
{
    std::vector<QString> pnts;
    QSqlQuery query( m_db );
    QString qustr = "SELECT id FROM Pnt";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getPnts:" << query.lastError();
    }
    if ( query.exec() ) {
        while ( query.next() ) {
            pnts.push_back( QString( query.value( 0 ).toString() ) );
        }
    } else {
        qDebug() << "exec getPnts: " << query.lastError();
    }
    return pnts;
}

PntDb DbManager::getPnt( QString pntid )
{
    PntDb pnt;
    QSqlQuery query( m_db );
    QString qustr = "SELECT id, role, freq_max, acft_modelname, flightnb FROM "
                    "Pnt WHERE id = :id";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getPnt: " << query.lastError()
                 << "\n request: " << qustr;
    }
    query.bindValue( ":id", pntid );
    if ( query.exec() ) {
        query.next();
        pnt.id = query.value( 0 ).toString();
        pnt.role = query.value( 1 ).toString();
        pnt.freq_max = query.value( 2 ).toInt();
        pnt.acft_modelname = query.value( 3 ).toString();
        pnt.flightnb = query.value( 4 ).toInt();
    } else {
        qDebug() << "exec getPnt: " << query.lastError();
    }
    return pnt;
}

std::vector<QString> DbManager::getPnts( const QString& acft_model )
{
    std::vector<QString> pnts;
    QSqlQuery query( m_db );
    QString qustr = "SELECT id FROM Pnt WHERE "
                    "acft_modelname = :amod";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getPnts: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":amod", acft_model );
    if ( query.exec() ) {
        while ( query.next() ) {
            pnts.push_back( QString( query.value( 0 ).toString() ) );
        }
    } else {
        qDebug() << "exec getPnts: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    return pnts;
}

std::vector<QString> DbManager::getPnts(
    const QString& model, const QString& role )
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
            pnts.push_back( QString( query.value( 0 ).toString() ) );
        }
    } else {
        qDebug() << "exec getPnts: " << query.lastError();
    }
    return pnts;
}

std::vector<QString> DbManager::getPnts( const QString& model,
    const QString& role, const QDate& date, const QString& status )
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
    query.bindValue( ":role", role );
    query.bindValue( ":amod", model );
    query.bindValue( ":status", status );
    query.bindValue( ":date", date.toString( DATEFMT ) );
    if ( query.exec() ) {
        while ( query.next() ) {
            pnts.push_back( QString( query.value( 0 ).toString() ) );
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
    query.bindValue( ":date", d.toString( DATEFMT ) );
    query.bindValue( ":role", r );
    query.bindValue( ":mod", m );
    if ( query.exec() ) {
        while ( query.next() ) {
            pnts.push_back( QString( query.value( 0 ).toString() ) );
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
        "SELECT (name, freq_max, crew, nop, ntot) FROM Acft_model WHERE "
        "name LIKE :n";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare getAcftModel: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":n", name );
    if ( query.exec() ) {
        query.next();

        acftmod.name = query.value( 0 ).toString();
        acftmod.freq_max = query.value( 1 ).toInt();
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
