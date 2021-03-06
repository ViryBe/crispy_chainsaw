#include "mainwindow.h"


MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent ), ui( new Ui::MainWindow )
{
    ui->setupUi( this );
    refresh_pilot_list();
    auto idPilot = ui->pilotList->currentItem()->text();
    refresh_pilot_information( idPilot );
    if ( gMANAGER.getLastScheduledDay() < QDate::currentDate().addDays( 7 ) ) {
        on_validerB737_clicked();
        on_validerB727_clicked();
    }
    QDate dateFrom = ui->dateFromB727->date();
    QDate dateTo = ui->dateToB727->date();
    //update_tables( dateFrom, dateTo );
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
    //ScheduleInstance::recomputeFrom(gMANAGER.getAcftModel(pilot.acft_modelname), pilot.role, ui->dateFromB727->date());
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
    //ScheduleInstance::recomputeFrom(gMANAGER.getAcftModel(pilotInfo.acft_modelname), pilotInfo.role, ui->dateFromB727->date());
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
    update_tables( dateFrom, dateTo );
}

void MainWindow::refresh_pilot_days(
    const QString& id, QDate dateFrom, QDate dateTo )
{
    ui->dateTo->setMinimumDate( ui->dateFrom->date() );
    ui->standByDays->setText( QString::number(
        gMANAGER.cardWorkdays( id, dateFrom, dateTo, "stby" ) ) );
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
    QDate dateMonth = date.addDays( 1 - date.day() );
    ui->dateFrom->setDate( dateMonth );
    ui->dateFromB727->setDate( date );
    ui->dateFromB737->setDate( date );
    ui->dateTo->setDate( dateMonth.addMonths( 1 ).addDays( -1 ) );
    ui->dateToB727->setDate( date.addDays( 15 ) );
    ui->dateToB737->setDate( date.addDays( 15 ) );
    refresh_pilot_days(
        idPilot, dateMonth, dateMonth.addMonths( 1 ).addDays( -1 ) );
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
    ui->dateTo->setDate( date.addMonths( 1 ).addDays( -1 ) );
}

void MainWindow::update_tables( QDate dateFrom, QDate dateTo )
{
    auto nbDays = dateFrom.daysTo( dateTo );
    auto kDATEFMT = "yyyyMMdd"; // Not necessarily the same as in the db.cpp
    // Generate schedules
    auto genSched = [&] ( QString acftname, std::vector<QString> roles ) {
        for (auto r : roles) {
            auto acftmodel = gMANAGER.getAcftModel(acftname);
            ScheduleInstance::schedule(acftmodel, r, dateFrom, dateTo);
        }
    };
    genSched("b727", {"cpt", "fo", "fe"});
    genSched("b737", {"cpt", "fo"});
    qDebug() << "schedule generated for b737";
    for ( QDate d = dateFrom ; d.daysTo(dateTo) >= 0 ; d = d.addDays(1) ) {
        gMANAGER.fillWorkdays(d);
    }
    //gMANAGER.fillWorkdays( dateFrom );
    auto viewname = "ScheduleView" + dateFrom.toString(kDATEFMT) +
        dateTo.toString(kDATEFMT);
    gMANAGER.createScheduleView( viewname, dateFrom, dateTo );

    // Set query models (link schedule to table views)
    auto setQuModel = [&] ( QString acftname, std::vector<QString> roles,
            std::vector<QSqlQueryModel*>& models ) {
        for (auto i = 0u ; i < roles.size() ; i++) {
            QString qustr = DbManager::scheduleViewQuery(viewname, dateFrom,
                    dateTo, acftname, roles[i]);
            models[i]->setQuery(qustr);
            models[i]->setHeaderData(
                    0, Qt::Horizontal, QObject::tr( "PNT" ) );
            for ( int j = 0; j <= nbDays; j++ ) {
                QString header = dateFrom.addDays( j ).toString( "dd" );
                models[ i ]->setHeaderData( j + 1, Qt::Horizontal,
                        QObject::tr( header.toStdString().c_str() ) );
            }
        }
    };
    std::vector<QSqlQueryModel*> b727models = {
        new QSqlQueryModel, new QSqlQueryModel, new QSqlQueryModel};
    setQuModel("b727", {"cpt", "fo", "fe"}, b727models);

    std::vector<QSqlQueryModel*> b737models = {
        new QSqlQueryModel, new QSqlQueryModel};
    setQuModel("b737", {"cpt", "fo"}, b737models);

    ui->capB727Tab->setModel( b727models[ 0 ] );
    ui->foB727Tab->setModel( b727models[ 1 ] );
    ui->feB727Tab->setModel( b727models[ 2 ] );
    ui->capB737Tab->setModel( b737models[ 0 ] );
    ui->foB737Tab->setModel( b737models[ 1 ] );
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
    ModifyFlight newModifyFlight( date, appareil );
    newModifyFlight.setModal( true );
    newModifyFlight.exec();
}

void MainWindow::on_changeDureeB727_clicked()
{
    QDate date = ui->dateFromB727->date();
    QString appareil = "B727";
    ModifyFlight newModifyFlight( date, appareil );
    newModifyFlight.setModal( true );
    newModifyFlight.exec();
}

