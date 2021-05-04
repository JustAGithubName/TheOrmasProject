/********************************************************************************
** Form generated from reading UI file 'GenerateAccRepDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEACCREPDLG_H
#define UI_GENERATEACCREPDLG_H

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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateAccountCardReport
{
public:
    QGridLayout *gridLayout;
    QLabel *fromLb;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLabel *label;
    QWidget *oneAccWidget;
    QGridLayout *gridLayout_2;
    QLabel *accLb;
    QLabel *orLb;
    QLineEdit *accIDEdit;
    QPushButton *sAccBtn;
    QPushButton *accBtn;
    QLabel *accNameLb;
    QLineEdit *accNumberEdit;
    QLabel *accNamePh;
    QDateEdit *fromDateEdit;
    QDateEdit *tillDateEdit;
    QRadioButton *allAccRb;
    QRadioButton *oneAccRb;

    void setupUi(QDialog *GenerateAccountCardReport)
    {
        if (GenerateAccountCardReport->objectName().isEmpty())
            GenerateAccountCardReport->setObjectName(QStringLiteral("GenerateAccountCardReport"));
        GenerateAccountCardReport->resize(644, 302);
        GenerateAccountCardReport->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GenerateAccountCardReport->setModal(false);
        gridLayout = new QGridLayout(GenerateAccountCardReport);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        fromLb = new QLabel(GenerateAccountCardReport);
        fromLb->setObjectName(QStringLiteral("fromLb"));

        gridLayout->addWidget(fromLb, 1, 1, 1, 1);

        label_2 = new QLabel(GenerateAccountCardReport);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(GenerateAccountCardReport);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(GenerateAccountCardReport);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 8, 1, 1, 5);

        label = new QLabel(GenerateAccountCardReport);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 1, 1, 5);

        oneAccWidget = new QWidget(GenerateAccountCardReport);
        oneAccWidget->setObjectName(QStringLiteral("oneAccWidget"));
        oneAccWidget->setEnabled(false);
        gridLayout_2 = new QGridLayout(oneAccWidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        accLb = new QLabel(oneAccWidget);
        accLb->setObjectName(QStringLiteral("accLb"));

        gridLayout_2->addWidget(accLb, 0, 3, 1, 1);

        orLb = new QLabel(oneAccWidget);
        orLb->setObjectName(QStringLiteral("orLb"));
        orLb->setMinimumSize(QSize(40, 0));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        orLb->setFont(font1);
        orLb->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(orLb, 0, 2, 1, 1);

        accIDEdit = new QLineEdit(oneAccWidget);
        accIDEdit->setObjectName(QStringLiteral("accIDEdit"));
        accIDEdit->setMaximumSize(QSize(120, 16777215));
        accIDEdit->setReadOnly(true);

        gridLayout_2->addWidget(accIDEdit, 0, 1, 1, 1);

        sAccBtn = new QPushButton(oneAccWidget);
        sAccBtn->setObjectName(QStringLiteral("sAccBtn"));

        gridLayout_2->addWidget(sAccBtn, 1, 0, 1, 1);

        accBtn = new QPushButton(oneAccWidget);
        accBtn->setObjectName(QStringLiteral("accBtn"));

        gridLayout_2->addWidget(accBtn, 0, 0, 1, 1);

        accNameLb = new QLabel(oneAccWidget);
        accNameLb->setObjectName(QStringLiteral("accNameLb"));

        gridLayout_2->addWidget(accNameLb, 2, 0, 1, 1);

        accNumberEdit = new QLineEdit(oneAccWidget);
        accNumberEdit->setObjectName(QStringLiteral("accNumberEdit"));
        accNumberEdit->setMinimumSize(QSize(150, 0));
        accNumberEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(accNumberEdit, 0, 4, 1, 1);

        accNamePh = new QLabel(oneAccWidget);
        accNamePh->setObjectName(QStringLiteral("accNamePh"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(accNamePh->sizePolicy().hasHeightForWidth());
        accNamePh->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QStringLiteral("Times New Roman"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        accNamePh->setFont(font2);
        accNamePh->setTextFormat(Qt::RichText);
        accNamePh->setScaledContents(true);

        gridLayout_2->addWidget(accNamePh, 3, 0, 1, 5);


        gridLayout->addWidget(oneAccWidget, 3, 1, 1, 5);

        fromDateEdit = new QDateEdit(GenerateAccountCardReport);
        fromDateEdit->setObjectName(QStringLiteral("fromDateEdit"));

        gridLayout->addWidget(fromDateEdit, 1, 2, 1, 1);

        tillDateEdit = new QDateEdit(GenerateAccountCardReport);
        tillDateEdit->setObjectName(QStringLiteral("tillDateEdit"));

        gridLayout->addWidget(tillDateEdit, 1, 4, 1, 1);

        allAccRb = new QRadioButton(GenerateAccountCardReport);
        allAccRb->setObjectName(QStringLiteral("allAccRb"));
        allAccRb->setChecked(true);

        gridLayout->addWidget(allAccRb, 2, 1, 1, 2);

        oneAccRb = new QRadioButton(GenerateAccountCardReport);
        oneAccRb->setObjectName(QStringLiteral("oneAccRb"));

        gridLayout->addWidget(oneAccRb, 2, 3, 1, 2);

        QWidget::setTabOrder(fromDateEdit, tillDateEdit);
        QWidget::setTabOrder(tillDateEdit, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(GenerateAccountCardReport);

        QMetaObject::connectSlotsByName(GenerateAccountCardReport);
    } // setupUi

    void retranslateUi(QDialog *GenerateAccountCardReport)
    {
        GenerateAccountCardReport->setWindowTitle(QApplication::translate("GenerateAccountCardReport", "Generate account card report", 0));
        fromLb->setText(QApplication::translate("GenerateAccountCardReport", "From date:", 0));
        label_2->setText(QApplication::translate("GenerateAccountCardReport", "till date:", 0));
        okBtn->setText(QApplication::translate("GenerateAccountCardReport", "OK", 0));
        cancelBtn->setText(QApplication::translate("GenerateAccountCardReport", "Cancel", 0));
        label->setText(QApplication::translate("GenerateAccountCardReport", "Generate account card report for period", 0));
        accLb->setText(QApplication::translate("GenerateAccountCardReport", "Enter account number:", 0));
        orLb->setText(QApplication::translate("GenerateAccountCardReport", "OR", 0));
        sAccBtn->setText(QApplication::translate("GenerateAccountCardReport", "Select subaccount", 0));
        accBtn->setText(QApplication::translate("GenerateAccountCardReport", "Select account", 0));
        accNameLb->setText(QApplication::translate("GenerateAccountCardReport", "Account name:", 0));
        accNumberEdit->setText(QString());
        accNamePh->setText(QString());
        allAccRb->setText(QApplication::translate("GenerateAccountCardReport", "For all accounts", 0));
        oneAccRb->setText(QApplication::translate("GenerateAccountCardReport", "For one account or subaccount", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateAccountCardReport: public Ui_GenerateAccountCardReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEACCREPDLG_H
