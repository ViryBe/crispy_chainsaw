#include "planningpilot.h"
#include "ui_planningpilot.h"

planningPilot::planningPilot( QWidget* parent )
    : QDialog( parent ), ui( new Ui::planningPilot )
{
    QDate dateFrom;
    QDate dateTo;
    ui->setupUi( this );
    ui->dateTo->setDate( dateFrom.currentDate() );
    ui->dateFrom->setDate( dateTo.currentDate() );
    ui->dateTo->setMinimumDate( ui->dateFrom->date() );
}

planningPilot::~planningPilot() { delete ui; }
