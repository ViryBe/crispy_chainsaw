#include "workday.h"

Workday::WorkDayStatus Workday::str2wds( const QString& s )
{
    Workday::WorkDayStatus res = Workday::WorkDayStatus::off;
    if ( s == "off" ) {
        res = Workday::WorkDayStatus::off;
    } else if ( s == "office" ) {
        res = Workday::WorkDayStatus::office;
    } else if ( s == "standby" ) {
        res = Workday::WorkDayStatus::standby;
    } else if ( s == "v1" ) {
        res = Workday::WorkDayStatus::v1;
    } else if ( s == "v2" ) {
        res = Workday::WorkDayStatus::v2;
    } else if ( s == "v3" ) {
        res = Workday::WorkDayStatus::v3;
    } else {
        throw "invalid worday status";
    }
    return res;
}

QString Workday::wds2str( const Workday::WorkDayStatus& wds )
{
    QString res = "";
    if ( wds == Workday::WorkDayStatus::off ) {
        res = "off";
    } else if ( wds == Workday::WorkDayStatus::office ) {
        res = "office";
    } else if ( wds == Workday::WorkDayStatus::standby ) {
        res = "standby";
    } else if ( wds == Workday::WorkDayStatus::v1 ) {
        res = "v1";
    } else if ( wds == Workday::WorkDayStatus::v2 ) {
        res = "v2";
    } else if ( wds == Workday::WorkDayStatus::v3 ) {
        res = "v3";
    } else {
        qDebug( "invalid wds" );
    }

    return res;
}

Workday::Workday( const QString& pntid, const QDate& date,
                  const QString& status ) :
    m_pntid{pntid}, m_date{date}, m_status{str2wds(status)}
{
}

Workday::Workday( const WorkdayDb& wdb ) :
    m_pntid{wdb.pntid}, m_date{QDate::fromString(wdb.workdate, DATEFMT)},
    m_status{str2wds(wdb.status)}
{
}
