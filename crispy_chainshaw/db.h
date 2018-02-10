#ifndef DB_H
#define DB_H

#include <QtSql>
#include <iostream>

/// Type used to describe the day of a pilot
enum WorkDayStatus {OFF, STANDBY, OFFICE, V1, V2, V3};

/// Converts a string to a WorkDayStatus
WorkDayStatus str2wds(const QString&);

/// Interacts with the database
class DbManager
{
	public:
		DbManager(const QString&);
		void add_pilot(const QString&, const QString&, const int&);
		void add_acft_model(const QString&, const int&, const int&,
				const int&);
		WorkDayStatus see_status(const QDateTime, const int);
	private:
		QSqlDatabase m_db;
};

#endif
