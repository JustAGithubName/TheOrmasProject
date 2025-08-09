/********************************************************************************
** Form generated from reading UI file 'GenerateCmpBlcDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATECMPBLCDLG_H
#define UI_GENERATECMPBLCDLG_H

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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateCompanyBalance
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QTabWidget *tabSelector;
    QWidget *tabMonth;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbMonthly;
    QDateEdit *dateMonthlyEdit;
    QWidget *tabYear;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lbYear;
    QDateEdit *dateYearlyEdit;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QLabel *fromLb_2;
    QDateEdit *fromDateEdit;
    QLabel *label_3;
    QDateEdit *tillDateEdit;
    QWidget *radioWidget;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radioMon;
    QRadioButton *radioYear;
    QRadioButton *radioPeriod;

    void setupUi(QDialog *GenerateCompanyBalance)
    {
        if (GenerateCompanyBalance->objectName().isEmpty())
            GenerateCompanyBalance->setObjectName(QStringLiteral("GenerateCompanyBalance"));
        GenerateCompanyBalance->resize(543, 182);
        GenerateCompanyBalance->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GenerateCompanyBalance->setModal(false);
        gridLayout = new QGridLayout(GenerateCompanyBalance);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(GenerateCompanyBalance);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(GenerateCompanyBalance);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 4);

        tabSelector = new QTabWidget(GenerateCompanyBalance);
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
        fromLb_2 = new QLabel(tab);
        fromLb_2->setObjectName(QStringLiteral("fromLb_2"));

        horizontalLayout_2->addWidget(fromLb_2);

        fromDateEdit = new QDateEdit(tab);
        fromDateEdit->setObjectName(QStringLiteral("fromDateEdit"));
        fromDateEdit->setCurrentSection(QDateTimeEdit::MonthSection);

        horizontalLayout_2->addWidget(fromDateEdit);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        tillDateEdit = new QDateEdit(tab);
        tillDateEdit->setObjectName(QStringLiteral("tillDateEdit"));

        horizontalLayout_2->addWidget(tillDateEdit);

        tabSelector->addTab(tab, QString());

        gridLayout->addWidget(tabSelector, 0, 0, 1, 1);

        radioWidget = new QWidget(GenerateCompanyBalance);
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


        gridLayout->addWidget(radioWidget, 1, 0, 1, 3);

        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(GenerateCompanyBalance);

        tabSelector->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GenerateCompanyBalance);
    } // setupUi

    void retranslateUi(QDialog *GenerateCompanyBalance)
    {
        GenerateCompanyBalance->setWindowTitle(QApplication::translate("GenerateCompanyBalance", "Generate company balance", 0));
        okBtn->setText(QApplication::translate("GenerateCompanyBalance", "OK", 0));
        cancelBtn->setText(QApplication::translate("GenerateCompanyBalance", "Cancel", 0));
        lbMonthly->setText(QApplication::translate("GenerateCompanyBalance", "Select month:", 0));
        dateMonthlyEdit->setDisplayFormat(QApplication::translate("GenerateCompanyBalance", "MM.yyyy", 0));
        tabSelector->setTabText(tabSelector->indexOf(tabMonth), QApplication::translate("GenerateCompanyBalance", "Monthly", 0));
        lbYear->setText(QApplication::translate("GenerateCompanyBalance", "Select year:", 0));
        dateYearlyEdit->setDisplayFormat(QApplication::translate("GenerateCompanyBalance", "yyyy", 0));
        tabSelector->setTabText(tabSelector->indexOf(tabYear), QApplication::translate("GenerateCompanyBalance", "Yearly", 0));
        fromLb_2->setText(QApplication::translate("GenerateCompanyBalance", "From date:", 0));
        fromDateEdit->setDisplayFormat(QApplication::translate("GenerateCompanyBalance", "MM.yyyy", 0));
        label_3->setText(QApplication::translate("GenerateCompanyBalance", "Till date:", 0));
        tillDateEdit->setDisplayFormat(QApplication::translate("GenerateCompanyBalance", "MM.yyyy", 0));
        tabSelector->setTabText(tabSelector->indexOf(tab), QApplication::translate("GenerateCompanyBalance", "For any period", 0));
        radioMon->setText(QApplication::translate("GenerateCompanyBalance", "Month", 0));
        radioYear->setText(QApplication::translate("GenerateCompanyBalance", "Year", 0));
        radioPeriod->setText(QApplication::translate("GenerateCompanyBalance", "Period", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateCompanyBalance: public Ui_GenerateCompanyBalance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATECMPBLCDLG_H
