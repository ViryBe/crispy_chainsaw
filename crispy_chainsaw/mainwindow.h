#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include "newpilot.h"
#include "newplane.h"
#include "ui_mainwindow.h"
#include "db.h"
#include <QMessageBox>

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
    //pilot tab
    void on_pilotAdd_clicked();
    void on_pilotDelete_clicked();
    void on_pilotList_currentTextChanged( const QString& currentText );
    void on_pilotManage_clicked();
    void on_refreshButton_clicked();

    //plane tab
    void on_planeManage_clicked();
    void on_planeAdd_clicked();

    //B737 tab
    void on_validerB737_clicked();
    void on_dateFrom_userDateChanged(const QDate &date);



private:
    Ui::MainWindow* ui;
    void refresh_pilot_information(const QString& idPilot);
    void refresh_pilot_days(QDate dateFrom, QDate dateTo);
    void refresh_pilot_list();
    void change_pilot_function();
};

#endif     // MAINWINDOW_H
