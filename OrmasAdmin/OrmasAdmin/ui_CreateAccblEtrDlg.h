/********************************************************************************
** Form generated from reading UI file 'CreateAccblEtrDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEACCBLETRDLG_H
#define UI_CREATEACCBLETRDLG_H

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

class Ui_CreateAccblEntry
{
public:
    QGridLayout *gridLayout;
    QLineEdit *daIDEdit;
    QLineEdit *daNumberEdit;
    QLineEdit *valueEdit;
    QLabel *caNamePh;
    QLabel *orLb_2;
    QLabel *daNamePh;
    QPushButton *dSubAccBtn;
    QPushButton *cSubAccBtn;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *addBtn;
    QPushButton *deleteBtn;
    QPushButton *cancelBtn;
    QLabel *caNameLb;
    QLabel *daLb;
    QLineEdit *daSubIDEdit;
    QLabel *valueLb;
    QLineEdit *caIDEdit;
    QPushButton *cAccBtn;
    QPushButton *dAccBtn;
    QLabel *daNameLb;
    QLabel *orLb;
    QLabel *caLb;
    QLineEdit *caNumberEdit;
    QLineEdit *caSubIDEdit;
    QComboBox *routingCmb;
    QLabel *routingLb;

    void setupUi(QDialog *CreateAccblEntry)
    {
        if (CreateAccblEntry->objectName().isEmpty())
            CreateAccblEntry->setObjectName(QStringLiteral("CreateAccblEntry"));
        CreateAccblEntry->resize(726, 358);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CreateAccblEntry->sizePolicy().hasHeightForWidth());
        CreateAccblEntry->setSizePolicy(sizePolicy);
        CreateAccblEntry->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateAccblEntry->setModal(false);
        gridLayout = new QGridLayout(CreateAccblEntry);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        daIDEdit = new QLineEdit(CreateAccblEntry);
        daIDEdit->setObjectName(QStringLiteral("daIDEdit"));
        daIDEdit->setMaximumSize(QSize(120, 16777215));
        daIDEdit->setReadOnly(true);

        gridLayout->addWidget(daIDEdit, 1, 1, 1, 1);

        daNumberEdit = new QLineEdit(CreateAccblEntry);
        daNumberEdit->setObjectName(QStringLiteral("daNumberEdit"));
        daNumberEdit->setMinimumSize(QSize(150, 0));
        daNumberEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(daNumberEdit, 1, 4, 1, 1);

        valueEdit = new QLineEdit(CreateAccblEntry);
        valueEdit->setObjectName(QStringLiteral("valueEdit"));
        valueEdit->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(valueEdit, 5, 1, 1, 2);

        caNamePh = new QLabel(CreateAccblEntry);
        caNamePh->setObjectName(QStringLiteral("caNamePh"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(caNamePh->sizePolicy().hasHeightForWidth());
        caNamePh->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        caNamePh->setFont(font);
        caNamePh->setTextFormat(Qt::RichText);

        gridLayout->addWidget(caNamePh, 10, 0, 1, 5);

        orLb_2 = new QLabel(CreateAccblEntry);
        orLb_2->setObjectName(QStringLiteral("orLb_2"));
        orLb_2->setMinimumSize(QSize(40, 0));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        orLb_2->setFont(font1);
        orLb_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(orLb_2, 6, 2, 1, 1);

        daNamePh = new QLabel(CreateAccblEntry);
        daNamePh->setObjectName(QStringLiteral("daNamePh"));
        sizePolicy1.setHeightForWidth(daNamePh->sizePolicy().hasHeightForWidth());
        daNamePh->setSizePolicy(sizePolicy1);
        daNamePh->setFont(font);
        daNamePh->setTextFormat(Qt::RichText);
        daNamePh->setScaledContents(true);

        gridLayout->addWidget(daNamePh, 4, 0, 1, 5);

        dSubAccBtn = new QPushButton(CreateAccblEntry);
        dSubAccBtn->setObjectName(QStringLiteral("dSubAccBtn"));

        gridLayout->addWidget(dSubAccBtn, 2, 0, 1, 1);

        cSubAccBtn = new QPushButton(CreateAccblEntry);
        cSubAccBtn->setObjectName(QStringLiteral("cSubAccBtn"));

        gridLayout->addWidget(cSubAccBtn, 7, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addBtn = new QPushButton(CreateAccblEntry);
        addBtn->setObjectName(QStringLiteral("addBtn"));

        horizontalLayout->addWidget(addBtn);

        deleteBtn = new QPushButton(CreateAccblEntry);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));

        horizontalLayout->addWidget(deleteBtn);

        cancelBtn = new QPushButton(CreateAccblEntry);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 11, 0, 1, 5);

        caNameLb = new QLabel(CreateAccblEntry);
        caNameLb->setObjectName(QStringLiteral("caNameLb"));

        gridLayout->addWidget(caNameLb, 8, 0, 1, 1);

        daLb = new QLabel(CreateAccblEntry);
        daLb->setObjectName(QStringLiteral("daLb"));

        gridLayout->addWidget(daLb, 1, 3, 1, 1);

        daSubIDEdit = new QLineEdit(CreateAccblEntry);
        daSubIDEdit->setObjectName(QStringLiteral("daSubIDEdit"));
        daSubIDEdit->setReadOnly(true);

        gridLayout->addWidget(daSubIDEdit, 2, 1, 1, 1);

        valueLb = new QLabel(CreateAccblEntry);
        valueLb->setObjectName(QStringLiteral("valueLb"));
        valueLb->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(valueLb, 5, 0, 1, 1);

        caIDEdit = new QLineEdit(CreateAccblEntry);
        caIDEdit->setObjectName(QStringLiteral("caIDEdit"));
        caIDEdit->setMaximumSize(QSize(120, 16777215));
        caIDEdit->setReadOnly(true);

        gridLayout->addWidget(caIDEdit, 6, 1, 1, 1);

        cAccBtn = new QPushButton(CreateAccblEntry);
        cAccBtn->setObjectName(QStringLiteral("cAccBtn"));

        gridLayout->addWidget(cAccBtn, 6, 0, 1, 1);

        dAccBtn = new QPushButton(CreateAccblEntry);
        dAccBtn->setObjectName(QStringLiteral("dAccBtn"));

        gridLayout->addWidget(dAccBtn, 1, 0, 1, 1);

        daNameLb = new QLabel(CreateAccblEntry);
        daNameLb->setObjectName(QStringLiteral("daNameLb"));

        gridLayout->addWidget(daNameLb, 3, 0, 1, 1);

        orLb = new QLabel(CreateAccblEntry);
        orLb->setObjectName(QStringLiteral("orLb"));
        orLb->setMinimumSize(QSize(40, 0));
        orLb->setFont(font1);
        orLb->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(orLb, 1, 2, 1, 1);

        caLb = new QLabel(CreateAccblEntry);
        caLb->setObjectName(QStringLiteral("caLb"));

        gridLayout->addWidget(caLb, 6, 3, 1, 1);

        caNumberEdit = new QLineEdit(CreateAccblEntry);
        caNumberEdit->setObjectName(QStringLiteral("caNumberEdit"));
        caNumberEdit->setMinimumSize(QSize(150, 0));
        caNumberEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(caNumberEdit, 6, 4, 1, 1);

        caSubIDEdit = new QLineEdit(CreateAccblEntry);
        caSubIDEdit->setObjectName(QStringLiteral("caSubIDEdit"));
        caSubIDEdit->setReadOnly(true);

        gridLayout->addWidget(caSubIDEdit, 7, 1, 1, 1);

        routingCmb = new QComboBox(CreateAccblEntry);
        routingCmb->setObjectName(QStringLiteral("routingCmb"));

        gridLayout->addWidget(routingCmb, 0, 1, 1, 4);

        routingLb = new QLabel(CreateAccblEntry);
        routingLb->setObjectName(QStringLiteral("routingLb"));

        gridLayout->addWidget(routingLb, 0, 0, 1, 1);

        QWidget::setTabOrder(dAccBtn, daNumberEdit);
        QWidget::setTabOrder(daNumberEdit, dSubAccBtn);
        QWidget::setTabOrder(dSubAccBtn, valueEdit);
        QWidget::setTabOrder(valueEdit, cAccBtn);
        QWidget::setTabOrder(cAccBtn, caNumberEdit);
        QWidget::setTabOrder(caNumberEdit, cSubAccBtn);
        QWidget::setTabOrder(cSubAccBtn, addBtn);
        QWidget::setTabOrder(addBtn, cancelBtn);
        QWidget::setTabOrder(cancelBtn, daIDEdit);
        QWidget::setTabOrder(daIDEdit, caIDEdit);

        retranslateUi(CreateAccblEntry);

        QMetaObject::connectSlotsByName(CreateAccblEntry);
    } // setupUi

    void retranslateUi(QDialog *CreateAccblEntry)
    {
        CreateAccblEntry->setWindowTitle(QApplication::translate("CreateAccblEntry", "Create entry", 0));
        daNumberEdit->setText(QString());
        caNamePh->setText(QString());
        orLb_2->setText(QApplication::translate("CreateAccblEntry", "OR", 0));
        daNamePh->setText(QString());
        dSubAccBtn->setText(QApplication::translate("CreateAccblEntry", "Select debiting subaccount", 0));
        cSubAccBtn->setText(QApplication::translate("CreateAccblEntry", "Select crediting subaccount", 0));
        addBtn->setText(QApplication::translate("CreateAccblEntry", "Add", 0));
        deleteBtn->setText(QApplication::translate("CreateAccblEntry", "Delete", 0));
        cancelBtn->setText(QApplication::translate("CreateAccblEntry", "Cancel", 0));
        caNameLb->setText(QApplication::translate("CreateAccblEntry", "Crediting account name:", 0));
        daLb->setText(QApplication::translate("CreateAccblEntry", "Enter debiting account number:", 0));
        valueLb->setText(QApplication::translate("CreateAccblEntry", "Value:", 0));
        cAccBtn->setText(QApplication::translate("CreateAccblEntry", "Select crediting account", 0));
        dAccBtn->setText(QApplication::translate("CreateAccblEntry", "Select debiting account", 0));
        daNameLb->setText(QApplication::translate("CreateAccblEntry", "Debiting account name:", 0));
        orLb->setText(QApplication::translate("CreateAccblEntry", "OR", 0));
        caLb->setText(QApplication::translate("CreateAccblEntry", "Enter crediting account number:", 0));
        caNumberEdit->setText(QString());
        routingLb->setText(QApplication::translate("CreateAccblEntry", "Select appointment:", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateAccblEntry: public Ui_CreateAccblEntry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEACCBLETRDLG_H
