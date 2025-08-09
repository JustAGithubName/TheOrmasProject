/********************************************************************************
** Form generated from reading UI file 'CreateMcurDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEMCURDLG_H
#define UI_CREATEMCURDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateMulticurrency
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QTabWidget *tabWidget;
    QWidget *newTab;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *numberLb;
    QLineEdit *mianNumberEdit;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *chartOfAccBtn;
    QLineEdit *chartOfAccEdit;
    QLabel *accNameLb;
    QLabel *label;
    QLabel *accNamePh;
    QLabel *sBalanceLb;
    QLineEdit *currentBalanceEdit;
    QLabel *currencyLb;
    QLineEdit *detailsEdit;
    QDateEdit *openedDateEdit;
    QLabel *cBalanceLb;
    QLineEdit *startBalanceEdit;
    QComboBox *subCurrencyCmb;
    QLabel *firmLb;
    QLabel *oDateLb;
    QWidget *statusWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *statusBtn;
    QLineEdit *statusEdit;
    QLabel *statusLb;
    QLabel *statusPh;
    QLineEdit *subNumberEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *mainCurShortNamePh;
    QLineEdit *mainCurEdit;
    QWidget *selectTab;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QLineEdit *mainSubaccEdit;
    QPushButton *selectMainSubaccount;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *newNumberEdit;
    QLineEdit *mainSubaccNumberEdit;
    QLabel *label_6;
    QLineEdit *newCurrentBalanceEdit;
    QLabel *label_7;
    QLineEdit *newStartBalanceEdit;
    QLabel *label_8;
    QLabel *selLb;
    QComboBox *currencyCmb;
    QLineEdit *newDetailsEdit;
    QLineEdit *commonStartBalanceEdit;
    QLineEdit *commonEndBalanceEdit;
    QLabel *label_9;
    QLabel *label_10;

    void setupUi(QDialog *CreateMulticurrency)
    {
        if (CreateMulticurrency->objectName().isEmpty())
            CreateMulticurrency->setObjectName(QStringLiteral("CreateMulticurrency"));
        CreateMulticurrency->resize(700, 477);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CreateMulticurrency->sizePolicy().hasHeightForWidth());
        CreateMulticurrency->setSizePolicy(sizePolicy);
        CreateMulticurrency->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateMulticurrency->setModal(false);
        gridLayout = new QGridLayout(CreateMulticurrency);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreateMulticurrency);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(CreateMulticurrency);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 2);

        tabWidget = new QTabWidget(CreateMulticurrency);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        newTab = new QWidget();
        newTab->setObjectName(QStringLiteral("newTab"));
        gridLayout_3 = new QGridLayout(newTab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(newTab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        numberLb = new QLabel(groupBox);
        numberLb->setObjectName(QStringLiteral("numberLb"));
        numberLb->setMinimumSize(QSize(120, 0));

        gridLayout_2->addWidget(numberLb, 0, 0, 1, 1);

        mianNumberEdit = new QLineEdit(groupBox);
        mianNumberEdit->setObjectName(QStringLiteral("mianNumberEdit"));
        mianNumberEdit->setMinimumSize(QSize(150, 0));
        mianNumberEdit->setMaximumSize(QSize(150, 16777215));
        mianNumberEdit->setReadOnly(true);

        gridLayout_2->addWidget(mianNumberEdit, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        chartOfAccBtn = new QPushButton(groupBox);
        chartOfAccBtn->setObjectName(QStringLiteral("chartOfAccBtn"));

        gridLayout_2->addWidget(chartOfAccBtn, 2, 0, 1, 1);

        chartOfAccEdit = new QLineEdit(groupBox);
        chartOfAccEdit->setObjectName(QStringLiteral("chartOfAccEdit"));
        chartOfAccEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(chartOfAccEdit, 2, 1, 1, 1);

        accNameLb = new QLabel(groupBox);
        accNameLb->setObjectName(QStringLiteral("accNameLb"));

        gridLayout_2->addWidget(accNameLb, 3, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 2, 1, 1);

        accNamePh = new QLabel(groupBox);
        accNamePh->setObjectName(QStringLiteral("accNamePh"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        accNamePh->setFont(font);

        gridLayout_2->addWidget(accNamePh, 3, 1, 1, 3);

        sBalanceLb = new QLabel(groupBox);
        sBalanceLb->setObjectName(QStringLiteral("sBalanceLb"));

        gridLayout_2->addWidget(sBalanceLb, 4, 0, 1, 1);

        currentBalanceEdit = new QLineEdit(groupBox);
        currentBalanceEdit->setObjectName(QStringLiteral("currentBalanceEdit"));
        currentBalanceEdit->setMinimumSize(QSize(150, 0));
        currentBalanceEdit->setMaximumSize(QSize(150, 16777215));
        currentBalanceEdit->setReadOnly(true);

        gridLayout_2->addWidget(currentBalanceEdit, 5, 1, 1, 1);

        currencyLb = new QLabel(groupBox);
        currencyLb->setObjectName(QStringLiteral("currencyLb"));
        currencyLb->setMinimumSize(QSize(150, 0));

        gridLayout_2->addWidget(currencyLb, 6, 0, 1, 1);

        detailsEdit = new QLineEdit(groupBox);
        detailsEdit->setObjectName(QStringLiteral("detailsEdit"));
        detailsEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(detailsEdit, 10, 1, 1, 1);

        openedDateEdit = new QDateEdit(groupBox);
        openedDateEdit->setObjectName(QStringLiteral("openedDateEdit"));
        openedDateEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(openedDateEdit, 9, 1, 1, 1);

        cBalanceLb = new QLabel(groupBox);
        cBalanceLb->setObjectName(QStringLiteral("cBalanceLb"));

        gridLayout_2->addWidget(cBalanceLb, 5, 0, 1, 1);

        startBalanceEdit = new QLineEdit(groupBox);
        startBalanceEdit->setObjectName(QStringLiteral("startBalanceEdit"));
        startBalanceEdit->setMinimumSize(QSize(150, 0));
        startBalanceEdit->setMaximumSize(QSize(150, 16777215));
        startBalanceEdit->setReadOnly(true);

        gridLayout_2->addWidget(startBalanceEdit, 4, 1, 1, 1);

        subCurrencyCmb = new QComboBox(groupBox);
        subCurrencyCmb->setObjectName(QStringLiteral("subCurrencyCmb"));
        subCurrencyCmb->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(subCurrencyCmb, 6, 1, 1, 1);

        firmLb = new QLabel(groupBox);
        firmLb->setObjectName(QStringLiteral("firmLb"));

        gridLayout_2->addWidget(firmLb, 10, 0, 1, 1);

        oDateLb = new QLabel(groupBox);
        oDateLb->setObjectName(QStringLiteral("oDateLb"));

        gridLayout_2->addWidget(oDateLb, 9, 0, 1, 1);

        statusWidget = new QWidget(groupBox);
        statusWidget->setObjectName(QStringLiteral("statusWidget"));
        horizontalLayout_3 = new QHBoxLayout(statusWidget);
        horizontalLayout_3->setSpacing(9);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        statusBtn = new QPushButton(statusWidget);
        statusBtn->setObjectName(QStringLiteral("statusBtn"));
        sizePolicy.setHeightForWidth(statusBtn->sizePolicy().hasHeightForWidth());
        statusBtn->setSizePolicy(sizePolicy);
        statusBtn->setMinimumSize(QSize(150, 0));

        horizontalLayout_3->addWidget(statusBtn);

        statusEdit = new QLineEdit(statusWidget);
        statusEdit->setObjectName(QStringLiteral("statusEdit"));
        statusEdit->setMinimumSize(QSize(150, 0));
        statusEdit->setMaximumSize(QSize(150, 16777215));
        statusEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(statusEdit);

        statusLb = new QLabel(statusWidget);
        statusLb->setObjectName(QStringLiteral("statusLb"));

        horizontalLayout_3->addWidget(statusLb);

        statusPh = new QLabel(statusWidget);
        statusPh->setObjectName(QStringLiteral("statusPh"));
        statusPh->setMinimumSize(QSize(120, 0));
        statusPh->setFont(font);

        horizontalLayout_3->addWidget(statusPh);


        gridLayout_2->addWidget(statusWidget, 8, 0, 1, 4);

        subNumberEdit = new QLineEdit(groupBox);
        subNumberEdit->setObjectName(QStringLiteral("subNumberEdit"));
        subNumberEdit->setReadOnly(true);

        gridLayout_2->addWidget(subNumberEdit, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 7, 0, 1, 1);

        mainCurShortNamePh = new QLabel(groupBox);
        mainCurShortNamePh->setObjectName(QStringLiteral("mainCurShortNamePh"));

        gridLayout_2->addWidget(mainCurShortNamePh, 7, 1, 1, 1);

        mainCurEdit = new QLineEdit(groupBox);
        mainCurEdit->setObjectName(QStringLiteral("mainCurEdit"));
        mainCurEdit->setReadOnly(true);

        gridLayout_2->addWidget(mainCurEdit, 7, 2, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        tabWidget->addTab(newTab, QString());
        selectTab = new QWidget();
        selectTab->setObjectName(QStringLiteral("selectTab"));
        gridLayout_4 = new QGridLayout(selectTab);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox_2 = new QGroupBox(selectTab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        mainSubaccEdit = new QLineEdit(groupBox_2);
        mainSubaccEdit->setObjectName(QStringLiteral("mainSubaccEdit"));
        mainSubaccEdit->setReadOnly(true);

        gridLayout_5->addWidget(mainSubaccEdit, 0, 1, 1, 1);

        selectMainSubaccount = new QPushButton(groupBox_2);
        selectMainSubaccount->setObjectName(QStringLiteral("selectMainSubaccount"));

        gridLayout_5->addWidget(selectMainSubaccount, 0, 0, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_5->addWidget(label_4, 2, 0, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_5->addWidget(label_5, 2, 2, 1, 1);

        newNumberEdit = new QLineEdit(groupBox_2);
        newNumberEdit->setObjectName(QStringLiteral("newNumberEdit"));
        newNumberEdit->setReadOnly(true);

        gridLayout_5->addWidget(newNumberEdit, 2, 1, 1, 1);

        mainSubaccNumberEdit = new QLineEdit(groupBox_2);
        mainSubaccNumberEdit->setObjectName(QStringLiteral("mainSubaccNumberEdit"));
        mainSubaccNumberEdit->setReadOnly(true);

        gridLayout_5->addWidget(mainSubaccNumberEdit, 0, 2, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_5->addWidget(label_6, 3, 0, 1, 1);

        newCurrentBalanceEdit = new QLineEdit(groupBox_2);
        newCurrentBalanceEdit->setObjectName(QStringLiteral("newCurrentBalanceEdit"));

        gridLayout_5->addWidget(newCurrentBalanceEdit, 4, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 4, 0, 1, 1);

        newStartBalanceEdit = new QLineEdit(groupBox_2);
        newStartBalanceEdit->setObjectName(QStringLiteral("newStartBalanceEdit"));

        gridLayout_5->addWidget(newStartBalanceEdit, 3, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_5->addWidget(label_8, 6, 0, 1, 1);

        selLb = new QLabel(groupBox_2);
        selLb->setObjectName(QStringLiteral("selLb"));

        gridLayout_5->addWidget(selLb, 5, 0, 1, 1);

        currencyCmb = new QComboBox(groupBox_2);
        currencyCmb->setObjectName(QStringLiteral("currencyCmb"));

        gridLayout_5->addWidget(currencyCmb, 5, 1, 1, 1);

        newDetailsEdit = new QLineEdit(groupBox_2);
        newDetailsEdit->setObjectName(QStringLiteral("newDetailsEdit"));

        gridLayout_5->addWidget(newDetailsEdit, 6, 1, 1, 2);

        commonStartBalanceEdit = new QLineEdit(groupBox_2);
        commonStartBalanceEdit->setObjectName(QStringLiteral("commonStartBalanceEdit"));
        commonStartBalanceEdit->setReadOnly(true);

        gridLayout_5->addWidget(commonStartBalanceEdit, 1, 1, 1, 1);

        commonEndBalanceEdit = new QLineEdit(groupBox_2);
        commonEndBalanceEdit->setObjectName(QStringLiteral("commonEndBalanceEdit"));
        commonEndBalanceEdit->setReadOnly(true);

        gridLayout_5->addWidget(commonEndBalanceEdit, 1, 2, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_5->addWidget(label_9, 3, 2, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_5->addWidget(label_10, 4, 2, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 0, 0, 1, 1);

        tabWidget->addTab(selectTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        QWidget::setTabOrder(statusBtn, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);
        QWidget::setTabOrder(cancelBtn, statusEdit);

        retranslateUi(CreateMulticurrency);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CreateMulticurrency);
    } // setupUi

    void retranslateUi(QDialog *CreateMulticurrency)
    {
        CreateMulticurrency->setWindowTitle(QApplication::translate("CreateMulticurrency", "Create/Update multicurrency", 0));
        okBtn->setText(QApplication::translate("CreateMulticurrency", "OK", 0));
        cancelBtn->setText(QApplication::translate("CreateMulticurrency", "Cancel", 0));
        groupBox->setTitle(QApplication::translate("CreateMulticurrency", "New multicurrency", 0));
        numberLb->setText(QApplication::translate("CreateMulticurrency", "Main number:", 0));
#ifndef QT_NO_TOOLTIP
        mianNumberEdit->setToolTip(QApplication::translate("CreateMulticurrency", "<html><head/><body><p>For example: John</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        chartOfAccBtn->setText(QApplication::translate("CreateMulticurrency", "Select accout from chart", 0));
        accNameLb->setText(QApplication::translate("CreateMulticurrency", "Account name:", 0));
        label->setText(QApplication::translate("CreateMulticurrency", "Number will generate from other parameters", 0));
        accNamePh->setText(QString());
        sBalanceLb->setText(QApplication::translate("CreateMulticurrency", "Start balance:", 0));
#ifndef QT_NO_TOOLTIP
        currentBalanceEdit->setToolTip(QApplication::translate("CreateMulticurrency", "<html><head/><body><p>For example: John.Doe@gmail.com (does not mandatory field)</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        currentBalanceEdit->setText(QApplication::translate("CreateMulticurrency", "0", 0));
        currencyLb->setText(QApplication::translate("CreateMulticurrency", "Select currency:", 0));
#ifndef QT_NO_TOOLTIP
        detailsEdit->setToolTip(QApplication::translate("CreateMulticurrency", "<html><head/><body><p>For example: &quot;Mango Company&quot;</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        cBalanceLb->setText(QApplication::translate("CreateMulticurrency", "Current balance:", 0));
#ifndef QT_NO_TOOLTIP
        startBalanceEdit->setToolTip(QApplication::translate("CreateMulticurrency", "<html><head/><body><p>For example: Doe</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        startBalanceEdit->setText(QApplication::translate("CreateMulticurrency", "0", 0));
        firmLb->setText(QApplication::translate("CreateMulticurrency", "Details:", 0));
        oDateLb->setText(QApplication::translate("CreateMulticurrency", "Opened date:", 0));
        statusBtn->setText(QApplication::translate("CreateMulticurrency", "Change status", 0));
        statusLb->setText(QApplication::translate("CreateMulticurrency", "Status name:", 0));
        statusPh->setText(QString());
        label_2->setText(QApplication::translate("CreateMulticurrency", "Sub number:", 0));
        label_3->setText(QApplication::translate("CreateMulticurrency", "Main currency:", 0));
        mainCurShortNamePh->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(newTab), QApplication::translate("CreateMulticurrency", "New Multicurency", 0));
        groupBox_2->setTitle(QApplication::translate("CreateMulticurrency", "Add multicurrency", 0));
        selectMainSubaccount->setText(QApplication::translate("CreateMulticurrency", "Select subaccount", 0));
        label_4->setText(QApplication::translate("CreateMulticurrency", "New sub number:", 0));
        label_5->setText(QApplication::translate("CreateMulticurrency", "Number will generate from other parameters", 0));
        label_6->setText(QApplication::translate("CreateMulticurrency", "Start balance:", 0));
        newCurrentBalanceEdit->setText(QApplication::translate("CreateMulticurrency", "0", 0));
        label_7->setText(QApplication::translate("CreateMulticurrency", "Current balance:", 0));
        newStartBalanceEdit->setText(QApplication::translate("CreateMulticurrency", "0", 0));
        label_8->setText(QApplication::translate("CreateMulticurrency", "Details:", 0));
        selLb->setText(QApplication::translate("CreateMulticurrency", "Select currency:", 0));
        label_9->setText(QApplication::translate("CreateMulticurrency", "If account is PASSIVE then value is negative", 0));
        label_10->setText(QApplication::translate("CreateMulticurrency", "and starts with - , for example -500", 0));
        tabWidget->setTabText(tabWidget->indexOf(selectTab), QApplication::translate("CreateMulticurrency", "Add multicurrency", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateMulticurrency: public Ui_CreateMulticurrency {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEMCURDLG_H
