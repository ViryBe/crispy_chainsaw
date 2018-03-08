#ifndef NEWPLANE_H
#define NEWPLANE_H

#include <QDialog>

namespace Ui
{
    class newPlane;
}

class newPlane : public QDialog
{
    Q_OBJECT

public:
    explicit newPlane( QWidget* parent = 0 );
    ~newPlane();
    void updateInformation( const QString&, const QString& );

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::newPlane* ui;
};

#endif     // NEWPLANE_H
