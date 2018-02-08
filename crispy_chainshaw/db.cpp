#include <iostream>
#include <ctime>
#include <QtSql>

class DbManager
{
	public:
		DbManager(const QString& path);
		bool add_species(const QString&);
		bool consult();
	private:
		QSqlDatabase m_db;
};

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

bool DbManager::add_pilot(const QString& name, const QString& role,
		const QInt freq_max)
{
	bool success = false;
	QSqlQuery query(m_db);
	query.prepare(
			"INSERT INTO Pnt (name, role, freq_max) VALUES " \
			"(:name, :role, :freq_max)");
	query.bindValue(":name", name);
	query.bindValue(":role", role);
	query.bindValue(":freq_max", freq_max);
	if (query.exec()) {
		success = true;
	}
	else {
		qDebug() << "error adding species: "
			<< query.lastError();
	}
	return success;
}

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
