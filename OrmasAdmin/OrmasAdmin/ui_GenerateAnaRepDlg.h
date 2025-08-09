/********************************************************************************
** Form generated from reading UI file 'GenerateAnaRepDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEANAREPDLG_H
#define UI_GENERATEANAREPDLG_H

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

class Ui_GenerateAnalysisReport
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

    void setupUi(QDialog *GenerateAnalysisReport)
    {
        if (GenerateAnalysisReport->objectName().isEmpty())
            GenerateAnalysisReport->setObjectName(QStringLiteral("GenerateAnalysisReport"));
        GenerateAnalysisReport->resize(523, 209);
        GenerateAnalysisReport->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GenerateAnalysisReport->setModal(false);
        gridLayout = new QGridLayout(GenerateAnalysisReport);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        tabSelector = new QTabWidget(GenerateAnalysisReport);
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

        okBtn = new QPushButton(GenerateAnalysisReport);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(GenerateAnalysisReport);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 3, 1, 1, 2);

        radioWidget = new QWidget(GenerateAnalysisReport);
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

        retranslateUi(GenerateAnalysisReport);

        tabSelector->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GenerateAnalysisReport);
    } // setupUi

    void retranslateUi(QDialog *GenerateAnalysisReport)
    {
        GenerateAnalysisReport->setWindowTitle(QApplication::translate("GenerateAnalysisReport", "Generate analysis report", 0));
        lbMonthly->setText(QApplication::translate("GenerateAnalysisReport", "Select month:", 0));
        dateMonthlyEdit->setDisplayFormat(QApplication::translate("GenerateAnalysisReport", "MM.yyyy", 0));
        ownFormCbx->setText(QApplication::translate("GenerateAnalysisReport", "Company letterhead", 0));
        tabSelector->setTabText(tabSelector->indexOf(tabMonth), QApplication::translate("GenerateAnalysisReport", "Monthly", 0));
        lbYear->setText(QApplication::translate("GenerateAnalysisReport", "Select year:", 0));
        dateYearlyEdit->setDisplayFormat(QApplication::translate("GenerateAnalysisReport", "yyyy", 0));
        tabSelector->setTabText(tabSelector->indexOf(tabYear), QApplication::translate("GenerateAnalysisReport", "Yearly", 0));
        fromLb->setText(QApplication::translate("GenerateAnalysisReport", "From date:", 0));
        fromDateEdit->setDisplayFormat(QApplication::translate("GenerateAnalysisReport", "MM.yyyy", 0));
        label_2->setText(QApplication::translate("GenerateAnalysisReport", "Till date:", 0));
        tillDateEdit->setDisplayFormat(QApplication::translate("GenerateAnalysisReport", "MM.yyyy", 0));
        tabSelector->setTabText(tabSelector->indexOf(tab), QApplication::translate("GenerateAnalysisReport", "For any period", 0));
        okBtn->setText(QApplication::translate("GenerateAnalysisReport", "OK", 0));
        cancelBtn->setText(QApplication::translate("GenerateAnalysisReport", "Cancel", 0));
        radioMon->setText(QApplication::translate("GenerateAnalysisReport", "Month", 0));
        radioYear->setText(QApplication::translate("GenerateAnalysisReport", "Year", 0));
        radioPeriod->setText(QApplication::translate("GenerateAnalysisReport", "Period", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateAnalysisReport: public Ui_GenerateAnalysisReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEANAREPDLG_H
