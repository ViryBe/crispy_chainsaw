#ifndef MODIFYFLIGHT_H
#define MODIFYFLIGHT_H

#include <QDialog>

namespace Ui {
class ModifyFlight;
}

class ModifyFlight : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyFlight(QDate dateSend, QString plane,QWidget *parent = 0);
    ~ModifyFlight();

private slots:

    void on_pasEffectue_stateChanged(int arg1);

    void on_dateEdit_userDateChanged(const QDate &date);

private:
    QString appareil;
    Ui::ModifyFlight *ui;
};

#endif // MODIFYFLIGHT_H
