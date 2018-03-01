#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pilotAdd_clicked();

    void on_pilotList_currentTextChanged(const QString &currentText);

    void on_pilotManage_clicked();

    void on_refreshButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
