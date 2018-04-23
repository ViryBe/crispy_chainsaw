#include "mainwindow.h"


MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent ), ui( new Ui::MainWindow )
{
    ui->setupUi( this );
    refresh_pilot_list();
    auto idPilot = ui->pilotList->currentItem()->text();
    refresh_pilot_information( idPilot );
}

MainWindow::~MainWindow() { delete ui; }


// Fonctions relatives onglet pilote


void MainWindow::refresh_pilot_list()
{
    ui->pilotList->clear();
    pntsIds.clear();
    pntsIds = gMANAGER.getPnts();
    std::sort( pntsIds.begin(), pntsIds.end() );
    for ( auto id : pntsIds ) {
        ui->pilotList->addItem( id.toUpper() );
    }
    ui->pilotList->setCurrentRow( 0 );
}

void MainWindow::on_pilotAdd_clicked()
{
    PntDb pilot;
    newPilot NewPilot( pilot );
    NewPilot.setModal( true );
    NewPilot.exec();
    refresh_pilot_list();
}

void MainWindow::on_pilotManage_clicked()
{
    QString idPilot = ui->pilotList->currentItem()->text();
    auto pilotInfo = gMANAGER.getPnt( idPilot );

    // Création de la nouvelle boite de dialogue pour modifier les infos
    newPilot NewPilot( pilotInfo );
    NewPilot.setModal( true );
    NewPilot.updateInformation();
    NewPilot.exec();

    refresh_pilot_information( idPilot );
}

void MainWindow::on_pilotDelete_clicked()
{
    auto reply = QMessageBox::question( this, "Suppression pilote",
        "Etes vous surs de vouloir supprimer ce pilote ?",
        QMessageBox::Yes | QMessageBox::No );
    if ( reply == QMessageBox::Yes ) {
        gMANAGER.deletePnt( ui->pilotList->currentItem()->text() );
        refresh_pilot_list();
    }
}


void MainWindow::on_pilotList_currentTextChanged( const QString& currentText )
{
    refresh_pilot_information( currentText );
}


void MainWindow::on_refreshButton_clicked()
{
    QDate dateFrom = ui->dateFrom->date();
    QDate dateTo = ui->dateTo->date();
    refresh_pilot_days(
        ui->pilotList->currentItem()->text(), dateFrom, dateTo );
}


// Onglet avions


void MainWindow::on_validerB737_clicked()
{
    QDate dateFrom = ui->dateFromB737->date();
    QDate dateTo = ui->dateToB737->date();
}

void MainWindow::refresh_pilot_days(
    const QString& id, QDate dateFrom, QDate dateTo )
{
    ui->dateTo->setMinimumDate( ui->dateFrom->date() );
    ui->standByDays->setText(
        QString::number( gMANAGER.cardInactiveDays( id, dateFrom, dateTo ) ) );
    ui->officeDays->setText( QString::number(
        gMANAGER.cardWorkdays( id, dateFrom, dateTo, "office" ) ) );
    ui->homeDays->setText( QString::number(
        gMANAGER.cardWorkdays( id, dateFrom, dateTo, "off" ) ) );
    ui->flightDays->setText( QString::number(
        gMANAGER.cardWorkdays( id, dateFrom, dateTo, "v_" ) ) );
}

void MainWindow::refresh_pilot_information( const QString& idPilot )
{
    auto pilotInfo = gMANAGER.getPnt( idPilot );
    ui->codePilotBDD->setText( pilotInfo.id );
    ui->pilotNameBDD->setText( pilotInfo.name );
    QDate date = date.currentDate();
    QDate dateMonth = date.addDays(1 - date.day());
    ui->dateFrom->setDate( dateMonth );
    ui->dateFromB727->setDate( date );
    ui->dateFromB737->setDate( date );
    ui->dateTo->setDate( dateMonth.addDays( -1).addMonths(1) );
    ui->dateToB727->setDate( date.addDays( 15 ) );
    ui->dateToB737->setDate( date.addDays( 15 ) );
    refresh_pilot_days( idPilot, dateMonth, dateMonth.addDays( -1).addMonths(1) );
    ui->limitationVol->setValue( pilotInfo.maxfreq );
    if ( pilotInfo.acft_modelname == "b727" ) {
        if ( pilotInfo.role == "cpt" ) {
            ui->B727Cdt->setChecked( true );
        } else if ( pilotInfo.role == "fo" ) {
            ui->B727FO->setChecked( true );
        } else {
            ui->B727FE->setChecked( true );
        }
    } else if ( pilotInfo.role == "cpt" ) {
        ui->B737Cdt->setChecked( true );
    } else {
        ui->B737FO->setChecked( true );
    }
}


void MainWindow::on_dateFrom_userDateChanged( const QDate& date )
{
    ui->dateTo->setDate( date.addDays( -1).addMonths(1) );
}