void MainWindow::on_actionExporter_triggered()
{
    QDate date = ui->dateFromB727->date();
    QDate dateTo = ui->dateToB727->date();
    QString filtre;
    QString fichier = QFileDialog::getSaveFileName(this, "Choisir l'emplacement",  "planning_B727_" + date.toString("yyyyMMdd")
                                                   + dateTo.toString("_yyyyMMdd"), "CSV Files (*.csv)", &filtre);
    // [Collect model data to QString]
    QString textData;
    textData += "De, " + date.toString("yyyy_MM_dd") +", Au, "+ dateTo.toString("yyyy_MM_dd") + "\n";
    QAbstractItemModel *model = ui->capB727Tab->model();
    int rows = model->rowCount();
    int columns = model->columnCount();
    textData += "\nCaptain\nPNT, ";

    for (int j = 0; j < columns - 1; j++) {

            textData += date.addDays(j).toString("dd");
            textData += ", ";      // for .csv file format
    }
    textData += "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

                textData += model->data(model->index(i,j)).toString();
                textData += ", ";      // for .csv file format
        }
        textData += "\n";             // (optional: for new line segmentation)
    }

    model = ui->foB727Tab->model();
    rows = model->rowCount();
    columns = model->columnCount();
    textData += "\nFirst Officer\nPNT, ";
    for (int j = 0; j < columns - 1; j++) {

            textData += date.addDays(j).toString("dd");
            textData += ", ";      // for .csv file format
    }
    textData += "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

                textData += model->data(model->index(i,j)).toString();
                textData += ", ";      // for .csv file format
        }
        textData += "\n";             // (optional: for new line segmentation)
    }

    model = ui->feB727Tab->model();
    rows = model->rowCount();
    columns = model->columnCount();
    textData += "\nFlight Engineer\nPNT, ";

    for (int j = 0; j < columns - 1; j++) {

            textData += date.addDays(j).toString("dd");
            textData += ", ";      // for .csv file format
    }
    textData += "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

                textData += model->data(model->index(i,j)).toString();
                textData += ", ";      // for .csv file format
        }
        textData += "\n";             // (optional: for new line segmentation)
    }

    // [Save to file] (header file <QFile> needed)
    // .csv
    QFile csvFile(fichier);
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        QTextStream out(&csvFile);
        out << textData;

        csvFile.close();
    }
}

void MainWindow::on_actionExporter_B737_triggered()
{
    QDate date = ui->dateFromB737->date();
    QDate dateTo = ui->dateToB737->date();
    QString filtre;
    QString fichier = QFileDialog::getSaveFileName(this, "Choisir l'emplacement",  "planning_B737_" + date.toString("yyyyMMdd")
                                                   + dateTo.toString("_yyyyMMdd"), "CSV Files (*.csv)", &filtre);
    // [Collect model data to QString]
    QString textData;
    textData += "De, " + date.toString("yyyy_MM_dd") +", Au, "+ dateTo.toString("yyyy_MM_dd") + "\n";
    QAbstractItemModel *model = ui->capB737Tab->model();
    int rows = model->rowCount();
    int columns = model->columnCount();
    textData += "\nCaptain\nPNT, ";

    for (int j = 0; j < columns -1; j++) {

            textData += date.addDays(j).toString("dd");
            textData += ", ";      // for .csv file format
    }
    textData += "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

                textData += model->data(model->index(i,j)).toString();
                textData += ", ";      // for .csv file format
        }
        textData += "\n";             // (optional: for new line segmentation)
    }

    model = ui->foB737Tab->model();
    rows = model->rowCount();
    columns = model->columnCount();
    textData += "\nFirst Officer\nPNT, ";
    for (int j = 0; j < columns - 1; j++) {

            textData += date.addDays(j).toString("dd");
            textData += ", ";      // for .csv file format
    }
    textData += "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

                textData += model->data(model->index(i,j)).toString();
                textData += ", ";      // for .csv file format
        }
        textData += "\n";             // (optional: for new line segmentation)
    }


    // [Save to file] (header file <QFile> needed)
    // .csv
    QFile csvFile(fichier);
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        QTextStream out(&csvFile);
        out << textData;

        csvFile.close();
    }
}

void MainWindow::on_actionExporter_pilotes_triggered()
{
    QDate dateFrom = ui->dateFrom->date();
    QDate dateTo = ui->dateTo->date();
    QString filtre;
    QString fichier = QFileDialog::getSaveFileName(this, "Choisir l'emplacement",  "récapitulatif_pilotes_" + dateFrom.toString("yyyyMMdd")
                                                   + dateTo.toString("_yyyyMMdd"), "CSV Files (*.csv)", &filtre);
    // [Collect model data to QString]
    QString textData;
    textData += "De, " + dateFrom.toString("yyyy_MM_dd") +", Au, "+ dateTo.toString("yyyy_MM_dd") + "\n\n";
    textData += "PNT, STBY, OFFICE, OFF, SIMU, FLIGHT\n";
    for ( auto id : pntsIds ) {
        textData += id + ", " +
        QString::number( gMANAGER.cardWorkdays( id, dateFrom, dateTo, "stby" ) ) + ", " +
        QString::number( gMANAGER.cardWorkdays( id, dateFrom, dateTo, "office" ) ) + ", " +
        QString::number( gMANAGER.cardWorkdays( id, dateFrom, dateTo, "off" ) ) + ", " +
                QString::number( gMANAGER.cardWorkdays( id, dateFrom, dateTo, "simu" ) ) + ", " +
        QString::number( gMANAGER.cardWorkdays( id, dateFrom, dateTo, "v_" ) )  + "\n ";
    }

    // [Save to file] (header file <QFile> needed)
    // .csv
    QFile csvFile(fichier);
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        QTextStream out(&csvFile);
        out << textData;

        csvFile.close();
    }
}

