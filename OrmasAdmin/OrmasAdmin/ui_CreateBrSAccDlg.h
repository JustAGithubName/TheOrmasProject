/********************************************************************************
** Form generated from reading UI file 'CreateBrSAccDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEBRSACCDLG_H
#define UI_CREATEBRSACCDLG_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CreateBranchSubaccount
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLabel *label_5;
    QPushButton *subaccountBtn;
    QLineEdit *subaccountEdit;
    QComboBox *branchCmb;

    void setupUi(QDialog *CreateBranchSubaccount)
    {
        if (CreateBranchSubaccount->objectName().isEmpty())
            CreateBranchSubaccount->setObjectName(QStringLiteral("CreateBranchSubaccount"));
        CreateBranchSubaccount->resize(595, 122);
        CreateBranchSubaccount->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateBranchSubaccount->setModal(false);
        gridLayout = new QGridLayout(CreateBranchSubaccount);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 17);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreateBranchSubaccount);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(CreateBranchSubaccount);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 2);

        label_5 = new QLabel(CreateBranchSubaccount);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        subaccountBtn = new QPushButton(CreateBranchSubaccount);
        subaccountBtn->setObjectName(QStringLiteral("subaccountBtn"));

        gridLayout->addWidget(subaccountBtn, 1, 0, 1, 1);

        subaccountEdit = new QLineEdit(CreateBranchSubaccount);
        subaccountEdit->setObjectName(QStringLiteral("subaccountEdit"));
        subaccountEdit->setReadOnly(true);

        gridLayout->addWidget(subaccountEdit, 1, 1, 1, 1);

        branchCmb = new QComboBox(CreateBranchSubaccount);
        branchCmb->setObjectName(QStringLiteral("branchCmb"));

        gridLayout->addWidget(branchCmb, 0, 1, 1, 1);

        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(CreateBranchSubaccount);

        QMetaObject::connectSlotsByName(CreateBranchSubaccount);
    } // setupUi

    void retranslateUi(QDialog *CreateBranchSubaccount)
    {
        CreateBranchSubaccount->setWindowTitle(QApplication::translate("CreateBranchSubaccount", "Create/Update branch-subaccount relation", 0));
        okBtn->setText(QApplication::translate("CreateBranchSubaccount", "Ok", 0));
        cancelBtn->setText(QApplication::translate("CreateBranchSubaccount", "Cancel", 0));
        label_5->setText(QApplication::translate("CreateBranchSubaccount", "Branch:", 0));
        subaccountBtn->setText(QApplication::translate("CreateBranchSubaccount", "Select subaccount", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateBranchSubaccount: public Ui_CreateBranchSubaccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEBRSACCDLG_H
