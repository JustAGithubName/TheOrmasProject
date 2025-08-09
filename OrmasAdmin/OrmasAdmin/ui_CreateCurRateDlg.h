/********************************************************************************
** Form generated from reading UI file 'CreateCurRateDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATECURRATEDLG_H
#define UI_CREATECURRATEDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
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

class Ui_CreateCurrencyRate
{
public:
    QGridLayout *gridLayout;
    QComboBox *fromCurrencyCmb;
    QDateEdit *dateEdit;
    QLabel *currencyLb;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLineEdit *fromValueEdit;
    QLabel *lb;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLabel *oDateLb;
    QLabel *label_3;
    QComboBox *toCurrencyCmb;
    QLineEdit *toValueEdit;

    void setupUi(QDialog *CreateCurrencyRate)
    {
        if (CreateCurrencyRate->objectName().isEmpty())
            CreateCurrencyRate->setObjectName(QStringLiteral("CreateCurrencyRate"));
        CreateCurrencyRate->resize(641, 197);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CreateCurrencyRate->sizePolicy().hasHeightForWidth());
        CreateCurrencyRate->setSizePolicy(sizePolicy);
        CreateCurrencyRate->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateCurrencyRate->setModal(false);
        gridLayout = new QGridLayout(CreateCurrencyRate);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        fromCurrencyCmb = new QComboBox(CreateCurrencyRate);
        fromCurrencyCmb->setObjectName(QStringLiteral("fromCurrencyCmb"));
        fromCurrencyCmb->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(fromCurrencyCmb, 1, 1, 1, 1);

        dateEdit = new QDateEdit(CreateCurrencyRate);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setMaximumSize(QSize(150, 16777215));
        dateEdit->setReadOnly(true);

        gridLayout->addWidget(dateEdit, 0, 1, 1, 1);

        currencyLb = new QLabel(CreateCurrencyRate);
        currencyLb->setObjectName(QStringLiteral("currencyLb"));
        currencyLb->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(currencyLb, 1, 0, 1, 1);

        label_4 = new QLabel(CreateCurrencyRate);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreateCurrencyRate);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(CreateCurrencyRate);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 8, 0, 1, 4);

        fromValueEdit = new QLineEdit(CreateCurrencyRate);
        fromValueEdit->setObjectName(QStringLiteral("fromValueEdit"));
        fromValueEdit->setMinimumSize(QSize(150, 0));
        fromValueEdit->setMaximumSize(QSize(150, 16777215));
        fromValueEdit->setReadOnly(false);

        gridLayout->addWidget(fromValueEdit, 2, 1, 1, 1);

        lb = new QLabel(CreateCurrencyRate);
        lb->setObjectName(QStringLiteral("lb"));
        lb->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(lb, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 3, 1, 1);

        label = new QLabel(CreateCurrencyRate);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 2, 1, 1);

        oDateLb = new QLabel(CreateCurrencyRate);
        oDateLb->setObjectName(QStringLiteral("oDateLb"));

        gridLayout->addWidget(oDateLb, 0, 0, 1, 1);

        label_3 = new QLabel(CreateCurrencyRate);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        toCurrencyCmb = new QComboBox(CreateCurrencyRate);
        toCurrencyCmb->setObjectName(QStringLiteral("toCurrencyCmb"));

        gridLayout->addWidget(toCurrencyCmb, 3, 1, 1, 1);

        toValueEdit = new QLineEdit(CreateCurrencyRate);
        toValueEdit->setObjectName(QStringLiteral("toValueEdit"));

        gridLayout->addWidget(toValueEdit, 4, 1, 1, 1);

        QWidget::setTabOrder(fromValueEdit, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(CreateCurrencyRate);

        QMetaObject::connectSlotsByName(CreateCurrencyRate);
    } // setupUi

    void retranslateUi(QDialog *CreateCurrencyRate)
    {
        CreateCurrencyRate->setWindowTitle(QApplication::translate("CreateCurrencyRate", "Create/Update subaccount", 0));
        currencyLb->setText(QApplication::translate("CreateCurrencyRate", "From currency:", 0));
        label_4->setText(QApplication::translate("CreateCurrencyRate", "To value:", 0));
        okBtn->setText(QApplication::translate("CreateCurrencyRate", "OK", 0));
        cancelBtn->setText(QApplication::translate("CreateCurrencyRate", "Cancel", 0));
#ifndef QT_NO_TOOLTIP
        fromValueEdit->setToolTip(QApplication::translate("CreateCurrencyRate", "<html><head/><body><p>For example: John</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        lb->setText(QApplication::translate("CreateCurrencyRate", "From value:", 0));
        label->setText(QApplication::translate("CreateCurrencyRate", "Must bu equal to 1, 10,100 and etc.", 0));
        oDateLb->setText(QApplication::translate("CreateCurrencyRate", "Date:", 0));
        label_3->setText(QApplication::translate("CreateCurrencyRate", "To currency:", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateCurrencyRate: public Ui_CreateCurrencyRate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATECURRATEDLG_H
