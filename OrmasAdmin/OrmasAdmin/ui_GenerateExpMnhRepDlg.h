/********************************************************************************
** Form generated from reading UI file 'GenerateExpMnhRepDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEEXPMNHREPDLG_H
#define UI_GENERATEEXPMNHREPDLG_H

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

class Ui_GenerateExpMnhReport
{
public:
    QGridLayout *gridLayout;
    QPushButton *empBtn;
    QDateEdit *fromDateEdit;
    QLabel *fromLb;
    QDateEdit *tillDateEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLabel *label_2;
    QLabel *nameLb;
    QLineEdit *empEdit;
    QLabel *surnameLb;
    QLabel *namePh;
    QLabel *surnamePh;

    void setupUi(QDialog *GenerateExpMnhReport)
    {
        if (GenerateExpMnhReport->objectName().isEmpty())
            GenerateExpMnhReport->setObjectName(QStringLiteral("GenerateExpMnhReport"));
        GenerateExpMnhReport->resize(529, 139);
        GenerateExpMnhReport->setMaximumSize(QSize(16777215, 16777212));
        GenerateExpMnhReport->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GenerateExpMnhReport->setModal(false);
        gridLayout = new QGridLayout(GenerateExpMnhReport);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        empBtn = new QPushButton(GenerateExpMnhReport);
        empBtn->setObjectName(QStringLiteral("empBtn"));

        gridLayout->addWidget(empBtn, 1, 1, 1, 1);

        fromDateEdit = new QDateEdit(GenerateExpMnhReport);
        fromDateEdit->setObjectName(QStringLiteral("fromDateEdit"));

        gridLayout->addWidget(fromDateEdit, 0, 2, 1, 1);

        fromLb = new QLabel(GenerateExpMnhReport);
        fromLb->setObjectName(QStringLiteral("fromLb"));

        gridLayout->addWidget(fromLb, 0, 1, 1, 1);

        tillDateEdit = new QDateEdit(GenerateExpMnhReport);
        tillDateEdit->setObjectName(QStringLiteral("tillDateEdit"));

        gridLayout->addWidget(tillDateEdit, 0, 4, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(GenerateExpMnhReport);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(GenerateExpMnhReport);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 3, 1, 1, 4);

        label_2 = new QLabel(GenerateExpMnhReport);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        nameLb = new QLabel(GenerateExpMnhReport);
        nameLb->setObjectName(QStringLiteral("nameLb"));

        gridLayout->addWidget(nameLb, 2, 1, 1, 1);

        empEdit = new QLineEdit(GenerateExpMnhReport);
        empEdit->setObjectName(QStringLiteral("empEdit"));

        gridLayout->addWidget(empEdit, 1, 2, 1, 3);

        surnameLb = new QLabel(GenerateExpMnhReport);
        surnameLb->setObjectName(QStringLiteral("surnameLb"));

        gridLayout->addWidget(surnameLb, 2, 3, 1, 1);

        namePh = new QLabel(GenerateExpMnhReport);
        namePh->setObjectName(QStringLiteral("namePh"));

        gridLayout->addWidget(namePh, 2, 2, 1, 1);

        surnamePh = new QLabel(GenerateExpMnhReport);
        surnamePh->setObjectName(QStringLiteral("surnamePh"));

        gridLayout->addWidget(surnamePh, 2, 4, 1, 1);

        QWidget::setTabOrder(fromDateEdit, tillDateEdit);
        QWidget::setTabOrder(tillDateEdit, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(GenerateExpMnhReport);

        QMetaObject::connectSlotsByName(GenerateExpMnhReport);
    } // setupUi

    void retranslateUi(QDialog *GenerateExpMnhReport)
    {
        GenerateExpMnhReport->setWindowTitle(QApplication::translate("GenerateExpMnhReport", "Generate expeditor monthly report", 0));
        empBtn->setText(QApplication::translate("GenerateExpMnhReport", "Select employee", 0));
        fromLb->setText(QApplication::translate("GenerateExpMnhReport", "From date:", 0));
        okBtn->setText(QApplication::translate("GenerateExpMnhReport", "OK", 0));
        cancelBtn->setText(QApplication::translate("GenerateExpMnhReport", "Cancel", 0));
        label_2->setText(QApplication::translate("GenerateExpMnhReport", "Till date:", 0));
        nameLb->setText(QApplication::translate("GenerateExpMnhReport", "Name:", 0));
        surnameLb->setText(QApplication::translate("GenerateExpMnhReport", "Surname:", 0));
        namePh->setText(QString());
        surnamePh->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GenerateExpMnhReport: public Ui_GenerateExpMnhReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEEXPMNHREPDLG_H
