#ifndef NEWPILOT_H
#define NEWPILOT_H

#include <QDialog>

namespace Ui {
class newPilot;
}

class newPilot : public QDialog
{
    Q_OBJECT

public:
    explicit newPilot(QWidget *parent = 0);
    ~newPilot();

private:
    Ui::newPilot *ui;
};

#endif // NEWPILOT_H
