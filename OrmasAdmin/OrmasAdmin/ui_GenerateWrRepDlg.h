/********************************************************************************
** Form generated from reading UI file 'GenerateWrRepDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEWRREPDLG_H
#define UI_GENERATEWRREPDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_GenerateWarehouseReport
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLabel *warehouseLB;
    QComboBox *warehouseCmb;

    void setupUi(QDialog *GenerateWarehouseReport)
    {
        if (GenerateWarehouseReport->objectName().isEmpty())
            GenerateWarehouseReport->setObjectName(QStringLiteral("GenerateWarehouseReport"));
        GenerateWarehouseReport->resize(501, 81);
        GenerateWarehouseReport->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GenerateWarehouseReport->setModal(false);
        gridLayout = new QGridLayout(GenerateWarehouseReport);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(GenerateWarehouseReport);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(GenerateWarehouseReport);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 3);

        warehouseLB = new QLabel(GenerateWarehouseReport);
        warehouseLB->setObjectName(QStringLiteral("warehouseLB"));

        gridLayout->addWidget(warehouseLB, 0, 1, 1, 1);

        warehouseCmb = new QComboBox(GenerateWarehouseReport);
        warehouseCmb->setObjectName(QStringLiteral("warehouseCmb"));

        gridLayout->addWidget(warehouseCmb, 0, 2, 1, 2);

        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(GenerateWarehouseReport);

        QMetaObject::connectSlotsByName(GenerateWarehouseReport);
    } // setupUi

    void retranslateUi(QDialog *GenerateWarehouseReport)
    {
        GenerateWarehouseReport->setWindowTitle(QApplication::translate("GenerateWarehouseReport", "Generate warehouse turnover balance sheet", 0));
        okBtn->setText(QApplication::translate("GenerateWarehouseReport", "OK", 0));
        cancelBtn->setText(QApplication::translate("GenerateWarehouseReport", "Cancel", 0));
        warehouseLB->setText(QApplication::translate("GenerateWarehouseReport", "Select warehouse:", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateWarehouseReport: public Ui_GenerateWarehouseReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEWRREPDLG_H
