#ifndef PLANNINGPILOT_H
#define PLANNINGPILOT_H

#include <QDialog>

namespace Ui
{
    class planningPilot;
}

class planningPilot : public QDialog
{
    Q_OBJECT

public:
    explicit planningPilot( QWidget* parent = 0 );
    ~planningPilot();

private slots:
    void on_dateFrom_userDateChanged(const QDate &date);

private:
    Ui::planningPilot* ui;
};

#endif     // PLANNINGPILOT_H
