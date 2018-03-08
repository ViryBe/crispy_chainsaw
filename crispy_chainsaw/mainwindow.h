#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QWidget>

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
    void on_pilotAdd_clicked();

    void on_pilotList_currentTextChanged( const QString& currentText );

    void on_pilotManage_clicked();

    void on_refreshButton_clicked();

    void on_planeManage_clicked();

    void on_planeAdd_clicked();

    void on_validerB737_clicked();

private:
    Ui::MainWindow* ui;
};

#endif     // MAINWINDOW_H
