#include "schedule.h"

const int kMAXFLIGHTWEEK = 55; ///< Time of flight per week
const int kMAXFLIGHTMONTH = 100; ///< Flight time per month
const int kMAXFLIGHTYEAR = 900; ///< Flight time per year
const int kMAXSERVWEEK = 60; ///< Time of service per week
const int kMAXSERVMONTH = 190; ///< Time of service per month
const int kMINRESTSERV8 = 9; ///< Rest time if less than 8 hours of service
const int kMINRESTSERV89 = 10; ///< Rest time if 8 or 9 hours of service
const int kMINRESTSERV9 = 11; ///< Rest time if more than 9 hours of service
const int kMONTH = 28; ///< Number of days in a month
const int kWEEK = 7; ///< Number of days in a week

ScheduleInstance::ScheduleInstance(
    const AcftModelDb& _model, QString _role, QDate dbeg, QDate dend )
{

    m_model = _model;
    m_role = _role;

    // Number of variables = freq * number of days
    n = m_model.maxfreq * static_cast<int>( dbeg.daysTo( dend ) );

    // Init domains
    domain.resize( n + 1 );
    current_domain.resize( n + 1 );
    QDate today = dbeg;
    QString fl_st;
    for ( int i = 1; i <= n; i++ ) {
        std::vector<QString> crewmem;
        // Retrieve available pilots
        fl_st = ( i - 1 ) / m_model.maxfreq;
        today.addDays( ( i - 1 ) % m_model.maxfreq );
        if ( _MANAGER.workForced( today, m_model.name, m_role, fl_st ) ) {
            crewmem = {
                _MANAGER.getWorkingPnt( today, m_model.name, m_role, fl_st )};
        } else {
            crewmem = _MANAGER.getIdlePnts( m_model.name, m_role, today );
        }

        domain[ i ].resize( crewmem.size() );
        domain[ i ] = crewmem;
        current_domain[ i ].resize( crewmem.size() );
        current_domain[ i ] = crewmem;
    }

    v.resize( n + 1 );

    // Init flight number per pilot and sort domains
    std::vector<QString> pntids = _MANAGER.getPnts( m_model.name, _role );
    for ( auto pid : pntids ) {
        workRegister wr;
        auto year = dbeg.year();
        auto oneyearago = QDate( year - 1, dbeg.month(), dbeg.day() );
        std::vector<WorkdayDb> wds = _MANAGER.getWorkdays( pid, oneyearago,
                                                           dbeg );
        for (auto wd : wds) {
            if (wd.status == "v1" || wd.status == "v2" || wd.status == "v3" ) {
                wr.yearflight += 1;
                wr.monthflight += ( dbeg.daysTo(wd.workdate) <= kMONTH ) ?
                            1 : 0;
                wr.weekflight += ( dbeg.daysTo( wd.workdate ) <= kWEEK ) ?
                            1 : 0;
            } else if ( wd.status == "office" ) {
                wr.yearservice += 1;
                wr.monthservice += ( dbeg.daysTo(wd.workdate) <= kMONTH ) ?
                            1 : 0;
                wr.weekservice += ( dbeg.daysTo( wd.workdate ) <= kWEEK ) ?
                            1 : 0;
            }
        }
        workload.emplace( std::make_pair( pid, wr ) );
    }
    sort_domains();

    // create schedule
    bcssp( n, Status::unknown );
}

ScheduleInstance::ScheduleInstance(
    const AcftModelDb& _model, QString _role, QDate dbeg )
{
    ScheduleInstance( _model, _role, dbeg, dbeg.addDays( 15 ) );
}

int ScheduleInstance::bt_label( int i )
{
    consistent = false;
    auto cd_copy = current_domain[ i ];
    for ( auto j = 0; j < cd_copy.size() && !consistent; j++ ) {
        // Update value vector and flights count
        try {
            // Remove previously planned flight
            workload.at( v[ i ] ).removeFlight();
        } catch ( std::out_of_range ) {
            // Happens when value not yet instantiated (v[i] not filled)
        }
        v[ i ] = cd_copy[ j ];
        workload.at( v[ i ] ).addFlight(); // Add newly planned flight

        consistent = true;
        for ( int h = 1; h < i && consistent; h++ ) {
            consistent = check( i, h );
            if ( !consistent ) {
                current_domain[ i ].erase(
                    std::remove( current_domain[ i ].begin(),
                        current_domain[ i ].end(), v[ i ] ) );
            }
        }
    }
    return consistent ? ( i + 1 ) : i;
}

int ScheduleInstance::bt_unlabel( int i )
{
    int h = i - 1;
    current_domain[ i ] = domain[ i ];

    if ( current_domain[ h ].size() > 0 ) {
        auto it = std::find(
            current_domain[ h ].begin(), current_domain[ h ].end(), v[ h ] );
        current_domain[ h ].erase( it );
    }
    consistent = current_domain[ h ].size() > 0;
    return h;
}

