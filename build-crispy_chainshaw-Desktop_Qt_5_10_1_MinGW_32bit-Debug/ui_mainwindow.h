/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExporter;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *pilotTab;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QListWidget *pilotList;
    QPushButton *pilotSee;
    QPushButton *pilotAdd;
    QVBoxLayout *verticalLayout_4;
    QLabel *information_text;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *codePliot;
    QLabel *codePilotBDD;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *pilotName;
    QLabel *pilotNameBDD;
    QSpacerItem *horizontalSpacer;
    QFrame *line_2;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QCheckBox *B737Cdt;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *B737FO;
    QGridLayout *B727Grid;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *b737Tab;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget;
    QWidget *b727Tab;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(692, 585);
        actionExporter = new QAction(MainWindow);
        actionExporter->setObjectName(QStringLiteral("actionExporter"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        pilotTab = new QWidget();
        pilotTab->setObjectName(QStringLiteral("pilotTab"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pilotTab->sizePolicy().hasHeightForWidth());
        pilotTab->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(pilotTab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_3->setContentsMargins(-1, -1, 20, -1);
        pilotList = new QListWidget(pilotTab);
        new QListWidgetItem(pilotList);
        new QListWidgetItem(pilotList);
        pilotList->setObjectName(QStringLiteral("pilotList"));
        pilotList->setMinimumSize(QSize(110, 0));
        pilotList->setMaximumSize(QSize(110, 16777215));

        verticalLayout_3->addWidget(pilotList);

        pilotSee = new QPushButton(pilotTab);
        pilotSee->setObjectName(QStringLiteral("pilotSee"));
        pilotSee->setMinimumSize(QSize(110, 0));
        pilotSee->setMaximumSize(QSize(110, 16777215));

        verticalLayout_3->addWidget(pilotSee);

        pilotAdd = new QPushButton(pilotTab);
        pilotAdd->setObjectName(QStringLiteral("pilotAdd"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pilotAdd->sizePolicy().hasHeightForWidth());
        pilotAdd->setSizePolicy(sizePolicy1);
        pilotAdd->setMinimumSize(QSize(110, 0));
        pilotAdd->setMaximumSize(QSize(110, 16777215));

        verticalLayout_3->addWidget(pilotAdd);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        information_text = new QLabel(pilotTab);
        information_text->setObjectName(QStringLiteral("information_text"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(information_text->sizePolicy().hasHeightForWidth());
        information_text->setSizePolicy(sizePolicy2);
        QFont font;
        font.setFamily(QStringLiteral("Gentium"));
        font.setPointSize(20);
        information_text->setFont(font);

        verticalLayout_4->addWidget(information_text);

        verticalSpacer_5 = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_4->addItem(verticalSpacer_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        codePliot = new QLabel(pilotTab);
        codePliot->setObjectName(QStringLiteral("codePliot"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(codePliot->sizePolicy().hasHeightForWidth());
        codePliot->setSizePolicy(sizePolicy3);
        codePliot->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(codePliot);

        codePilotBDD = new QLabel(pilotTab);
        codePilotBDD->setObjectName(QStringLiteral("codePilotBDD"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(codePilotBDD->sizePolicy().hasHeightForWidth());
        codePilotBDD->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(codePilotBDD);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pilotName = new QLabel(pilotTab);
        pilotName->setObjectName(QStringLiteral("pilotName"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(20);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pilotName->sizePolicy().hasHeightForWidth());
        pilotName->setSizePolicy(sizePolicy5);
        pilotName->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pilotName);

        pilotNameBDD = new QLabel(pilotTab);
        pilotNameBDD->setObjectName(QStringLiteral("pilotNameBDD"));
        sizePolicy4.setHeightForWidth(pilotNameBDD->sizePolicy().hasHeightForWidth());
        pilotNameBDD->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(pilotNameBDD);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout);

        line_2 = new QFrame(pilotTab);
        line_2->setObjectName(QStringLiteral("line_2"));
        sizePolicy4.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy4);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_2);

        label_2 = new QLabel(pilotTab);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setFont(font);

        verticalLayout_4->addWidget(label_2);

        verticalSpacer = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_4->addItem(verticalSpacer);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_6 = new QLabel(pilotTab);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);
        label_6->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        B737Cdt = new QCheckBox(pilotTab);
        B737Cdt->setObjectName(QStringLiteral("B737Cdt"));
        sizePolicy4.setHeightForWidth(B737Cdt->sizePolicy().hasHeightForWidth());
        B737Cdt->setSizePolicy(sizePolicy4);
        B737Cdt->setCheckable(false);

        gridLayout->addWidget(B737Cdt, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        B737FO = new QCheckBox(pilotTab);
        B737FO->setObjectName(QStringLiteral("B737FO"));
        sizePolicy4.setHeightForWidth(B737FO->sizePolicy().hasHeightForWidth());
        B737FO->setSizePolicy(sizePolicy4);
        B737FO->setCheckable(false);

        gridLayout->addWidget(B737FO, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        B727Grid = new QGridLayout();
        B727Grid->setSpacing(6);
        B727Grid->setObjectName(QStringLiteral("B727Grid"));
        checkBox_5 = new QCheckBox(pilotTab);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        sizePolicy4.setHeightForWidth(checkBox_5->sizePolicy().hasHeightForWidth());
        checkBox_5->setSizePolicy(sizePolicy4);
        checkBox_5->setCheckable(false);

        B727Grid->addWidget(checkBox_5, 2, 1, 1, 1);

        checkBox_3 = new QCheckBox(pilotTab);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        sizePolicy4.setHeightForWidth(checkBox_3->sizePolicy().hasHeightForWidth());
        checkBox_3->setSizePolicy(sizePolicy4);
        checkBox_3->setCheckable(false);

        B727Grid->addWidget(checkBox_3, 1, 1, 1, 1);

        checkBox_2 = new QCheckBox(pilotTab);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        sizePolicy4.setHeightForWidth(checkBox_2->sizePolicy().hasHeightForWidth());
        checkBox_2->setSizePolicy(sizePolicy4);
        checkBox_2->setCheckable(false);

        B727Grid->addWidget(checkBox_2, 0, 1, 1, 1);

        label_5 = new QLabel(pilotTab);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setMinimumSize(QSize(100, 0));

        B727Grid->addWidget(label_5, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        B727Grid->addItem(horizontalSpacer_2, 0, 2, 1, 1);


        gridLayout_2->addLayout(B727Grid, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);


        horizontalLayout_2->addLayout(verticalLayout_4);

        tabWidget->addTab(pilotTab, QString());
        b737Tab = new QWidget();
        b737Tab->setObjectName(QStringLiteral("b737Tab"));
        verticalLayout_2 = new QVBoxLayout(b737Tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tableWidget = new QTableWidget(b737Tab);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout_2->addWidget(tableWidget);

        tabWidget->addTab(b737Tab, QString());
        b727Tab = new QWidget();
        b727Tab->setObjectName(QStringLiteral("b727Tab"));
        tabWidget->addTab(b727Tab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 692, 26));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuFichier->addAction(actionExporter);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Crispy Planification", nullptr));
        actionExporter->setText(QApplication::translate("MainWindow", "Exporter", nullptr));

        const bool __sortingEnabled = pilotList->isSortingEnabled();
        pilotList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = pilotList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "Pilote1", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = pilotList->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "Pilote2", nullptr));
        pilotList->setSortingEnabled(__sortingEnabled);

        pilotSee->setText(QApplication::translate("MainWindow", "Voir Pilote", nullptr));
        pilotAdd->setText(QApplication::translate("MainWindow", "Nouveau Pilote", nullptr));
        information_text->setText(QApplication::translate("MainWindow", "Informations Pilote", nullptr));
        codePliot->setText(QApplication::translate("MainWindow", "Code Pilote", nullptr));
        codePilotBDD->setText(QApplication::translate("MainWindow", "DA", nullptr));
        pilotName->setText(QApplication::translate("MainWindow", "Nom", nullptr));
        pilotNameBDD->setText(QApplication::translate("MainWindow", "Delta Alpha", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Qualification", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "B737", nullptr));
        B737Cdt->setText(QApplication::translate("MainWindow", "CDT", nullptr));
        B737FO->setText(QApplication::translate("MainWindow", "F/O", nullptr));
        checkBox_5->setText(QApplication::translate("MainWindow", "F/E", nullptr));
        checkBox_3->setText(QApplication::translate("MainWindow", "F/O", nullptr));
        checkBox_2->setText(QApplication::translate("MainWindow", "CDT", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "B727", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(pilotTab), QApplication::translate("MainWindow", "Pilotes", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Pilote 2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Horaire 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(b737Tab), QApplication::translate("MainWindow", "B737", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(b727Tab), QApplication::translate("MainWindow", "B727", nullptr));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
