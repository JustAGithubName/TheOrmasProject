/********************************************************************************
** Form generated from reading UI file 'GenerateComRepDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATECOMREPDLG_H
#define UI_GENERATECOMREPDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_GenerateCommonReport
{
public:
    QGridLayout *gridLayout;
    QDateEdit *tillDateEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLabel *label_2;
    QDateEdit *fromDateEdit;
    QLabel *fromLb;

    void setupUi(QDialog *GenerateCommonReport)
    {
        if (GenerateCommonReport->objectName().isEmpty())
            GenerateCommonReport->setObjectName(QStringLiteral("GenerateCommonReport"));
        GenerateCommonReport->resize(501, 81);
        GenerateCommonReport->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GenerateCommonReport->setModal(false);
        gridLayout = new QGridLayout(GenerateCommonReport);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        tillDateEdit = new QDateEdit(GenerateCommonReport);
        tillDateEdit->setObjectName(QStringLiteral("tillDateEdit"));

        gridLayout->addWidget(tillDateEdit, 0, 4, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(GenerateCommonReport);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(GenerateCommonReport);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 4);

        label_2 = new QLabel(GenerateCommonReport);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        fromDateEdit = new QDateEdit(GenerateCommonReport);
        fromDateEdit->setObjectName(QStringLiteral("fromDateEdit"));

        gridLayout->addWidget(fromDateEdit, 0, 2, 1, 1);

        fromLb = new QLabel(GenerateCommonReport);
        fromLb->setObjectName(QStringLiteral("fromLb"));

        gridLayout->addWidget(fromLb, 0, 1, 1, 1);

        QWidget::setTabOrder(fromDateEdit, tillDateEdit);
        QWidget::setTabOrder(tillDateEdit, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(GenerateCommonReport);

        QMetaObject::connectSlotsByName(GenerateCommonReport);
    } // setupUi

    void retranslateUi(QDialog *GenerateCommonReport)
    {
        GenerateCommonReport->setWindowTitle(QApplication::translate("GenerateCommonReport", "Generate common report", 0));
        okBtn->setText(QApplication::translate("GenerateCommonReport", "OK", 0));
        cancelBtn->setText(QApplication::translate("GenerateCommonReport", "Cancel", 0));
        label_2->setText(QApplication::translate("GenerateCommonReport", "Till date:", 0));
        fromLb->setText(QApplication::translate("GenerateCommonReport", "From date:", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateCommonReport: public Ui_GenerateCommonReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATECOMREPDLG_H
