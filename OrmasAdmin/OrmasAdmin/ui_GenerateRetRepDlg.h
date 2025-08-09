/********************************************************************************
** Form generated from reading UI file 'GenerateRetRepDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATERETREPDLG_H
#define UI_GENERATERETREPDLG_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_GenerateReturnReport
{
public:
    QGridLayout *gridLayout;
    QPushButton *empBtn;
    QLabel *nameLb;
    QDateEdit *tillDateEdit;
    QLabel *fromLb;
    QDateEdit *fromDateEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLabel *label_2;
    QLineEdit *empEdit;
    QCheckBox *allCkb;
    QLabel *namePh;
    QLabel *surnameLb;
    QLabel *surnamePh;

    void setupUi(QDialog *GenerateReturnReport)
    {
        if (GenerateReturnReport->objectName().isEmpty())
            GenerateReturnReport->setObjectName(QStringLiteral("GenerateReturnReport"));
        GenerateReturnReport->resize(529, 166);
        GenerateReturnReport->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GenerateReturnReport->setModal(false);
        gridLayout = new QGridLayout(GenerateReturnReport);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        empBtn = new QPushButton(GenerateReturnReport);
        empBtn->setObjectName(QStringLiteral("empBtn"));

        gridLayout->addWidget(empBtn, 2, 1, 1, 1);

        nameLb = new QLabel(GenerateReturnReport);
        nameLb->setObjectName(QStringLiteral("nameLb"));

        gridLayout->addWidget(nameLb, 3, 1, 1, 1);

        tillDateEdit = new QDateEdit(GenerateReturnReport);
        tillDateEdit->setObjectName(QStringLiteral("tillDateEdit"));

        gridLayout->addWidget(tillDateEdit, 0, 4, 1, 1);

        fromLb = new QLabel(GenerateReturnReport);
        fromLb->setObjectName(QStringLiteral("fromLb"));

        gridLayout->addWidget(fromLb, 0, 1, 1, 1);

        fromDateEdit = new QDateEdit(GenerateReturnReport);
        fromDateEdit->setObjectName(QStringLiteral("fromDateEdit"));

        gridLayout->addWidget(fromDateEdit, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(GenerateReturnReport);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(GenerateReturnReport);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 4, 1, 1, 4);

        label_2 = new QLabel(GenerateReturnReport);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        empEdit = new QLineEdit(GenerateReturnReport);
        empEdit->setObjectName(QStringLiteral("empEdit"));

        gridLayout->addWidget(empEdit, 2, 2, 1, 3);

        allCkb = new QCheckBox(GenerateReturnReport);
        allCkb->setObjectName(QStringLiteral("allCkb"));

        gridLayout->addWidget(allCkb, 1, 1, 1, 1);

        namePh = new QLabel(GenerateReturnReport);
        namePh->setObjectName(QStringLiteral("namePh"));

        gridLayout->addWidget(namePh, 3, 2, 1, 1);

        surnameLb = new QLabel(GenerateReturnReport);
        surnameLb->setObjectName(QStringLiteral("surnameLb"));

        gridLayout->addWidget(surnameLb, 3, 3, 1, 1);

        surnamePh = new QLabel(GenerateReturnReport);
        surnamePh->setObjectName(QStringLiteral("surnamePh"));

        gridLayout->addWidget(surnamePh, 3, 4, 1, 1);

        QWidget::setTabOrder(fromDateEdit, tillDateEdit);
        QWidget::setTabOrder(tillDateEdit, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(GenerateReturnReport);

        QMetaObject::connectSlotsByName(GenerateReturnReport);
    } // setupUi

    void retranslateUi(QDialog *GenerateReturnReport)
    {
        GenerateReturnReport->setWindowTitle(QApplication::translate("GenerateReturnReport", "Generate retrun report", 0));
        empBtn->setText(QApplication::translate("GenerateReturnReport", "Select employee", 0));
        nameLb->setText(QApplication::translate("GenerateReturnReport", "Name:", 0));
        fromLb->setText(QApplication::translate("GenerateReturnReport", "From date:", 0));
        okBtn->setText(QApplication::translate("GenerateReturnReport", "OK", 0));
        cancelBtn->setText(QApplication::translate("GenerateReturnReport", "Cancel", 0));
        label_2->setText(QApplication::translate("GenerateReturnReport", "Till date:", 0));
        allCkb->setText(QApplication::translate("GenerateReturnReport", "For all employees", 0));
        namePh->setText(QString());
        surnameLb->setText(QApplication::translate("GenerateReturnReport", "Surname:", 0));
        surnamePh->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GenerateReturnReport: public Ui_GenerateReturnReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATERETREPDLG_H
