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

void DbManager::add_workday(const QString& date, const QString& st)
{
    QSqlQuery query(m_db);
    query.prepare(
                "INSERT INTO Workday (date, status) VALUES " \
                "(:date, :status)");
    query.bindValue(":date", date);
    query.bindValue(":status", st);
    if (query.exec()) {
    }
    else {
        qDebug() << "error adding workday: "
                 << query.lastError();
    }
}

QString DbManager::see_status(QDate date, QString pntid)
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
    qDebug() << dateqst;
    query.bindValue(":pntid", pntid);
    query.bindValue(":date", QString(date.toString(DATEFMT)));
    if (query.exec()) {
        // Result should be unique
        while (query.next()) {
            res = query.value(0).toString();
            qDebug() << res;
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


/*
int DbManager::getFlightTimePilot(QString code_pilot, int month)
// return le nombre d'h de vol pour le pilot "code pilot" pour le mois month
{
    return 0;
}
*/

bool DbManager::test()
{
    QDate dummydate = QDate(2018, 2, 10);
    QString dummyid = "ag";
    QString exp_status = "off";
    QString obtained_status = see_status(dummydate, dummyid);
    qDebug() << "Obtained status: " + obtained_status;
    return obtained_status == exp_status;
}
