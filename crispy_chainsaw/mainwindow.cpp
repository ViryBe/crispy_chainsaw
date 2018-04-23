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
    // set the date from today to + 15 days
    QDate date = date.currentDate();
    ui->dateFrom->setDate( date );
    ui->dateFromB727->setDate( date );
    ui->dateFromB737->setDate( date );
    ui->dateTo->setDate( date.addDays( 15 ) );
    ui->dateToB727->setDate( date.addDays( 15 ) );
    ui->dateToB737->setDate( date.addDays( 15 ) );
    refresh_pilot_days( idPilot, date, date.addDays( 15 ) );
    //    qDebug() << pilotInfo.maxfreq;     // ok
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
    ui->dateTo->setDate( date.addDays( 15 ) );
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
    // Generate schedules
    for (auto r : {"cpt", "fo"}) {
        auto acftmodel = gMANAGER.getAcftModel( "b727" );
        auto gensched = ScheduleInstance( acftmodel, r, dateFrom );
        qDebug() << "schedule generated for " << r;
        gensched.updateDb( gMANAGER );
    }
    gMANAGER.fillWorkdays(dateFrom);
    gMANAGER.createScheduleView( "ScheduleView", dateFrom, dateTo );

    // Set misc requests and models
    QString kVIEWNAME = "yyyyMMdd";
    QString basequstr = "SELECT id";
    for ( auto i = 0; i <= nbDays; i++ ) {
        QDate today = dateFrom.addDays( i );
        basequstr += ", c" + today.toString( kVIEWNAME );
    }
    basequstr += " FROM ScheduleView";

    // {cpt, fo, fe}
    QSqlQueryModel* b727models[] = {new QSqlQueryModel, new QSqlQueryModel,
        new QSqlQueryModel};
    QString b727roles[] = {QString("cpt"), QString("fo"), QString("fe")};
    for (int i = 0 ; i < 3; i++) {
        QString qustr = basequstr + " WHERE acftmodel LIKE 'b727' AND "
            "role LIKE '" + b727roles[i] + "'";
        qDebug() << "query:" << qustr;
        b727models[i]->setQuery(qustr);
        b727models[i]->setHeaderData( 0, Qt::Horizontal, QObject::tr( "PNT" ) );
        for ( int j = 0; j <= nbDays; j++ ) {
            QString header = dateFrom.addDays( j ).toString( "dd" );
            b727models[i]->setHeaderData(
                    j + 1, Qt::Horizontal,
                    QObject::tr( header.toStdString().c_str() ) );
        }
    }

    QSqlQueryModel* b737models[] = {new QSqlQueryModel, new QSqlQueryModel};
    QString b737roles[] = {QString("cpt"), QString("fo")};
    for (int i = 0 ; i < 2; i++) {
        QString qustr = basequstr + " WHERE acftmodel LIKE 'b737' AND "
            "role LIKE '" + b737roles[i] + "'";
        qDebug() << "query:" << qustr;
        b737models[i]->setQuery(qustr);
        b737models[i]->setHeaderData( 0, Qt::Horizontal, QObject::tr( "PNT" ) );
        for ( int j = 0; j <= nbDays; j++ ) {
            QString header = dateFrom.addDays( j ).toString( "dd" );
            b737models[i]->setHeaderData(
                    j + 1, Qt::Horizontal,
                    QObject::tr( header.toStdString().c_str() ) );
        }
    }

    // B727 captains
    /*
    QSqlQueryModel* b727cpt_model = new QSqlQueryModel;
    {
        QString b727cpt_qustr = basequstr + " WHERE acftmodel LIKE 'b727' AND "
                                "role LIKE 'cpt'";
        qDebug() << "queryb727cpt:" << b727cpt_qustr;
        b727cpt_model->setQuery( b727cpt_qustr );
    }
    b727cpt_model->setHeaderData( 0, Qt::Horizontal, QObject::tr( "PNT" ) );
    for ( int j = 0; j <= nbDays; j++ ) {
        QString header = dateFrom.addDays( j ).toString( "dd" );
        b727cpt_model->setHeaderData(
                j + 1, Qt::Horizontal,
                QObject::tr( header.toStdString().c_str() ) );
    }
    */

    //ui->foB737Tab->show();
    ui->capB727Tab->setModel(b727models[0]);
    ui->foB727Tab->setModel(b727models[1]);
    ui->feB727Tab->setModel(b727models[2]);
    ui->capB737Tab->setModel(b737models[0]);
    ui->foB737Tab->setModel(b737models[1]);
    //ui->capB727Tab->setModel( b727cpt_model );
    //ui->foB727Tab->setModel(b727fo_model);

    // B727 first office
    /*
    QSqlQueryModel* b727fo_model = new QSqlQueryModel;
    {
        QString b727fo_qustr = basequstr + " WHERE acftmodel LIKE 'b727' AND "
            "role LIKE 'fo'";
        qDebug() << "queryb727fo:" << b727fo_qustr;
        b727fo_model->setQuery(b727fo_qustr);
    }
    b727fo_model->setHeaderData(0, Qt::Horizontal, QObject::tr("PNT"));
    for (int j = 0; j <= nbDays; j++) {
        QString header = dateFrom.addDays(j).toString("dd");
        b727fo_model->setHeaderData(
                j+1, Qt::Horizontal,
                QObject::tr(header.toStdString().c_str()));
    }
    */
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
