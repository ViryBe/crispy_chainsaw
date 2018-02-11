#include "db.h"

QString DATEFMT = "yyyy-mm-dd";

WorkDayStatus str2wds(const QString& s)
{
    WorkDayStatus res = WorkDayStatus::OFF;
    if (s == "off") { res = WorkDayStatus::OFF; }
    else if (s == "office") { res = WorkDayStatus::OFFICE; }
    else if (s == "standby") { res = WorkDayStatus::STANDBY; }
    else if (s == "v1") { res = WorkDayStatus::V1; }
    else if (s == "v2") { res = WorkDayStatus::V2; }
    else if (s == "v3") { res = WorkDayStatus::V3; }
    else { qDebug() << "invalid string not a workdaystatus"; }
    return res;
}

QString wds2str(const WorkDayStatus& wds)
{
    QString res = "";
    if (wds == WorkDayStatus::OFF) {res="off";}
    else if (wds == WorkDayStatus::OFFICE) {res="office";}
    else if (wds == WorkDayStatus::STANDBY){res="standby";}
    else if (wds == WorkDayStatus::V1){res="v1";}
    else if (wds == WorkDayStatus::V2){res="v2";}
    else if (wds == WorkDayStatus::V3){res="v3";}
    else {qDebug() << "invalid wds";}

    return res;
}

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

void DbManager::add_pilot(const QString& name, const QString& role,
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

/*
void DbManager::add_acft_model(const QString& name, const int& freq_max,
        const int& nop, const int& ntot)
{
    QSqlQuery query(m_db);
    query.prepare(
            "INSERT INTO Acft_model (name, freq_max, nop, ntot) VALUES " \
            "(:name, :freq_max, :nop, :ntot)");
    query.bindValue(":name", name);
    query.bindValue(":freq_max", freq_max);
    query.bindValue(":nop", nop);
    query.bindValue(":ntot", ntot);
    if (query.exec()) {
    }
    else {
        qDebug() << "error adding acft model: "
            << query.lastError();
    }
}
*/

void DbManager::add_workday(const QString& date, const WorkDayStatus& st)
{
    QSqlQuery query(m_db);
    query.prepare(
                "INSERT INTO Workday (date, status) VALUES " \
                "(:date, :status)");
    query.bindValue(":date", date);
    query.bindValue(":status", wds2str(st));
    if (query.exec()) {
    }
    else {
        qDebug() << "error adding workday: "
                 << query.lastError();
    }
}

WorkDayStatus DbManager::see_status(QDateTime date, QString pntid)
{
    WorkDayStatus res = WorkDayStatus::OFF;
    QSqlQuery query(m_db);
    query.prepare(
            "SELECT Workday.status FROM Workday INNER JOIN Pnt ON " \
            "Workday.pntid = Pnt.id WHERE " \
            "Pnt.id = :pntid AND Workday.date = :date"
            );
    query.bindValue(":pntid", pntid);
    query.bindValue(":date", date.toString(DATEFMT));
    if (query.exec()) {
        // Result should be unique
        while (query.next()) {
            res = str2wds(query.value(0).toString());
        }
    }
    else {
        qDebug() << "error consulting status: "
            << query.lastError();
    }
    return res;
}

/*
bool DbManager::consult()
{
    bool success = false;
    QSqlQuery query(m_db);
    if (query.exec("SELECT name FROM Pnt")) {
        while (query.next()) {
            auto res = query.value(0).toString();
            qDebug() << res;
        }
        success = true;
    }
    else {
        qDebug() << "error consulting: "
            << query.lastError();
    }
    return success;
}
*/
