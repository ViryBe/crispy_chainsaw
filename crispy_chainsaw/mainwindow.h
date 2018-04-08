#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "db.h"
#include "newpilot.h"
#include "newplane.h"
#include "planningpilot.h"
#include "schedule.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMainWindow>
#include <QMessageBox>
#include <QMessageBox>
#include <QWidget>
#include <algorithm>
#include <map>
#include <vector>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = 0 );
    ~MainWindow();

private slots:
    // pilot tab
    void on_pilotAdd_clicked();
    void on_pilotDelete_clicked();
    void on_pilotList_currentTextChanged( const QString& currentText );
    void on_pilotManage_clicked();
    void on_refreshButton_clicked();

    // B737 tab
    void on_validerB737_clicked();
    void on_dateFrom_userDateChanged( const QDate& date );
    void on_validerB727_clicked();
    void on_dateFromB737_userDateChanged( const QDate& date );
    void on_dateFromB727_userDateChanged( const QDate& date );
    void on_officeButton_clicked();

private:
    Ui::MainWindow* ui;
    std::vector<QString> pntsIds;
    void refresh_pilot_information( const QString& idPilot );
    void refresh_pilot_days( const QString& idPilot, QDate, QDate );
    void refresh_pilot_list();
    void update_tables( QDate dateFrom, QDate dateTo );
};

#endif     // MAINWINDOW_H
