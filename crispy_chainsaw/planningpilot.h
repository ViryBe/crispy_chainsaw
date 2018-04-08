#ifndef PLANNINGPILOT_H
#define PLANNINGPILOT_H

#include <QDialog>
#include "db.h"
#include "schedule.h"

namespace Ui
{
    class planningPilot;
}

class planningPilot : public QDialog
{
    Q_OBJECT

public:
    explicit planningPilot( QString idPilot ,QWidget* parent = 0 );
    ~planningPilot();

private slots:
    void on_dateFrom_userDateChanged(const QDate &date);

    void on_buttonBox_accepted();

private:
    Ui::planningPilot* ui;
    QString id;
};

#endif     // PLANNINGPILOT_H
