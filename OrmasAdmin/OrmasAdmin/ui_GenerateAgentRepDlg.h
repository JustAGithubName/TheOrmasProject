/********************************************************************************
** Form generated from reading UI file 'GenerateAgentRepDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEAGENTREPDLG_H
#define UI_GENERATEAGENTREPDLG_H

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

class Ui_GenerateAgentReport
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
    QDateEdit *fromDateEdit;
    QLabel *label;
    QDateEdit *tillDateEdit;

    void setupUi(QDialog *GenerateAgentReport)
    {
        if (GenerateAgentReport->objectName().isEmpty())
            GenerateAgentReport->setObjectName(QStringLiteral("GenerateAgentReport"));
        GenerateAgentReport->resize(645, 161);
        GenerateAgentReport->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GenerateAgentReport->setModal(false);
        gridLayout = new QGridLayout(GenerateAgentReport);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        empButton = new QPushButton(GenerateAgentReport);
        empButton->setObjectName(QStringLiteral("empButton"));
        empButton->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(empButton, 1, 1, 1, 1);

        forLb = new QLabel(GenerateAgentReport);
        forLb->setObjectName(QStringLiteral("forLb"));

        gridLayout->addWidget(forLb, 0, 1, 1, 1);

        empSurnameLb = new QLabel(GenerateAgentReport);
        empSurnameLb->setObjectName(QStringLiteral("empSurnameLb"));
        empSurnameLb->setMinimumSize(QSize(50, 0));
        empSurnameLb->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(empSurnameLb, 2, 3, 1, 1);

        empSurnamePh = new QLabel(GenerateAgentReport);
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

        empPhoneLb = new QLabel(GenerateAgentReport);
        empPhoneLb->setObjectName(QStringLiteral("empPhoneLb"));

        gridLayout->addWidget(empPhoneLb, 2, 5, 1, 1);

        empNameLb = new QLabel(GenerateAgentReport);
        empNameLb->setObjectName(QStringLiteral("empNameLb"));
        empNameLb->setMinimumSize(QSize(50, 0));
        empNameLb->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(empNameLb, 2, 1, 1, 1);

        empNamePh = new QLabel(GenerateAgentReport);
        empNamePh->setObjectName(QStringLiteral("empNamePh"));
        empNamePh->setMinimumSize(QSize(100, 0));
        empNamePh->setFont(font);

        gridLayout->addWidget(empNamePh, 2, 2, 1, 1);

        empPhonePh = new QLabel(GenerateAgentReport);
        empPhonePh->setObjectName(QStringLiteral("empPhonePh"));
        empPhonePh->setMinimumSize(QSize(100, 0));
        empPhonePh->setFont(font);

        gridLayout->addWidget(empPhonePh, 2, 6, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(GenerateAgentReport);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(GenerateAgentReport);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 4, 1, 1, 6);

        employeeEdit = new QLineEdit(GenerateAgentReport);
        employeeEdit->setObjectName(QStringLiteral("employeeEdit"));
        employeeEdit->setReadOnly(true);

        gridLayout->addWidget(employeeEdit, 1, 4, 1, 1);

        fromDateEdit = new QDateEdit(GenerateAgentReport);
        fromDateEdit->setObjectName(QStringLiteral("fromDateEdit"));
        fromDateEdit->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(fromDateEdit, 0, 2, 1, 1);

        label = new QLabel(GenerateAgentReport);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 3, 1, 1);

        tillDateEdit = new QDateEdit(GenerateAgentReport);
        tillDateEdit->setObjectName(QStringLiteral("tillDateEdit"));

        gridLayout->addWidget(tillDateEdit, 0, 4, 1, 1);

        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(GenerateAgentReport);

        QMetaObject::connectSlotsByName(GenerateAgentReport);
    } // setupUi

    void retranslateUi(QDialog *GenerateAgentReport)
    {
        GenerateAgentReport->setWindowTitle(QApplication::translate("GenerateAgentReport", "Generate agent", 0));
        empButton->setText(QApplication::translate("GenerateAgentReport", "Select employee", 0));
        forLb->setText(QApplication::translate("GenerateAgentReport", "For date:", 0));
        empSurnameLb->setText(QApplication::translate("GenerateAgentReport", "Surname:", 0));
        empSurnamePh->setText(QString());
        empPhoneLb->setText(QApplication::translate("GenerateAgentReport", "Phone:", 0));
        empNameLb->setText(QApplication::translate("GenerateAgentReport", "Name:", 0));
        empNamePh->setText(QString());
        empPhonePh->setText(QString());
        okBtn->setText(QApplication::translate("GenerateAgentReport", "OK", 0));
        cancelBtn->setText(QApplication::translate("GenerateAgentReport", "Cancel", 0));
        label->setText(QApplication::translate("GenerateAgentReport", "till:", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateAgentReport: public Ui_GenerateAgentReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEAGENTREPDLG_H