void ScheduleInstance::bcssp( int n, Status status )
{
    consistent = true;
    int i = 1;
    while ( status == Status::unknown ) {
        sort_domains();
        if ( consistent ) {
            i = bt_label( i );
        } else {
            i = bt_unlabel( i );
        }
        if ( i > n ) {
            status = Status::solution;
        } else if ( i == 0 ) {
            status = Status::impossible;
            qDebug() << "impossible";
        }
    }
}

bool ScheduleInstance::check( int i, int j )
{
    bool valid = true;
    // Check for legal times
    auto wr = workload.at( v[ i ] );
    if ( !wr.check() && v[ j ] == v[ i ] ) {
        // Even if times are not respected, only days requiring this pnt should
        // be blamed, not others. If legal constraints are not respected but
        // v[j] does not involve pilot of v[i], true is returned nonetheless as
        // the two workdays do not show incompatibilites.
        valid &= false;
    }
    if (     // If two flights happen the same day...
        ( ( i - 1 ) / m_model.maxfreq ) == ( ( j - 1 ) / m_model.maxfreq ) ) {
        // ...ensure pilots are different
        valid &= v[ i ] != v[ j ];
    }
    return valid;
}

void ScheduleInstance::recomputeFrom(
    const AcftModelDb& amod, QString role, QDate dfrom )
{
    // First clean the schedule
    QDate to = _MANAGER.getLastScheduledDay();
    std::vector<WorkdayDb> autosetdays =
        _MANAGER.getAutomaticallySetWorkdays( dfrom, to, role, amod.name );
    for ( WorkdayDb wday : autosetdays ) {
        _MANAGER.deleteWorkday( wday.workdate, wday.pntid );
    }
    ScheduleInstance rescheduled = ScheduleInstance( amod, role, dfrom, to );
    rescheduled.updateDb( _MANAGER );
}

void ScheduleInstance::updateDb( DbManager dbm )
{
    // For each variable, update related workday
    for ( int i = 1; i <= n; i++ ) {
        QDate date = m_startdate.addDays( ( i - 1 ) / m_model.maxfreq );
        QString flightno = "v" + ( ( i - 1 ) % m_model.maxfreq + 1 );
        QString pntid = v[ i ];

        dbm.addWorkday( date, flightno, pntid );
    }
}

bool ScheduleInstance::workRegister::operator<=( const workRegister& wr )
{
    if ( weekflight != wr.weekflight ) {
        return weekflight < wr.weekflight;
    } else if ( monthflight != wr.monthflight ) {
        return monthflight < wr.monthflight;
    } else if ( yearflight != wr.yearflight ) {
        return yearflight < wr.yearflight;
    } else if ( weekservice != wr.weekservice ) {
        return weekservice < wr.weekservice;
    } else if ( monthservice != wr.monthservice ) {
        return monthservice < wr.monthservice;
    } else {
        return yearservice <= wr.yearservice;
    }
}

void ScheduleInstance::workRegister::addFlight()
{
    ++yearflight;
    ++monthflight;
    ++weekflight;
}

void ScheduleInstance::workRegister::removeFlight()
{
    yearflight = std::max( yearflight - 1, 0 );
    monthflight = std::max( monthflight - 1, 0 );
    weekflight = std::max( weekflight - 1, 0 );
}

bool ScheduleInstance::workRegister::check()
{
    return weekflight <= kMAXFLIGHTWEEK &&
            monthflight <= kMAXFLIGHTMONTH &&
            yearflight <= kMAXFLIGHTYEAR &&
            weekservice <= kMAXSERVWEEK &&
            monthservice <= kMAXSERVMONTH;
}

void ScheduleInstance::sort_domains()
{
    auto cmp = [this]( QString p1, QString p2 ) {
        return workload.find( p1 )->second <= workload.find( p2 )->second;
    };

    for ( int i = 1; i <= n; i++ ) {
        std::sort( domain[ i ].begin(), domain[ i ].end(), cmp );
        std::sort(
            current_domain[ i ].begin(), current_domain[ i ].end(), cmp );
    }
}

void ScheduleInstance::print()
{
    for ( int i = 1; i <= n; i++ ) {
        int day;
        int flight_no;
        day = 1 + ( i - 1 ) / m_model.maxfreq;
        flight_no = ( i - 1 ) % m_model.maxfreq;

        qDebug() << "day: " << day << ";"
                 << "flight number: " << flight_no << ";"
                 << "pnt: " << v[ i ];
    }
}

bool ScheduleInstance::test()
{
    QString role = "cpt";
    AcftModelDb mod;
    mod.name = "a";
    mod.maxfreq = 2;
    mod.crew = 2;

    ScheduleInstance si = ScheduleInstance(
        mod, role, QDate::currentDate(), QDate::currentDate().addDays( 2 ) );
    si.print();
    return true;
}
