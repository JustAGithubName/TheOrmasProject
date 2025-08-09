/********************************************************************************
** Form generated from reading UI file 'CreatePrExDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEPREXDLG_H
#define UI_CREATEPREXDLG_H

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
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CreatePriceExtension
{
public:
    QGridLayout *gridLayout;
    QSpinBox *daySpb;
    QLabel *clientNamePh;
    QLineEdit *locationEdit;
    QLabel *clientNameLb;
    QDateEdit *dateEdit;
    QLabel *dateLb;
    QLabel *dayCountLb;
    QLabel *clientSurnamePh;
    QLabel *valueLb;
    QLineEdit *valueEdit;
    QLabel *clientPhonePh;
    QLabel *clientPhoneLb;
    QLabel *cityNameLb;
    QLabel *regionNamePh;
    QLabel *rgNameLb;
    QPushButton *clientBtn;
    QLabel *label_2;
    QPushButton *productBtn;
    QLineEdit *productEdit;
    QLineEdit *clientEdit;
    QPushButton *locationBtn;
    QLabel *brNameLb;
    QLineEdit *branchEdit;
    QPushButton *branchBtn;
    QLabel *prNameLb;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLabel *prNamePh;
    QLabel *prPriceLb;
    QLabel *prPricePh;
    QLabel *brNamePh;
    QLabel *cityNamePh;
    QLabel *label;
    QPushButton *expeditorBtn;
    QLineEdit *expeditorEdit;
    QLabel *expeditorNamePh;
    QLabel *label_4;
    QLabel *expeditorSurnamePh;
    QLabel *Expeditorphone;
    QLabel *expeditorPhonePh;

    void setupUi(QDialog *CreatePriceExtension)
    {
        if (CreatePriceExtension->objectName().isEmpty())
            CreatePriceExtension->setObjectName(QStringLiteral("CreatePriceExtension"));
        CreatePriceExtension->resize(1085, 542);
        CreatePriceExtension->setMinimumSize(QSize(150, 0));
        CreatePriceExtension->setMaximumSize(QSize(16777215, 16777215));
        CreatePriceExtension->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreatePriceExtension->setModal(false);
        gridLayout = new QGridLayout(CreatePriceExtension);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        daySpb = new QSpinBox(CreatePriceExtension);
        daySpb->setObjectName(QStringLiteral("daySpb"));
        daySpb->setMaximum(365);

        gridLayout->addWidget(daySpb, 3, 4, 1, 1);

        clientNamePh = new QLabel(CreatePriceExtension);
        clientNamePh->setObjectName(QStringLiteral("clientNamePh"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        clientNamePh->setFont(font);

        gridLayout->addWidget(clientNamePh, 11, 1, 1, 1);

        locationEdit = new QLineEdit(CreatePriceExtension);
        locationEdit->setObjectName(QStringLiteral("locationEdit"));
        locationEdit->setReadOnly(true);

        gridLayout->addWidget(locationEdit, 8, 2, 1, 2);

        clientNameLb = new QLabel(CreatePriceExtension);
        clientNameLb->setObjectName(QStringLiteral("clientNameLb"));

        gridLayout->addWidget(clientNameLb, 11, 0, 1, 1);

        dateEdit = new QDateEdit(CreatePriceExtension);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));

        gridLayout->addWidget(dateEdit, 3, 1, 1, 2);

        dateLb = new QLabel(CreatePriceExtension);
        dateLb->setObjectName(QStringLiteral("dateLb"));

        gridLayout->addWidget(dateLb, 3, 0, 1, 1);

        dayCountLb = new QLabel(CreatePriceExtension);
        dayCountLb->setObjectName(QStringLiteral("dayCountLb"));

        gridLayout->addWidget(dayCountLb, 3, 3, 1, 1);

        clientSurnamePh = new QLabel(CreatePriceExtension);
        clientSurnamePh->setObjectName(QStringLiteral("clientSurnamePh"));
        clientSurnamePh->setFont(font);

        gridLayout->addWidget(clientSurnamePh, 11, 3, 1, 1);

        valueLb = new QLabel(CreatePriceExtension);
        valueLb->setObjectName(QStringLiteral("valueLb"));

        gridLayout->addWidget(valueLb, 2, 0, 1, 1);

        valueEdit = new QLineEdit(CreatePriceExtension);
        valueEdit->setObjectName(QStringLiteral("valueEdit"));

        gridLayout->addWidget(valueEdit, 2, 1, 1, 2);

        clientPhonePh = new QLabel(CreatePriceExtension);
        clientPhonePh->setObjectName(QStringLiteral("clientPhonePh"));
        clientPhonePh->setFont(font);

        gridLayout->addWidget(clientPhonePh, 11, 5, 1, 1);

        clientPhoneLb = new QLabel(CreatePriceExtension);
        clientPhoneLb->setObjectName(QStringLiteral("clientPhoneLb"));

        gridLayout->addWidget(clientPhoneLb, 11, 4, 1, 1);

        cityNameLb = new QLabel(CreatePriceExtension);
        cityNameLb->setObjectName(QStringLiteral("cityNameLb"));
        cityNameLb->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(cityNameLb, 9, 3, 1, 1);

        regionNamePh = new QLabel(CreatePriceExtension);
        regionNamePh->setObjectName(QStringLiteral("regionNamePh"));
        regionNamePh->setFont(font);

        gridLayout->addWidget(regionNamePh, 9, 1, 1, 2);

        rgNameLb = new QLabel(CreatePriceExtension);
        rgNameLb->setObjectName(QStringLiteral("rgNameLb"));

        gridLayout->addWidget(rgNameLb, 9, 0, 1, 1);

        clientBtn = new QPushButton(CreatePriceExtension);
        clientBtn->setObjectName(QStringLiteral("clientBtn"));

        gridLayout->addWidget(clientBtn, 10, 0, 1, 2);

        label_2 = new QLabel(CreatePriceExtension);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 11, 2, 1, 1);

        productBtn = new QPushButton(CreatePriceExtension);
        productBtn->setObjectName(QStringLiteral("productBtn"));
        productBtn->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(productBtn, 0, 0, 1, 2);

        productEdit = new QLineEdit(CreatePriceExtension);
        productEdit->setObjectName(QStringLiteral("productEdit"));
        productEdit->setReadOnly(true);

        gridLayout->addWidget(productEdit, 0, 2, 1, 2);

        clientEdit = new QLineEdit(CreatePriceExtension);
        clientEdit->setObjectName(QStringLiteral("clientEdit"));
        clientEdit->setReadOnly(true);

        gridLayout->addWidget(clientEdit, 10, 2, 1, 2);

        locationBtn = new QPushButton(CreatePriceExtension);
        locationBtn->setObjectName(QStringLiteral("locationBtn"));

        gridLayout->addWidget(locationBtn, 8, 0, 1, 2);

        brNameLb = new QLabel(CreatePriceExtension);
        brNameLb->setObjectName(QStringLiteral("brNameLb"));
        brNameLb->setMinimumSize(QSize(120, 0));
        brNameLb->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(brNameLb, 7, 0, 1, 1);

        branchEdit = new QLineEdit(CreatePriceExtension);
        branchEdit->setObjectName(QStringLiteral("branchEdit"));
        branchEdit->setReadOnly(true);

        gridLayout->addWidget(branchEdit, 6, 2, 1, 2);

        branchBtn = new QPushButton(CreatePriceExtension);
        branchBtn->setObjectName(QStringLiteral("branchBtn"));

        gridLayout->addWidget(branchBtn, 6, 0, 1, 2);

        prNameLb = new QLabel(CreatePriceExtension);
        prNameLb->setObjectName(QStringLiteral("prNameLb"));
        prNameLb->setMinimumSize(QSize(120, 0));
        prNameLb->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(prNameLb, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreatePriceExtension);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(CreatePriceExtension);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 12, 0, 1, 6);

        prNamePh = new QLabel(CreatePriceExtension);
        prNamePh->setObjectName(QStringLiteral("prNamePh"));
        prNamePh->setMinimumSize(QSize(100, 0));
        prNamePh->setFont(font);

        gridLayout->addWidget(prNamePh, 1, 1, 1, 2);

        prPriceLb = new QLabel(CreatePriceExtension);
        prPriceLb->setObjectName(QStringLiteral("prPriceLb"));
        prPriceLb->setMinimumSize(QSize(120, 0));
        prPriceLb->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(prPriceLb, 1, 3, 1, 1);

        prPricePh = new QLabel(CreatePriceExtension);
        prPricePh->setObjectName(QStringLiteral("prPricePh"));
        prPricePh->setMinimumSize(QSize(100, 0));
        prPricePh->setFont(font);

        gridLayout->addWidget(prPricePh, 1, 4, 1, 2);

        brNamePh = new QLabel(CreatePriceExtension);
        brNamePh->setObjectName(QStringLiteral("brNamePh"));
        brNamePh->setMinimumSize(QSize(100, 0));
        brNamePh->setFont(font);

        gridLayout->addWidget(brNamePh, 7, 1, 1, 3);

        cityNamePh = new QLabel(CreatePriceExtension);
        cityNamePh->setObjectName(QStringLiteral("cityNamePh"));
        cityNamePh->setMinimumSize(QSize(150, 0));
        cityNamePh->setFont(font);

        gridLayout->addWidget(cityNamePh, 9, 4, 1, 2);

        label = new QLabel(CreatePriceExtension);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 5, 0, 1, 1);

        expeditorBtn = new QPushButton(CreatePriceExtension);
        expeditorBtn->setObjectName(QStringLiteral("expeditorBtn"));

        gridLayout->addWidget(expeditorBtn, 4, 0, 1, 2);

        expeditorEdit = new QLineEdit(CreatePriceExtension);
        expeditorEdit->setObjectName(QStringLiteral("expeditorEdit"));
        expeditorEdit->setReadOnly(true);

        gridLayout->addWidget(expeditorEdit, 4, 2, 1, 2);

        expeditorNamePh = new QLabel(CreatePriceExtension);
        expeditorNamePh->setObjectName(QStringLiteral("expeditorNamePh"));

        gridLayout->addWidget(expeditorNamePh, 5, 1, 1, 1);

        label_4 = new QLabel(CreatePriceExtension);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 5, 2, 1, 1);

        expeditorSurnamePh = new QLabel(CreatePriceExtension);
        expeditorSurnamePh->setObjectName(QStringLiteral("expeditorSurnamePh"));

        gridLayout->addWidget(expeditorSurnamePh, 5, 3, 1, 1);

        Expeditorphone = new QLabel(CreatePriceExtension);
        Expeditorphone->setObjectName(QStringLiteral("Expeditorphone"));

        gridLayout->addWidget(Expeditorphone, 5, 4, 1, 1);

        expeditorPhonePh = new QLabel(CreatePriceExtension);
        expeditorPhonePh->setObjectName(QStringLiteral("expeditorPhonePh"));

        gridLayout->addWidget(expeditorPhonePh, 5, 5, 1, 1);

        QWidget::setTabOrder(productBtn, branchBtn);
        QWidget::setTabOrder(branchBtn, locationBtn);
        QWidget::setTabOrder(locationBtn, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(CreatePriceExtension);

        QMetaObject::connectSlotsByName(CreatePriceExtension);
    } // setupUi

    void retranslateUi(QDialog *CreatePriceExtension)
    {
        CreatePriceExtension->setWindowTitle(QApplication::translate("CreatePriceExtension", "Create/Update price extension", 0));
        clientNamePh->setText(QString());
        clientNameLb->setText(QApplication::translate("CreatePriceExtension", "Client name:", 0));
        dateLb->setText(QApplication::translate("CreatePriceExtension", "Select date:", 0));
        dayCountLb->setText(QApplication::translate("CreatePriceExtension", "Sale time in days:", 0));
        clientSurnamePh->setText(QString());
        valueLb->setText(QApplication::translate("CreatePriceExtension", "Value:", 0));
        clientPhonePh->setText(QString());
        clientPhoneLb->setText(QApplication::translate("CreatePriceExtension", "Phone:", 0));
        cityNameLb->setText(QApplication::translate("CreatePriceExtension", "City name:", 0));
        regionNamePh->setText(QString());
        rgNameLb->setText(QApplication::translate("CreatePriceExtension", "Location name:", 0));
        clientBtn->setText(QApplication::translate("CreatePriceExtension", "Select client", 0));
        label_2->setText(QApplication::translate("CreatePriceExtension", "Client surname:", 0));
        productBtn->setText(QApplication::translate("CreatePriceExtension", "Select product", 0));
#ifndef QT_NO_TOOLTIP
        productEdit->setToolTip(QApplication::translate("CreatePriceExtension", "<html><head/><body><p>Enter client ID</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        locationBtn->setText(QApplication::translate("CreatePriceExtension", "Select location", 0));
        brNameLb->setText(QApplication::translate("CreatePriceExtension", "Branch name:", 0));
#ifndef QT_NO_TOOLTIP
        branchEdit->setToolTip(QApplication::translate("CreatePriceExtension", "<html><head/><body><p>Enter employee ID</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        branchBtn->setText(QApplication::translate("CreatePriceExtension", "Select branch", 0));
        prNameLb->setText(QApplication::translate("CreatePriceExtension", "Product name:", 0));
        okBtn->setText(QApplication::translate("CreatePriceExtension", "OK", 0));
        cancelBtn->setText(QApplication::translate("CreatePriceExtension", "Cancel", 0));
        prNamePh->setText(QString());
        prPriceLb->setText(QApplication::translate("CreatePriceExtension", "Product price", 0));
        prPricePh->setText(QString());
        brNamePh->setText(QString());
        cityNamePh->setText(QString());
        label->setText(QApplication::translate("CreatePriceExtension", "Expeditor name:", 0));
        expeditorBtn->setText(QApplication::translate("CreatePriceExtension", "Select expeditor", 0));
        expeditorNamePh->setText(QString());
        label_4->setText(QApplication::translate("CreatePriceExtension", "Expeditor surname:", 0));
        expeditorSurnamePh->setText(QString());
        Expeditorphone->setText(QApplication::translate("CreatePriceExtension", "Expeditor phone:", 0));
        expeditorPhonePh->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CreatePriceExtension: public Ui_CreatePriceExtension {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEPREXDLG_H
