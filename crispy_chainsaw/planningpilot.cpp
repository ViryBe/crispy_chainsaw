#include "planningpilot.h"
#include "ui_planningpilot.h"

planningPilot::planningPilot( QString idPilot, QWidget* parent )
    : QDialog( parent ), ui( new Ui::planningPilot ), id (idPilot)
{
    QDate dateFrom;
    QDate dateTo;
    ui->setupUi( this );
    ui->dateTo->setDate( dateFrom.currentDate() );
    ui->dateFrom->setDate( dateTo.currentDate() );
    ui->dateTo->setMinimumDate( ui->dateFrom->date() );
}

planningPilot::~planningPilot() { delete ui; }

void planningPilot::on_dateFrom_userDateChanged(const QDate &date)
{
    ui->dateTo->setMinimumDate( ui->dateFrom->date() );
}

void planningPilot::on_buttonBox_accepted()
{
    QString choix = ui->choixStatut->currentText();
    QDate dateFrom = ui->dateFrom->date();
    QDate dateTo = ui->dateTo->date();
    for (int i = 0; i<=dateFrom.daysTo(dateTo); i ++){
        gMANAGER.deleteWorkday(dateFrom.addDays(i), id);
        if (choix == "Congé"){
            gMANAGER.addWorkday(dateFrom.addDays(i), "off" , id, true);
        }
        else if (choix == "Bureau"){
            gMANAGER.addWorkday(dateFrom.addDays(i), "office" , id, true);
        }
        else if (choix == "Simulateur"){
            gMANAGER.addWorkday(dateFrom.addDays(i), "simu" , id, true);
        }
        else if (choix == "StandBy"){
            gMANAGER.addWorkday(dateFrom.addDays(i), "stby" , id, true);
        }
        else if (choix == "V1"){
            gMANAGER.addWorkday(dateFrom.addDays(i), "v1" , id, true);
        }
        else if (choix == "V2"){
            gMANAGER.addWorkday(dateFrom.addDays(i), "v2" , id, true);
        }
        else if (choix == "V3"){
            gMANAGER.addWorkday(dateFrom.addDays(i), "v3" , id, true);
        }
    }
    PntDb pilot = gMANAGER.getPnt(id);
    //ScheduleInstance::recomputeFrom(gMANAGER.getAcftModel(pilot.acft_modelname), pilot.role, dateFrom);
}
