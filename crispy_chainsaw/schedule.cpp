#include "schedule.h"

const int kMAXFLIGHTWEEK = 55;       ///< Time of flight per week
const int kMAXFLIGHTMONTH = 100;     ///< Flight time per month
const int kMAXFLIGHTYEAR = 900;      ///< Flight time per year
const int kMAXSERVWEEK = 60;         ///< Time of service per week
const int kMAXSERVMONTH = 190;       ///< Time of service per month
const int kMINRESTSERV8 = 9;     ///< Rest time if less than 8 hours of service
const int kMINRESTSERV89 = 10;     ///< Rest time if 8 or 9 hours of service
const int kMINRESTSERV9 = 11;     ///< Rest time if more than 9 hours of service
const int kMONTH = 28;            ///< Number of days in a month
const int kWEEK = 7;              ///< Number of days in a week
const int kYEAR = 365;            ///< Number of days in a year
const float kTIMEPERFLIGHT = 2.5;     ///< Mean time of a flight

ScheduleInstance::ScheduleInstance(
    const AcftModelDb& aModel, QString aRole, QDate dbeg )
{

    mModel = aModel;
    mRole = aRole;
    mStartDate = dbeg;

    // Number of variables = freq * number of days
    n = mModel.maxfreq * static_cast<int>( kWEEK );

    // Init domains
    domain.resize( n + 1 );
    current_domain.resize( n + 1 );
    for ( int i = 1; i <= n; i++ ) {
        std::vector<QString> crewmem;
        QString fl_st = "v" + QString::number( ( i - 1 ) % mModel.maxfreq + 1 );
        QDate today = dbeg.addDays( ( i - 1 ) / mModel.maxfreq );

        if ( gMANAGER.workForced( today, mModel.name, mRole, fl_st ) ) {
            // If workday forced, keep it
            crewmem = {
                gMANAGER.getWorkingPnt( today, mModel.name, mRole, fl_st )};
        } else {      // Delete previous and get idle pnts
            try {     // Try to remove existing days if they exist
                auto assignedpnt =
                    gMANAGER.getWorkingPnt( today, mModel.name, mRole, fl_st );
                gMANAGER.deleteWorkday( today, assignedpnt );
            } catch ( const QString& msg ) {
                qDebug() << msg;
            }
            crewmem = gMANAGER.getIdlePnts( today, mModel.name, mRole );
        }

        domain[ i ].resize( crewmem.size() );
        domain[ i ] = crewmem;
        current_domain[ i ].resize( crewmem.size() );
        current_domain[ i ] = crewmem;
    }

    v.resize( n + 1 );

    // Init flight number per pilot and sort domains
    std::vector<QString> pntids = gMANAGER.getPnts( mModel.name, aRole );
    for ( auto pid : pntids ) {
        /* Fill workregisters the following way:
         * * since a schedule is generated on one week, we suppose previous
         *   week is well scheduled, current week is a new one,
         * * verify that the workdays added won't violate the constraint on
         * a
         *   one month period, for this, take all the workdays from the date
         *   being one month before the *end* of the currently computed
         *   schedule
         * * idem for the year */
        workRegister wr;
        auto year = dbeg.year();
        auto oneyearago =
            QDate( year - 1, dbeg.month(), dbeg.day() ).addDays( kWEEK );
        std::vector<WorkdayDb> wds =
            gMANAGER.getWorkdays( pid, oneyearago, dbeg );
        for ( auto wd : wds ) {
            if ( wd.status == "v1" || wd.status == "v2" || wd.status == "v3" ) {
                wr.mPrevFlightTime.year += wd.lapse;
                wr.mPrevFlightTime.month +=
                    ( dbeg.daysTo( wd.workdate ) <= kMONTH - kWEEK ) ? wd.lapse
                                                                     : 0.;
            }
        }
        workload.emplace( std::make_pair( pid, wr ) );
    }
    sort_domains();

    // create schedule
    bcssp( n, Status::unknown );

    // And check rest constraints
    mRestCompliancy = checkRest();
}

