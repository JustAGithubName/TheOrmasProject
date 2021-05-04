/********************************************************************************
** Form generated from reading UI file 'GenerateDailySalesRepDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEDAILYSALESREPDLG_H
#define UI_GENERATEDAILYSALESREPDLG_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_GenerateDailySalesReport
{
public:
    QGridLayout *gridLayout;
    QPushButton *empButton;
    QLabel *forLb;
    QLabel *empSurnameLb;
    QLabel *empSurnamePh;
    QLabel *empPhoneLb;
    QLabel *empNameLb;
    QLabel *empNamePh;
    QLabel *empPhonePh;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLineEdit *employeeEdit;
    QDateEdit *forDateEdit;

    void setupUi(QDialog *GenerateDailySalesReport)
    {
        if (GenerateDailySalesReport->objectName().isEmpty())
            GenerateDailySalesReport->setObjectName(QStringLiteral("GenerateDailySalesReport"));
        GenerateDailySalesReport->resize(645, 161);
        GenerateDailySalesReport->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GenerateDailySalesReport->setModal(false);
        gridLayout = new QGridLayout(GenerateDailySalesReport);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        empButton = new QPushButton(GenerateDailySalesReport);
        empButton->setObjectName(QStringLiteral("empButton"));
        empButton->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(empButton, 1, 1, 1, 1);

        forLb = new QLabel(GenerateDailySalesReport);
        forLb->setObjectName(QStringLiteral("forLb"));

        gridLayout->addWidget(forLb, 0, 1, 1, 1);

        empSurnameLb = new QLabel(GenerateDailySalesReport);
        empSurnameLb->setObjectName(QStringLiteral("empSurnameLb"));
        empSurnameLb->setMinimumSize(QSize(50, 0));
        empSurnameLb->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(empSurnameLb, 2, 3, 1, 1);

        empSurnamePh = new QLabel(GenerateDailySalesReport);
        empSurnamePh->setObjectName(QStringLiteral("empSurnamePh"));
        empSurnamePh->setMinimumSize(QSize(100, 0));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        empSurnamePh->setFont(font);

        gridLayout->addWidget(empSurnamePh, 2, 4, 1, 1);

        empPhoneLb = new QLabel(GenerateDailySalesReport);
        empPhoneLb->setObjectName(QStringLiteral("empPhoneLb"));

        gridLayout->addWidget(empPhoneLb, 2, 5, 1, 1);

        empNameLb = new QLabel(GenerateDailySalesReport);
        empNameLb->setObjectName(QStringLiteral("empNameLb"));
        empNameLb->setMinimumSize(QSize(50, 0));
        empNameLb->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(empNameLb, 2, 1, 1, 1);

        empNamePh = new QLabel(GenerateDailySalesReport);
        empNamePh->setObjectName(QStringLiteral("empNamePh"));
        empNamePh->setMinimumSize(QSize(100, 0));
        empNamePh->setFont(font);

        gridLayout->addWidget(empNamePh, 2, 2, 1, 1);

        empPhonePh = new QLabel(GenerateDailySalesReport);
        empPhonePh->setObjectName(QStringLiteral("empPhonePh"));
        empPhonePh->setMinimumSize(QSize(100, 0));
        empPhonePh->setFont(font);

        gridLayout->addWidget(empPhonePh, 2, 6, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(GenerateDailySalesReport);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(GenerateDailySalesReport);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 4, 1, 1, 6);

        employeeEdit = new QLineEdit(GenerateDailySalesReport);
        employeeEdit->setObjectName(QStringLiteral("employeeEdit"));
        employeeEdit->setReadOnly(true);

        gridLayout->addWidget(employeeEdit, 1, 4, 1, 1);

        forDateEdit = new QDateEdit(GenerateDailySalesReport);
        forDateEdit->setObjectName(QStringLiteral("forDateEdit"));

        gridLayout->addWidget(forDateEdit, 0, 4, 1, 1);

        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(GenerateDailySalesReport);

        QMetaObject::connectSlotsByName(GenerateDailySalesReport);
    } // setupUi

    void retranslateUi(QDialog *GenerateDailySalesReport)
    {
        GenerateDailySalesReport->setWindowTitle(QApplication::translate("GenerateDailySalesReport", "Generate daily sales report", 0));
        empButton->setText(QApplication::translate("GenerateDailySalesReport", "Select employee", 0));
        forLb->setText(QApplication::translate("GenerateDailySalesReport", "For date:", 0));
        empSurnameLb->setText(QApplication::translate("GenerateDailySalesReport", "Surname:", 0));
        empSurnamePh->setText(QString());
        empPhoneLb->setText(QApplication::translate("GenerateDailySalesReport", "Phone:", 0));
        empNameLb->setText(QApplication::translate("GenerateDailySalesReport", "Name:", 0));
        empNamePh->setText(QString());
        empPhonePh->setText(QString());
        okBtn->setText(QApplication::translate("GenerateDailySalesReport", "OK", 0));
        cancelBtn->setText(QApplication::translate("GenerateDailySalesReport", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateDailySalesReport: public Ui_GenerateDailySalesReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEDAILYSALESREPDLG_H
