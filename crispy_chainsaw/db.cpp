#include "db.h"

QString DATEFMT = "yyyy-MM-dd";

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error, connection with db failed";
    }
    else
    {
        qDebug() << m_db.tables();
        qDebug() << "Database connection ok";
    }
}

void DbManager::addPilot(const QString& name, const QString& role,
    int freq_max)
{
    QSqlQuery query(m_db);
    query.prepare(
            "INSERT INTO Pnt (name, role, freq_max) VALUES " \
            "(:name, :role, :freq_max)");
    query.bindValue(":name", name);
    query.bindValue(":role", role);
    query.bindValue(":freq_max", freq_max);
    if (query.exec()) {
    }
    else {
        qDebug() << "error adding pilot: "
            << query.lastError();
    }
}

void DbManager::addWorkday(const QDate& date, const QString& st,
                           const QString& pntid)
{
    QString strdate = date.toString(DATEFMT);
    QSqlQuery query(m_db);
    query.prepare(
                "INSERT INTO Workday (date, status, pntid) VALUES "
                "(:date, :status, :pntid)");
    query.bindValue(":date", strdate);
    query.bindValue(":status", st);
    query.bindValue(":pntid", pntid);
    if (query.exec()) {
    }
    else {
        qDebug() << "error adding workday: "
                 << query.lastError();
    }
}

void DbManager::addWorkday(const WorkdayDb& wd)
{
    QDate wdate = QDate::fromString(wd.workdate, DATEFMT);
    addWorkday(wdate, wd.status, wd.pntid);
}

QString DbManager::statusOfPnt(QDate date, QString pntid)
{
    QString res = "";
    QSqlQuery query(m_db);
    QString qustr =
            "SELECT Workday.status FROM Workday INNER JOIN Pnt ON "
            "Workday.pntid = Pnt.id WHERE "
            "Pnt.id = :pntid AND Workday.workdate = :date";
    if (!query.prepare(qustr)) {
        qDebug() << "prepare failed";
    }
    QString dateqst = date.toString(DATEFMT);
    query.bindValue(":pntid", pntid);
    query.bindValue(":date", QString(date.toString(DATEFMT)));
    if (query.exec()) {
        // Result should be unique
        while (query.next()) {
            res = query.value(0).toString();
        }
    }
    else {
        qDebug() << "error consulting status: "
            << query.lastError();
    }
    return res;
}

std::vector<QString> DbManager::getPnts(const QString& acft_model)
{
    std::vector<QString> pnts;
    QSqlQuery query(m_db);
    QString qustr =
            "SELECT Pnt.id FROM Pnt INNER JOIN Acft_model ON "
            "Pnt.acft_modelid = Acft_model.id WHERE "
            "Acft_model.name LIKE :amod";
    if (!query.prepare(qustr)) {
        qDebug () << "pilots of model prepare failed";
    }
    query.bindValue(":amod", acft_model);
    if (query.exec()) {
        while (query.next()) {
            pnts.push_back(QString(query.value(0).toString()));
        }
    }
    else {
        qDebug() << "error retrieving pilots for aircraft model" + acft_model;
    }
    return pnts;
}

std::vector<QString> DbManager::getPnts(
        const QString& model, const QString& role, const QDate& date,
        const QString& status)
{
    std::vector<QString> pnts;
    QSqlQuery query(m_db);
    QString qustr =
            "SELECT Pnt.id FROM Pnt, Acft_model, Workday WHERE "
            "Pnt.acft_modelid = Acft_model.id AND "
            "Workday.pntid = Pnt.id AND "
            "Workday.status LIKE :status AND "
            "Pnt.status LIKE :role AND "
            "Acft_model.name LIKE :amod";

    if (!query.prepare(qustr)) {
        qDebug() << "error harvesting available pilots\n";
    }
    query.bindValue(":role", role);
    query.bindValue(":amod", model);
    query.bindValue(":status", status);
    if (query.exec()) {
        while (query.next()) {
            pnts.push_back(QString(query.value(0).toString()));
        }
    }
    else {
        qDebug() << "error retrieving " << role
                 << " available on the " << date.toString(DATEFMT)
                 << " for model " << model;
    }
    return pnts;
}

bool DbManager::test()
{
    bool success = true;
    QDate dummydate = QDate(2018, 2, 10);
    QString dummyid = "ag";
    QString exp_status = "off";
    QString obtained_status = statusOfPnt(dummydate, dummyid);
    success &= obtained_status == exp_status;
    qDebug() << "Obtained status: " + obtained_status;

    QString dummymodel = "a";
    std::vector<QString> dummy_pnts_moda = getPnts(dummymodel);
    for (auto const& pm: dummy_pnts_moda) {
        success &= pm == QString("ag") || pm == QString("cr");
    }
    return success;
}
