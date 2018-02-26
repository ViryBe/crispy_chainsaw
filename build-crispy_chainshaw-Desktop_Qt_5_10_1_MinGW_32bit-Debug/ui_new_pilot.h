/********************************************************************************
** Form generated from reading UI file 'new_pilot.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_PILOT_H
#define UI_NEW_PILOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *information_text;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *codePliot;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *pilotName;
    QLineEdit *lineEdit_2;
    QSpacerItem *horizontalSpacer;
    QFrame *line_2;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QCheckBox *B737Cdt;
    QCheckBox *B737FO;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *B727Grid;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_2;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(358, 517);
        verticalLayout_2 = new QVBoxLayout(Dialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        information_text = new QLabel(Dialog);
        information_text->setObjectName(QStringLiteral("information_text"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(information_text->sizePolicy().hasHeightForWidth());
        information_text->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Gentium"));
        font.setPointSize(20);
        information_text->setFont(font);

        verticalLayout_4->addWidget(information_text);

        verticalSpacer_5 = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_4->addItem(verticalSpacer_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        codePliot = new QLabel(Dialog);
        codePliot->setObjectName(QStringLiteral("codePliot"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(codePliot->sizePolicy().hasHeightForWidth());
        codePliot->setSizePolicy(sizePolicy1);
        codePliot->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(codePliot);

        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(lineEdit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pilotName = new QLabel(Dialog);
        pilotName->setObjectName(QStringLiteral("pilotName"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(20);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pilotName->sizePolicy().hasHeightForWidth());
        pilotName->setSizePolicy(sizePolicy2);
        pilotName->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pilotName);

        lineEdit_2 = new QLineEdit(Dialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lineEdit_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout);

        line_2 = new QFrame(Dialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy3);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_2);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font);

        verticalLayout_4->addWidget(label_2);

        verticalSpacer = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_4->addItem(verticalSpacer);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        B737Cdt = new QCheckBox(Dialog);
        B737Cdt->setObjectName(QStringLiteral("B737Cdt"));
        sizePolicy3.setHeightForWidth(B737Cdt->sizePolicy().hasHeightForWidth());
        B737Cdt->setSizePolicy(sizePolicy3);
        B737Cdt->setCheckable(true);

        gridLayout->addWidget(B737Cdt, 0, 1, 1, 1);

        B737FO = new QCheckBox(Dialog);
        B737FO->setObjectName(QStringLiteral("B737FO"));
        sizePolicy3.setHeightForWidth(B737FO->sizePolicy().hasHeightForWidth());
        B737FO->setSizePolicy(sizePolicy3);
        B737FO->setCheckable(true);

        gridLayout->addWidget(B737FO, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        B727Grid = new QGridLayout();
        B727Grid->setObjectName(QStringLiteral("B727Grid"));
        checkBox_3 = new QCheckBox(Dialog);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        sizePolicy3.setHeightForWidth(checkBox_3->sizePolicy().hasHeightForWidth());
        checkBox_3->setSizePolicy(sizePolicy3);
        checkBox_3->setCheckable(true);

        B727Grid->addWidget(checkBox_3, 1, 1, 1, 1);

        checkBox_5 = new QCheckBox(Dialog);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        sizePolicy3.setHeightForWidth(checkBox_5->sizePolicy().hasHeightForWidth());
        checkBox_5->setSizePolicy(sizePolicy3);
        checkBox_5->setCheckable(true);

        B727Grid->addWidget(checkBox_5, 2, 1, 1, 1);

        checkBox_2 = new QCheckBox(Dialog);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        sizePolicy3.setHeightForWidth(checkBox_2->sizePolicy().hasHeightForWidth());
        checkBox_2->setSizePolicy(sizePolicy3);
        checkBox_2->setCheckable(true);

        B727Grid->addWidget(checkBox_2, 0, 1, 1, 1);

        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(100, 0));

        B727Grid->addWidget(label_5, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        B727Grid->addItem(horizontalSpacer_2, 0, 2, 1, 1);


        gridLayout_2->addLayout(B727Grid, 1, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);


        verticalLayout_2->addLayout(verticalLayout_4);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        information_text->setText(QApplication::translate("Dialog", "Informations Pilote", nullptr));
        codePliot->setText(QApplication::translate("Dialog", "Code Pilote", nullptr));
        pilotName->setText(QApplication::translate("Dialog", "Nom", nullptr));
        label_2->setText(QApplication::translate("Dialog", "Qualification", nullptr));
        label_6->setText(QApplication::translate("Dialog", "B737", nullptr));
        B737Cdt->setText(QApplication::translate("Dialog", "CDT", nullptr));
        B737FO->setText(QApplication::translate("Dialog", "F/O", nullptr));
        checkBox_3->setText(QApplication::translate("Dialog", "F/O", nullptr));
        checkBox_5->setText(QApplication::translate("Dialog", "F/E", nullptr));
        checkBox_2->setText(QApplication::translate("Dialog", "CDT", nullptr));
        label_5->setText(QApplication::translate("Dialog", "B727", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_PILOT_H
