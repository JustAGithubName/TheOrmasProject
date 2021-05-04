/********************************************************************************
** Form generated from reading UI file 'CreateAccblExpDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEACCBLEXPDLG_H
#define UI_CREATEACCBLEXPDLG_H

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
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_CreateAccblExp
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *addBtn;
    QPushButton *deleteBtn;
    QPushButton *cancelBtn;
    QLabel *countLb;
    QLineEdit *sumEdit;
    QLabel *currencyLb;
    QComboBox *currencyCmb;
    QLabel *sumLb;
    QLineEdit *countEdit;
    QComboBox *measureCmb;
    QLabel *measureLb;
    QLabel *label;
    QTextEdit *expenseTextEdit;

    void setupUi(QDialog *CreateAccblExp)
    {
        if (CreateAccblExp->objectName().isEmpty())
            CreateAccblExp->setObjectName(QStringLiteral("CreateAccblExp"));
        CreateAccblExp->resize(671, 268);
        CreateAccblExp->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateAccblExp->setModal(false);
        gridLayout = new QGridLayout(CreateAccblExp);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 17);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addBtn = new QPushButton(CreateAccblExp);
        addBtn->setObjectName(QStringLiteral("addBtn"));

        horizontalLayout->addWidget(addBtn);

        deleteBtn = new QPushButton(CreateAccblExp);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));

        horizontalLayout->addWidget(deleteBtn);

        cancelBtn = new QPushButton(CreateAccblExp);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 9, 0, 1, 4);

        countLb = new QLabel(CreateAccblExp);
        countLb->setObjectName(QStringLiteral("countLb"));
        countLb->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(countLb, 1, 0, 1, 2);

        sumEdit = new QLineEdit(CreateAccblExp);
        sumEdit->setObjectName(QStringLiteral("sumEdit"));

        gridLayout->addWidget(sumEdit, 3, 2, 1, 1);

        currencyLb = new QLabel(CreateAccblExp);
        currencyLb->setObjectName(QStringLiteral("currencyLb"));

        gridLayout->addWidget(currencyLb, 5, 0, 1, 1);

        currencyCmb = new QComboBox(CreateAccblExp);
        currencyCmb->setObjectName(QStringLiteral("currencyCmb"));
        currencyCmb->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(currencyCmb, 5, 2, 1, 1);

        sumLb = new QLabel(CreateAccblExp);
        sumLb->setObjectName(QStringLiteral("sumLb"));

        gridLayout->addWidget(sumLb, 3, 0, 1, 2);

        countEdit = new QLineEdit(CreateAccblExp);
        countEdit->setObjectName(QStringLiteral("countEdit"));

        gridLayout->addWidget(countEdit, 1, 2, 1, 1);

        measureCmb = new QComboBox(CreateAccblExp);
        measureCmb->setObjectName(QStringLiteral("measureCmb"));

        gridLayout->addWidget(measureCmb, 2, 2, 1, 1);

        measureLb = new QLabel(CreateAccblExp);
        measureLb->setObjectName(QStringLiteral("measureLb"));

        gridLayout->addWidget(measureLb, 2, 0, 1, 1);

        label = new QLabel(CreateAccblExp);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        expenseTextEdit = new QTextEdit(CreateAccblExp);
        expenseTextEdit->setObjectName(QStringLiteral("expenseTextEdit"));

        gridLayout->addWidget(expenseTextEdit, 0, 2, 1, 1);

        QWidget::setTabOrder(countEdit, sumEdit);
        QWidget::setTabOrder(sumEdit, addBtn);
        QWidget::setTabOrder(addBtn, cancelBtn);

        retranslateUi(CreateAccblExp);

        QMetaObject::connectSlotsByName(CreateAccblExp);
    } // setupUi

    void retranslateUi(QDialog *CreateAccblExp)
    {
        CreateAccblExp->setWindowTitle(QApplication::translate("CreateAccblExp", "Create/Update expense", 0));
        addBtn->setText(QApplication::translate("CreateAccblExp", "Add", 0));
        deleteBtn->setText(QApplication::translate("CreateAccblExp", "Delete", 0));
        cancelBtn->setText(QApplication::translate("CreateAccblExp", "Cancel", 0));
        countLb->setText(QApplication::translate("CreateAccblExp", "Count:", 0));
        currencyLb->setText(QApplication::translate("CreateAccblExp", "Select currency:", 0));
        sumLb->setText(QApplication::translate("CreateAccblExp", "Sum:", 0));
#ifndef QT_NO_TOOLTIP
        countEdit->setToolTip(QApplication::translate("CreateAccblExp", "<html><head/><body><p>For example: 100</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        measureLb->setText(QApplication::translate("CreateAccblExp", "Select measure:", 0));
        label->setText(QApplication::translate("CreateAccblExp", "Expense description:", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateAccblExp: public Ui_CreateAccblExp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEACCBLEXPDLG_H
