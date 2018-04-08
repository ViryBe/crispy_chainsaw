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
    qDebug() << choix ;
    for (int i = 0; i<dateFrom.daysTo(dateTo); i ++){
        if (choix == "Congé"){
            _MANAGER.addWorkday(dateFrom.addDays(i), "off" , id, true);
        }
        else if (choix == "Bureau"){
            _MANAGER.addWorkday(dateFrom.addDays(i), "office" , id, true);
        }
        else if (choix == "Simulateur"){
            _MANAGER.addWorkday(dateFrom.addDays(i), "simu" , id, true);
        }
        else{
            _MANAGER.deleteWorkday(dateFrom.addDays(i), id);
        }
    }
}
