#include "db.h"

QString DATEFMT = "yyyy-MM-dd";

DbManager _MANAGER = DbManager("C:/Users/clrco/Documents/Projets/crispy_chainsaw/dummydata/dummy.db" );

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

void DbManager::addPnt( PntDb pdb )
{
    QSqlQuery query( m_db );
    QString qustr =
        "INSERT INTO Pnt "
        "(id, name, role, acft_modelname, flightnb, maxfreq) VALUES "
        "(:id, :name, :role, :amod, :fnb, :mf)";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare addPnt: " << query.lastError()
                 << "\nrequest:" << qustr;
    }
    query.bindValue( ":id", pdb.id.toLower() );
    query.bindValue( ":name", pdb.name.toLower() );
    query.bindValue( ":role", pdb.role.toLower() );
    query.bindValue( ":mf", pdb.maxfreq );
    query.bindValue( ":amod", pdb.acft_modelname.toLower() );
    query.bindValue( ":fnb", pdb.flightnb );
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
                    "(name, role, acft_modelname, flightnb, maxfreq) = "
                    "(:name, :role, :amod, :fnb, :mf) WHERE "
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
    query.bindValue( ":fnb", pdb.flightnb );
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
    if (!query.prepare( qustr ) ) {
        qDebug() << "prepare updatePnt: " << query.lastError();
    }
    query.bindValue(":id", pdb.id.toLower());
    if ( query.exec() ) {
        query.first();
        if (query.value(0).toInt() == 0) {
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
    QString strdate = date.toString( DATEFMT );
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
    QDate wdate = QDate::fromString( wd.workdate, DATEFMT );
    addWorkday( wdate, wd.status, wd.pntid );
}

bool DbManager::workProvided( const QDate& date, const QString& model,
    const QString& role, const QString& status )
{
    int nrslt;
    QSqlQuery query( m_db );
    QString qustr = "SELECT COUNT(Pnt.id) FROM Pnt INNER JOIN Workday ON "
                    "Pnt.id = Workday.pntid WHERE "
                    "Workday.workdate LIKE :date AND "
                    "Workday.status LIKE :status AND "
                    "Pnt.role LIKE :role AND "
                    "Pnt.acft_modelname LIKE :mod";
    if ( !query.prepare( qustr ) ) {
        qDebug() << "prepare workProvided: " << query.lastError();
    }
    query.bindValue( ":date", date.toString( DATEFMT ) );
    query.bindValue( ":status", status.toLower() );
    query.bindValue( ":role", role.toLower() );
    query.bindValue( ":mod", model.toLower() );
    if ( query.exec() ) {
        query.first();
        nrslt = query.value( 0 ).toInt();
    } else {
        qDebug() << "exec workProvided: " << query.lastError();
    }
    return nrslt > 0;
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
    query.bindValue( ":date", date.toString( DATEFMT ) );
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
    query.bindValue( ":date", QString( date.toString( DATEFMT ) ) );
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
            pnts.push_back( QString( query.value( 0 ).toString().toUpper() ) );
        }
    } else {
        qDebug() << "exec getPnts: " << query.lastError();
    }
    return pnts;
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
    query.bindValue( ":db", begin.toString( DATEFMT ) );
    query.bindValue( ":de", end.toString( DATEFMT ) );
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
    QString qustr = "SELECT id, name, role, maxfreq, acft_modelname, flightnb "
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
        pnt.flightnb = query.value( 5 ).toInt();
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
    query.bindValue( ":amod", acft_model.toLower() );
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
            pnts.push_back( QString( query.value( 0 ).toString() ).toUpper() );
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
    query.bindValue( ":role", role.toLower() );
    query.bindValue( ":amod", model.toLower() );
    query.bindValue( ":status", status.toLower() );
    query.bindValue( ":date", date.toString( DATEFMT ) );
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
    query.bindValue( ":date", d.toString( DATEFMT ) );
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

QString DbManager::capitalizeFirstLetters( QString str )
{
    std::regex firstlet( "\\b[a-z]" );
    return QString::fromStdString(
        static_cast<std::string>( std::regex_replace( str.toStdString(),
            firstlet, "\\u&", std::regex_constants::format_sed ) ) );
}