void MainWindow::update_tables( QDate dateFrom, QDate dateTo )
/* Two options here: either we iterate through all pnts,
 * or pnts are gathered considering the table to fill (i.e. using
 * appropriate getPnts method). The latter method has the advantage of
 * having a more precise context in the loop (defined role, defined
 * aircraft) which allows to rebuild the schedule without fetching back
 * neither the aircraft model nor the role from the database */
{
    auto nbDays = dateFrom.daysTo( dateTo );
    { // Schedule generation
        auto acftmodel = gMANAGER.getAcftModel( "b727" );
        auto gensched = ScheduleInstance( acftmodel, "cpt", dateFrom );
        qDebug() << "schedule generated";
        gensched.updateDb( gMANAGER );
    }

    gMANAGER.fillWorkdays(dateFrom);
    gMANAGER.createScheduleView( "ScheduleView", dateFrom, dateTo );

    QString kVIEWNAME = "yyyyMMdd";
    QString basequstr = "SELECT id";
    for ( auto i = 0; i <= nbDays; i++ ) {
        QDate today = dateFrom.addDays( i );
        basequstr += ", c" + today.toString( kVIEWNAME );
    }
    basequstr += " FROM ScheduleView";

    // B727 captains
    QSqlQueryModel* b727cpt_model = new QSqlQueryModel;
    {
        QString b727cpt_qustr = basequstr + " WHERE acftmodel LIKE 'b727' AND "
                                "role LIKE 'cpt'";
        qDebug() << "queryb727cpt:" << b727cpt_qustr;
        b727cpt_model->setQuery( b727cpt_qustr );
    }
    {
        auto acftmodel = gMANAGER.getAcftModel( "b727" );
        auto gensched = ScheduleInstance( acftmodel, "cpt", dateFrom );
        qDebug() << "schedule generated";
        gensched.updateDb( gMANAGER );
    }
    gMANAGER.fillWorkdays(dateFrom);
    gMANAGER.createScheduleView( "ScheduleView", dateFrom, dateTo );

    b727cpt_model->setHeaderData( 0, Qt::Horizontal, QObject::tr( "PNT" ) );
    for ( int j = 0; j <= nbDays; j++ ) {
        QString header = dateFrom.addDays( j ).toString( "dd" );
        b727cpt_model->setHeaderData(
                j + 1, Qt::Horizontal,
                QObject::tr( header.toStdString().c_str() ) );
    }

    ui->foB727Tab->setModel( b727cpt_model );
    ui->foB737Tab->show();
    ui->capB727Tab->setModel( b727cpt_model );
    /*std::map<QString, int> dict;
    ui->capB727Tab->setColumnCount(nbDays);
    ui->capB737Tab->setColumnCount(nbDays);
    ui->feB727Tab->setColumnCount(nbDays);
    ui->foB727Tab->setColumnCount(nbDays);
    ui->foB737Tab->setColumnCount(nbDays);
    for ( auto id : pntsIds ) {
        auto pilot = gMANAGER.getPnt( id );
        for ( int j = 0; j <= dateFrom.daysTo(dateTo); j++) {
            ui->capB727Tab
            try {
                auto info = gMANAGER.statusOfPnt( d, id );
                if ( pilot.acft_modelname == "b737" ) { // pilote de b737
                    if ( pilot.role == "cpt" ) {
                        qDebug() << info;
                    } else { // First officer
                        qDebug() << info;
                    }
                } else { // b727
                    if ( pilot.role == "cpt" ) {
                        qDebug() << info;
                    } else if ( pilot.role == "fo" ) {
                        qDebug() << info;
                    } else {
                        // flight engineer
                        qDebug() << info;
                    }
                }
            } catch (const QDate& d) {
                qDebug() << "couldn't fetch data for pnt:" << id
                         << "on the:" << d.toString( "yyyy-MM-dd" );
                auto regenerate = QMessageBox::question(
                        this, "Emploi du temps incomplet",
                        "Regenerer l'emploi du temps?",
                        QMessageBox::Yes | QMessageBox::No,
                        QMessageBox::Yes );
                if ( regenerate == QMessageBox::Yes ) {
                    auto pnt = gMANAGER.getPnt( id );
                    auto acftmod = gMANAGER.getAcftModel( pnt.acft_modelname );
                    auto regen = ScheduleInstance( acftmod, pnt.role,
                                                   dateFrom, dateTo );
                    regen.updateDb( gMANAGER );
                    qDebug() << "regeneration asked";
                }
            }
        }
    } */
}


void MainWindow::on_validerB727_clicked()
{
    QDate dateFrom = ui->dateFromB727->date();
    QDate dateTo = ui->dateToB727->date();
    update_tables( dateFrom, dateTo );
}


void MainWindow::on_officeButton_clicked()
{
    QString id = ui->pilotList->currentItem()->text();
    planningPilot newPlanningPilot( id );
    newPlanningPilot.setModal( true );
    newPlanningPilot.exec();
    refresh_pilot_information( ui->pilotList->currentItem()->text() );
}

void MainWindow::on_dateFromB737_userDateChanged( const QDate& date )
{
    ui->dateToB737->setDate( date.addDays( 15 ) );
    ui->dateToB737->setMinimumDate( ui->dateFromB737->date() );
}

void MainWindow::on_dateFromB727_userDateChanged( const QDate& date )
{
    ui->dateToB727->setDate( date.addDays( 15 ) );
    ui->dateToB727->setMinimumDate( ui->dateFromB727->date() );
}

void MainWindow::on_changeDureeB737_clicked()
{
    QDate date = ui->dateFromB737->date();
    QString appareil = "B737";
    ModifyFlight newModifyFlight( date, appareil);
    newModifyFlight.setModal( true );
    newModifyFlight.exec();
}

void MainWindow::on_changeDureeB727_clicked()
{
    QDate date = ui->dateFromB727->date();
    QString appareil = "B727";
    ModifyFlight newModifyFlight( date, appareil);
    newModifyFlight.setModal( true );
    newModifyFlight.exec();
}