void ScheduleInstance::schedule(const AcftModelDb& acftmod, QString role,
        QDate dbeg, QDate dend)
{
    auto ndays = dbeg.daysTo(dend);
    auto nweeks = ndays / kWEEK + 1;
    for (auto i = 0 ; i < nweeks ; i++) {
        auto gensched = ScheduleInstance(
                acftmod, role, dbeg.addDays(i * kWEEK));
        gensched.updateDb(gMANAGER);
    }
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
        } catch ( const std::out_of_range& ) {
            // Happens when value not yet instantiated (v[i] not filled)
        }
        v[ i ] = cd_copy[ j ];
        workload.at( v[ i ] ).addFlight();     // Add newly planned flight

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
    auto pnt = gMANAGER.getPnt( v[ i ] );
    valid &= pnt.maxfreq > 0 ? pnt.maxfreq > wr.flights : true;
    if ( v[ j ] == v[ i ] ) {
        float wft = ( wr.flights + 1 ) * kTIMEPERFLIGHT;
        valid &= wft <= kMAXFLIGHTWEEK &&
                 wft + wr.mPrevFlightTime.month <= kMAXFLIGHTMONTH &&
                 wft + wr.mPrevFlightTime.year <= kMAXFLIGHTYEAR;
    }
    if (     // If two flights happen the same day...
        ( ( i - 1 ) / mModel.maxfreq ) == ( ( j - 1 ) / mModel.maxfreq ) ) {
        // ...ensure pilots are different
        valid &= v[ i ] != v[ j ];
    }
    return valid;
}

bool ScheduleInstance::checkRest() { return true; }

void ScheduleInstance::recomputeFrom(
    const AcftModelDb& amod, QString role, QDate dfrom )
{
    // First clean the schedule
    QDate to = gMANAGER.getLastScheduledDay();
    std::vector<WorkdayDb> autosetdays =
        gMANAGER.getAutomaticallySetWorkdays( dfrom, to, role, amod.name );
    for ( WorkdayDb wday : autosetdays ) {
        gMANAGER.deleteWorkday( wday.workdate, wday.pntid );
    }
    for ( auto d = dfrom; d.daysTo( to ) > 0; d = d.addDays( kWEEK ) ) {
        ScheduleInstance rescheduled = ScheduleInstance( amod, role, d );
        rescheduled.updateDb( gMANAGER );
    }
}

void ScheduleInstance::updateDb( DbManager dbm )
{
    // For each variable, update related workday
    for ( int i = 1; i <= n; i++ ) {
        WorkdayDb wddb;
        wddb.forced = false;
        wddb.pntid = v[ i ];
        wddb.status = "v" + QString::number( ( i - 1 ) % mModel.maxfreq + 1 );
        wddb.workdate = mStartDate.addDays( ( i - 1 ) / mModel.maxfreq );
        wddb.lapse = kTIMEPERFLIGHT;

        dbm.addWorkday( wddb );
    }
}

bool ScheduleInstance::workRegister::operator<=( const workRegister& aWr )
{
    float yeara = aWr.mPrevFlightTime.year + kTIMEPERFLIGHT * aWr.flights;
    float yearth = mPrevFlightTime.year + kTIMEPERFLIGHT + flights;
    float montha = aWr.mPrevFlightTime.month + kTIMEPERFLIGHT * aWr.flights;
    float monthth = mPrevFlightTime.month + kTIMEPERFLIGHT * flights;
    if ( yearth != yeara ) {
        return yearth <= yeara;
    }
    if ( monthth != montha ) {
        return monthth <= montha;
    }
    return flights <= aWr.flights;
}

void ScheduleInstance::workRegister::addFlight() { ++flights; }

void ScheduleInstance::workRegister::removeFlight()
{
    flights = std::max( flights - 1, 0 );
}

bool ScheduleInstance::workRegister::check()
{
    float wft = flights * kTIMEPERFLIGHT;
    return wft <= kMAXFLIGHTWEEK &&
           mPrevFlightTime.month + wft <= kMAXFLIGHTMONTH &&
           mPrevFlightTime.year + wft <= kMAXFLIGHTYEAR;
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
        day = 1 + ( i - 1 ) / mModel.maxfreq;
        flight_no = ( i - 1 ) % mModel.maxfreq;

        qDebug() << "day: " << day << ";"
                 << "flight number: " << flight_no << ";"
                 << "pnt: " << v[ i ];
    }
}

bool ScheduleInstance::test()
{
    QString role = QString::fromStdString( "cpt" );
    AcftModelDb mod;
    mod.name = "a";
    mod.maxfreq = 2;
    mod.crew = 2;

    ScheduleInstance si = ScheduleInstance( mod, role, QDate::currentDate() );
    si.print();
    si.updateDb( gMANAGER );
    return true;
}
