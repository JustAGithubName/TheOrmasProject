/********************************************************************************
** Form generated from reading UI file 'GenerateFinRepDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEFINREPDLG_H
#define UI_GENERATEFINREPDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateFinancialReport
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabSelector;
    QWidget *tabMonth;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbMonthly;
    QDateEdit *dateMonthlyEdit;
    QCheckBox *ownFormCbx;
    QWidget *tabYear;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lbYear;
    QDateEdit *dateYearlyEdit;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QLabel *fromLb;
    QDateEdit *fromDateEdit;
    QLabel *label_2;
    QDateEdit *tillDateEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QWidget *radioWidget;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radioMon;
    QRadioButton *radioYear;
    QRadioButton *radioPeriod;

    void setupUi(QDialog *GenerateFinancialReport)
    {
        if (GenerateFinancialReport->objectName().isEmpty())
            GenerateFinancialReport->setObjectName(QStringLiteral("GenerateFinancialReport"));
        GenerateFinancialReport->resize(523, 209);
        GenerateFinancialReport->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GenerateFinancialReport->setModal(false);
        gridLayout = new QGridLayout(GenerateFinancialReport);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        tabSelector = new QTabWidget(GenerateFinancialReport);
        tabSelector->setObjectName(QStringLiteral("tabSelector"));
        tabSelector->setMinimumSize(QSize(500, 0));
        tabMonth = new QWidget();
        tabMonth->setObjectName(QStringLiteral("tabMonth"));
        horizontalLayout_3 = new QHBoxLayout(tabMonth);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lbMonthly = new QLabel(tabMonth);
        lbMonthly->setObjectName(QStringLiteral("lbMonthly"));

        horizontalLayout_3->addWidget(lbMonthly);

        dateMonthlyEdit = new QDateEdit(tabMonth);
        dateMonthlyEdit->setObjectName(QStringLiteral("dateMonthlyEdit"));

        horizontalLayout_3->addWidget(dateMonthlyEdit);

        ownFormCbx = new QCheckBox(tabMonth);
        ownFormCbx->setObjectName(QStringLiteral("ownFormCbx"));

        horizontalLayout_3->addWidget(ownFormCbx);

        tabSelector->addTab(tabMonth, QString());
        tabYear = new QWidget();
        tabYear->setObjectName(QStringLiteral("tabYear"));
        horizontalLayout_4 = new QHBoxLayout(tabYear);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lbYear = new QLabel(tabYear);
        lbYear->setObjectName(QStringLiteral("lbYear"));

        horizontalLayout_4->addWidget(lbYear);

        dateYearlyEdit = new QDateEdit(tabYear);
        dateYearlyEdit->setObjectName(QStringLiteral("dateYearlyEdit"));
        dateYearlyEdit->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 0)));
        dateYearlyEdit->setCurrentSection(QDateTimeEdit::YearSection);

        horizontalLayout_4->addWidget(dateYearlyEdit);

        tabSelector->addTab(tabYear, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        fromLb = new QLabel(tab);
        fromLb->setObjectName(QStringLiteral("fromLb"));

        horizontalLayout_2->addWidget(fromLb);

        fromDateEdit = new QDateEdit(tab);
        fromDateEdit->setObjectName(QStringLiteral("fromDateEdit"));
        fromDateEdit->setCurrentSection(QDateTimeEdit::MonthSection);

        horizontalLayout_2->addWidget(fromDateEdit);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        tillDateEdit = new QDateEdit(tab);
        tillDateEdit->setObjectName(QStringLiteral("tillDateEdit"));

        horizontalLayout_2->addWidget(tillDateEdit);

        tabSelector->addTab(tab, QString());

        gridLayout->addWidget(tabSelector, 0, 1, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(GenerateFinancialReport);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(GenerateFinancialReport);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 3, 1, 1, 2);

        radioWidget = new QWidget(GenerateFinancialReport);
        radioWidget->setObjectName(QStringLiteral("radioWidget"));
        horizontalLayout_5 = new QHBoxLayout(radioWidget);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        radioMon = new QRadioButton(radioWidget);
        radioMon->setObjectName(QStringLiteral("radioMon"));
        radioMon->setCheckable(true);
        radioMon->setChecked(true);

        horizontalLayout_5->addWidget(radioMon);

        radioYear = new QRadioButton(radioWidget);
        radioYear->setObjectName(QStringLiteral("radioYear"));

        horizontalLayout_5->addWidget(radioYear);

        radioPeriod = new QRadioButton(radioWidget);
        radioPeriod->setObjectName(QStringLiteral("radioPeriod"));

        horizontalLayout_5->addWidget(radioPeriod);


        gridLayout->addWidget(radioWidget, 2, 1, 1, 2);

        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(GenerateFinancialReport);

        tabSelector->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GenerateFinancialReport);
    } // setupUi

    void retranslateUi(QDialog *GenerateFinancialReport)
    {
        GenerateFinancialReport->setWindowTitle(QApplication::translate("GenerateFinancialReport", "Generate financial report", 0));
        lbMonthly->setText(QApplication::translate("GenerateFinancialReport", "Select month:", 0));
        dateMonthlyEdit->setDisplayFormat(QApplication::translate("GenerateFinancialReport", "MM.yyyy", 0));
        ownFormCbx->setText(QApplication::translate("GenerateFinancialReport", "Company letterhead", 0));
        tabSelector->setTabText(tabSelector->indexOf(tabMonth), QApplication::translate("GenerateFinancialReport", "Monthly", 0));
        lbYear->setText(QApplication::translate("GenerateFinancialReport", "Select year:", 0));
        dateYearlyEdit->setDisplayFormat(QApplication::translate("GenerateFinancialReport", "yyyy", 0));
        tabSelector->setTabText(tabSelector->indexOf(tabYear), QApplication::translate("GenerateFinancialReport", "Yearly", 0));
        fromLb->setText(QApplication::translate("GenerateFinancialReport", "From date:", 0));
        fromDateEdit->setDisplayFormat(QApplication::translate("GenerateFinancialReport", "MM.yyyy", 0));
        label_2->setText(QApplication::translate("GenerateFinancialReport", "Till date:", 0));
        tillDateEdit->setDisplayFormat(QApplication::translate("GenerateFinancialReport", "MM.yyyy", 0));
        tabSelector->setTabText(tabSelector->indexOf(tab), QApplication::translate("GenerateFinancialReport", "For any period", 0));
        okBtn->setText(QApplication::translate("GenerateFinancialReport", "OK", 0));
        cancelBtn->setText(QApplication::translate("GenerateFinancialReport", "Cancel", 0));
        radioMon->setText(QApplication::translate("GenerateFinancialReport", "Month", 0));
        radioYear->setText(QApplication::translate("GenerateFinancialReport", "Year", 0));
        radioPeriod->setText(QApplication::translate("GenerateFinancialReport", "Period", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateFinancialReport: public Ui_GenerateFinancialReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEFINREPDLG_H
