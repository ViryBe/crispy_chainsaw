#ifndef NEWPILOT_H
#define NEWPILOT_H

#include "pnt.h"
#include <QDialog>
#include "db.h"

namespace Ui
{
    class newPilot;
}

class newPilot : public QDialog
{
    Q_OBJECT

public:
    explicit newPilot( PntDb pilotInfo, QWidget* parent = 0 );
    ~newPilot();
    void updateInformation();

private slots:
    void on_buttonBox_accepted();

private:
    PntDb pilot;
    Ui::newPilot* ui;
};

#endif     // NEWPILOT_H
