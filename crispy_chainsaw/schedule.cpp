#include "schedule.h"

ScheduleInstance::ScheduleInstance( const AcftModel& _model,
    QString _role, QDate dbeg, QDate dend )
{

    m_model = _model;
    m_role = _role;

    // Number of variables = freq * number of days
    n = m_model.getFreqMax() * ( int ) dbeg.daysTo( dend );

    // Init domains
    domain.resize( n + 1 );
    current_domain.resize( n + 1 );
    QDate today = dbeg;
    QString fl_st;
    for ( int i = 1; i <= n; i++ ) {
        std::vector<QString> crewmem;
        // Retrieve available pilots
        fl_st = (int) ( (i - 1) / m_model.getFreqMax() );
        today.addDays( ( i - 1 ) % m_model.getFreqMax() );
        if (_MANAGER.workProvided(today, m_model.getName(),
                                  m_role, fl_st)) {
            crewmem = { _MANAGER.getWorkingPnt(today, m_model.getName(),
                        m_role, fl_st) };
        }
        else {
            crewmem = _MANAGER.getIdlePnts(
                        m_model.getName(), m_role, today );
        }

        domain[ i ].resize( crewmem.size() );
        domain[ i ] = crewmem;
        current_domain[ i ].resize( crewmem.size() );
        current_domain[ i ] = crewmem;
    }

    v.resize( n + 1 );

    // Init flight number per pilot and sort domains
    std::vector<QString> pntids =
        _MANAGER.getPnts( m_model.getName(), _role );
    for ( QString pid : pntids ) {
        flightnb.emplace(
            std::make_pair( pid, _MANAGER.getPnt( pid ).flightnb ) );
    }
    sort_domains();

    // create schedule
    bcssp( n, Status::unknown );
}

ScheduleInstance::ScheduleInstance(
    const AcftModel& _model, QString _role, QDate dbeg )
{
    ScheduleInstance( _model, _role, dbeg, dbeg.addDays( 15 ) );
}

int ScheduleInstance::bt_label( int i )
{
    consistent = false;
    auto cd_copy = current_domain[ i ];
    for ( unsigned int j = 0; j < cd_copy.size() && !consistent; j++ ) {
        // Update value vector and flights count
        try {
            // Remove previously planned flight
            flightnb.at( v[ i ] ) = std::max( flightnb.at( v[ i ] ) - 1, 0 );
        } catch ( std::out_of_range oor ) {
            // Happens when value not yet instantiated (v[i] not filled)
        }
        v[ i ] = cd_copy[ j ];
        flightnb.at( v[ i ] )++; // Add newly planned flight

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
    if (     // If two flights happen the same day...
        ( int ) ( ( i - 1 ) / m_model.getFreqMax() ) ==
        ( int ) ( ( j - 1 ) / m_model.getFreqMax() ) ) {
        // ...ensure pilots are different
        valid &= v[ i ] != v[j];
    }
    return valid;
}

void ScheduleInstance::updateDb( DbManager dbm )
{
    // For each variable, update related workday
    for ( int i = 1; i <= n; i++ ) {
        QDate date =
            m_startdate.addDays( ( int ) ( ( i - 1 ) / m_model.getFreqMax() ) );
        QString flightno = "v" + ( ( i - 1 ) % m_model.getFreqMax() + 1 );
        QString pntid = v[ i ];

        dbm.addWorkday( date, flightno, pntid );
    }
}

void ScheduleInstance::sort_domains()
{
    auto cmp = [this]( QString p1, QString p2 ) {
        return flightnb.find( p1 )->second < flightnb.find( p2 )->second;
    };

    for ( int i = 1; i <= n; i++ ) {
        std::sort( domain[ i ].begin(), domain[ i ].end(), cmp );
        std::sort(
            current_domain[ i ].begin(), current_domain[ i ].end(), cmp );
    }
}

void ScheduleInstance::print()
{
    int day;
    int flight_no;
    for ( int i = 1; i <= n; i++ ) {
        day = 1 + ( int ) ( ( i - 1 ) / m_model.getFreqMax() );
        flight_no = ( i - 1 ) % m_model.getFreqMax();

        qDebug() << "day: " << day << ";"
                 << "flight number: " << flight_no << ";"
                 << "pnt: " << v[ i ];
    }
}

bool ScheduleInstance::test()
{
    QString role = "cpt";
    AcftModel mod = AcftModel( "a", 2, 2 );

    ScheduleInstance si = ScheduleInstance(
        mod, role, QDate::currentDate(), QDate::currentDate().addDays( 2 ) );
    si.print();
    return true;
}
