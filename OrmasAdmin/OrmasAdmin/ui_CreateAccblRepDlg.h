/********************************************************************************
** Form generated from reading UI file 'CreateAccblRepDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEACCBLREPDLG_H
#define UI_CREATEACCBLREPDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateAccountableRep
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QTabWidget *tabWidget;
    QWidget *oneDocTab;
    QGridLayout *gridLayout_2;
    QLabel *BranchLb;
    QLabel *headerLb;
    QLabel *branchPh;
    QLabel *positionLb;
    QLabel *datelb;
    QLabel *reportNumberPh;
    QLabel *positionPh;
    QLabel *rolePh;
    QLabel *expenseLb;
    QLineEdit *appointmentEdit;
    QLineEdit *companyEdit;
    QLabel *companyPh;
    QLabel *companyLb;
    QPushButton *cmpBtn;
    QLabel *roleLb;
    QDateTimeEdit *reprotDateEdit;
    QLabel *approveLb;
    QDateTimeEdit *approveDateEdit;
    QLabel *statusPh;
    QLabel *directorLb;
    QLabel *directorPh;
    QPushButton *accontantBtn;
    QPushButton *directorBtn;
    QLabel *label_10;
    QLineEdit *directorEdit;
    QLineEdit *accountantEdit;
    QComboBox *currCmb;
    QLabel *label_9;
    QLineEdit *statusEdit;
    QPushButton *stsBtn;
    QLabel *curLb;
    QLabel *label;
    QLabel *employeePh;
    QLineEdit *employeeEdit;
    QPushButton *empBtn;
    QLabel *accountantPh;
    QGroupBox *sumGrb;
    QGridLayout *gridLayout_3;
    QLineEdit *spentEdit;
    QLabel *label_5;
    QLabel *label_7;
    QLineEdit *totalEdit;
    QLabel *label_12;
    QPushButton *addPaymentBtn;
    QFrame *line;
    QPushButton *deleteWithdrawalBtn;
    QPushButton *addWithdrawalBtn;
    QTableView *paymentTableView;
    QLabel *prevLb;
    QFrame *line_3;
    QLabel *label_4;
    QLineEdit *prevOverrunEdit;
    QLineEdit *prevRemainderEdit;
    QSpacerItem *horizontalSpacer_6;
    QFrame *line_2;
    QLabel *label_2;
    QLineEdit *remainderEdit;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_3;
    QLabel *label_6;
    QPushButton *deletePaymentBtn;
    QLineEdit *overrunEdit;
    QLabel *label_8;
    QTableView *withdrawalTableView;
    QWidget *tab;
    QGridLayout *gridLayout_4;
    QLabel *label_11;
    QPushButton *addEntryBtn;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *deleteEntryBtn;
    QLineEdit *entryTotalSumEdit;
    QTableView *entryTableView;
    QWidget *severalDocTab;
    QGridLayout *gridLayout_5;
    QPushButton *addItemBtn;
    QPushButton *deleteItemBtn;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_13;
    QLineEdit *itemSumEdit;
    QTableView *itemTableView;

    void setupUi(QDialog *CreateAccountableRep)
    {
        if (CreateAccountableRep->objectName().isEmpty())
            CreateAccountableRep->setObjectName(QStringLiteral("CreateAccountableRep"));
        CreateAccountableRep->resize(1357, 892);
        CreateAccountableRep->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateAccountableRep->setModal(false);
        gridLayout = new QGridLayout(CreateAccountableRep);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreateAccountableRep);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(CreateAccountableRep);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 3);

        tabWidget = new QTabWidget(CreateAccountableRep);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        oneDocTab = new QWidget();
        oneDocTab->setObjectName(QStringLiteral("oneDocTab"));
        gridLayout_2 = new QGridLayout(oneDocTab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        BranchLb = new QLabel(oneDocTab);
        BranchLb->setObjectName(QStringLiteral("BranchLb"));

        gridLayout_2->addWidget(BranchLb, 2, 0, 1, 1);

        headerLb = new QLabel(oneDocTab);
        headerLb->setObjectName(QStringLiteral("headerLb"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        headerLb->setFont(font);

        gridLayout_2->addWidget(headerLb, 3, 1, 1, 1);

        branchPh = new QLabel(oneDocTab);
        branchPh->setObjectName(QStringLiteral("branchPh"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        branchPh->setFont(font1);

        gridLayout_2->addWidget(branchPh, 2, 1, 1, 1);

        positionLb = new QLabel(oneDocTab);
        positionLb->setObjectName(QStringLiteral("positionLb"));

        gridLayout_2->addWidget(positionLb, 2, 2, 1, 1);

        datelb = new QLabel(oneDocTab);
        datelb->setObjectName(QStringLiteral("datelb"));

        gridLayout_2->addWidget(datelb, 4, 0, 1, 1);

        reportNumberPh = new QLabel(oneDocTab);
        reportNumberPh->setObjectName(QStringLiteral("reportNumberPh"));
        reportNumberPh->setFont(font1);

        gridLayout_2->addWidget(reportNumberPh, 3, 2, 1, 1);

        positionPh = new QLabel(oneDocTab);
        positionPh->setObjectName(QStringLiteral("positionPh"));
        positionPh->setFont(font1);

        gridLayout_2->addWidget(positionPh, 2, 3, 1, 1);

        rolePh = new QLabel(oneDocTab);
        rolePh->setObjectName(QStringLiteral("rolePh"));
        rolePh->setMinimumSize(QSize(200, 0));
        rolePh->setFont(font1);

        gridLayout_2->addWidget(rolePh, 2, 5, 1, 1);

        expenseLb = new QLabel(oneDocTab);
        expenseLb->setObjectName(QStringLiteral("expenseLb"));

        gridLayout_2->addWidget(expenseLb, 7, 0, 1, 1);

        appointmentEdit = new QLineEdit(oneDocTab);
        appointmentEdit->setObjectName(QStringLiteral("appointmentEdit"));

        gridLayout_2->addWidget(appointmentEdit, 7, 1, 1, 5);

        companyEdit = new QLineEdit(oneDocTab);
        companyEdit->setObjectName(QStringLiteral("companyEdit"));
        companyEdit->setReadOnly(true);

        gridLayout_2->addWidget(companyEdit, 0, 1, 1, 1);

        companyPh = new QLabel(oneDocTab);
        companyPh->setObjectName(QStringLiteral("companyPh"));
        companyPh->setMinimumSize(QSize(200, 0));
        companyPh->setFont(font1);

        gridLayout_2->addWidget(companyPh, 0, 3, 1, 1);

        companyLb = new QLabel(oneDocTab);
        companyLb->setObjectName(QStringLiteral("companyLb"));

        gridLayout_2->addWidget(companyLb, 0, 2, 1, 1);

        cmpBtn = new QPushButton(oneDocTab);
        cmpBtn->setObjectName(QStringLiteral("cmpBtn"));

        gridLayout_2->addWidget(cmpBtn, 0, 0, 1, 1);

        roleLb = new QLabel(oneDocTab);
        roleLb->setObjectName(QStringLiteral("roleLb"));

        gridLayout_2->addWidget(roleLb, 2, 4, 1, 1);

        reprotDateEdit = new QDateTimeEdit(oneDocTab);
        reprotDateEdit->setObjectName(QStringLiteral("reprotDateEdit"));

        gridLayout_2->addWidget(reprotDateEdit, 4, 1, 1, 1);

        approveLb = new QLabel(oneDocTab);
        approveLb->setObjectName(QStringLiteral("approveLb"));

        gridLayout_2->addWidget(approveLb, 4, 2, 1, 1);

        approveDateEdit = new QDateTimeEdit(oneDocTab);
        approveDateEdit->setObjectName(QStringLiteral("approveDateEdit"));

        gridLayout_2->addWidget(approveDateEdit, 4, 3, 1, 1);

        statusPh = new QLabel(oneDocTab);
        statusPh->setObjectName(QStringLiteral("statusPh"));
        statusPh->setFont(font1);

        gridLayout_2->addWidget(statusPh, 5, 5, 1, 1);

        directorLb = new QLabel(oneDocTab);
        directorLb->setObjectName(QStringLiteral("directorLb"));

        gridLayout_2->addWidget(directorLb, 0, 6, 1, 1);

        directorPh = new QLabel(oneDocTab);
        directorPh->setObjectName(QStringLiteral("directorPh"));
        directorPh->setMinimumSize(QSize(200, 0));
        directorPh->setFont(font1);

        gridLayout_2->addWidget(directorPh, 0, 7, 1, 1);

        accontantBtn = new QPushButton(oneDocTab);
        accontantBtn->setObjectName(QStringLiteral("accontantBtn"));

        gridLayout_2->addWidget(accontantBtn, 1, 4, 1, 1);

        directorBtn = new QPushButton(oneDocTab);
        directorBtn->setObjectName(QStringLiteral("directorBtn"));

        gridLayout_2->addWidget(directorBtn, 0, 4, 1, 1);

        label_10 = new QLabel(oneDocTab);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 1, 6, 1, 1);

        directorEdit = new QLineEdit(oneDocTab);
        directorEdit->setObjectName(QStringLiteral("directorEdit"));
        directorEdit->setReadOnly(true);

        gridLayout_2->addWidget(directorEdit, 0, 5, 1, 1);

        accountantEdit = new QLineEdit(oneDocTab);
        accountantEdit->setObjectName(QStringLiteral("accountantEdit"));

        gridLayout_2->addWidget(accountantEdit, 1, 5, 1, 1);

        currCmb = new QComboBox(oneDocTab);
        currCmb->setObjectName(QStringLiteral("currCmb"));

        gridLayout_2->addWidget(currCmb, 5, 1, 1, 1);

        label_9 = new QLabel(oneDocTab);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 5, 4, 1, 1);

        statusEdit = new QLineEdit(oneDocTab);
        statusEdit->setObjectName(QStringLiteral("statusEdit"));
        statusEdit->setReadOnly(true);

        gridLayout_2->addWidget(statusEdit, 5, 3, 1, 1);

        stsBtn = new QPushButton(oneDocTab);
        stsBtn->setObjectName(QStringLiteral("stsBtn"));

        gridLayout_2->addWidget(stsBtn, 5, 2, 1, 1);

        curLb = new QLabel(oneDocTab);
        curLb->setObjectName(QStringLiteral("curLb"));

        gridLayout_2->addWidget(curLb, 5, 0, 1, 1);

        label = new QLabel(oneDocTab);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 1, 2, 1, 1);

        employeePh = new QLabel(oneDocTab);
        employeePh->setObjectName(QStringLiteral("employeePh"));
        employeePh->setFont(font1);

        gridLayout_2->addWidget(employeePh, 1, 3, 1, 1);

        employeeEdit = new QLineEdit(oneDocTab);
        employeeEdit->setObjectName(QStringLiteral("employeeEdit"));
        employeeEdit->setReadOnly(true);

        gridLayout_2->addWidget(employeeEdit, 1, 1, 1, 1);

        empBtn = new QPushButton(oneDocTab);
        empBtn->setObjectName(QStringLiteral("empBtn"));

        gridLayout_2->addWidget(empBtn, 1, 0, 1, 1);

        accountantPh = new QLabel(oneDocTab);
        accountantPh->setObjectName(QStringLiteral("accountantPh"));
        accountantPh->setFont(font1);

        gridLayout_2->addWidget(accountantPh, 1, 7, 1, 1);

        sumGrb = new QGroupBox(oneDocTab);
        sumGrb->setObjectName(QStringLiteral("sumGrb"));
        gridLayout_3 = new QGridLayout(sumGrb);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        spentEdit = new QLineEdit(sumGrb);
        spentEdit->setObjectName(QStringLiteral("spentEdit"));
        spentEdit->setReadOnly(true);

        gridLayout_3->addWidget(spentEdit, 13, 2, 1, 1);

        label_5 = new QLabel(sumGrb);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 12, 0, 1, 1);

        label_7 = new QLabel(sumGrb);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_3->addWidget(label_7, 14, 0, 1, 1);

        totalEdit = new QLineEdit(sumGrb);
        totalEdit->setObjectName(QStringLiteral("totalEdit"));
        totalEdit->setReadOnly(true);

        gridLayout_3->addWidget(totalEdit, 12, 2, 1, 1);

        label_12 = new QLabel(sumGrb);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font1);

        gridLayout_3->addWidget(label_12, 8, 0, 1, 1);

        addPaymentBtn = new QPushButton(sumGrb);
        addPaymentBtn->setObjectName(QStringLiteral("addPaymentBtn"));

        gridLayout_3->addWidget(addPaymentBtn, 6, 2, 1, 1);

        line = new QFrame(sumGrb);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 3, 0, 1, 4);

        deleteWithdrawalBtn = new QPushButton(sumGrb);
        deleteWithdrawalBtn->setObjectName(QStringLiteral("deleteWithdrawalBtn"));

        gridLayout_3->addWidget(deleteWithdrawalBtn, 10, 3, 1, 1);

        addWithdrawalBtn = new QPushButton(sumGrb);
        addWithdrawalBtn->setObjectName(QStringLiteral("addWithdrawalBtn"));

        gridLayout_3->addWidget(addWithdrawalBtn, 10, 2, 1, 1);

        paymentTableView = new QTableView(sumGrb);
        paymentTableView->setObjectName(QStringLiteral("paymentTableView"));

        gridLayout_3->addWidget(paymentTableView, 5, 0, 1, 4);

        prevLb = new QLabel(sumGrb);
        prevLb->setObjectName(QStringLiteral("prevLb"));
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(true);
        font2.setWeight(75);
        prevLb->setFont(font2);

        gridLayout_3->addWidget(prevLb, 0, 0, 1, 1);

        line_3 = new QFrame(sumGrb);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_3, 11, 0, 1, 4);

        label_4 = new QLabel(sumGrb);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font2);

        gridLayout_3->addWidget(label_4, 4, 0, 1, 1);

        prevOverrunEdit = new QLineEdit(sumGrb);
        prevOverrunEdit->setObjectName(QStringLiteral("prevOverrunEdit"));
        prevOverrunEdit->setReadOnly(true);

        gridLayout_3->addWidget(prevOverrunEdit, 2, 2, 1, 1);

        prevRemainderEdit = new QLineEdit(sumGrb);
        prevRemainderEdit->setObjectName(QStringLiteral("prevRemainderEdit"));
        prevRemainderEdit->setReadOnly(true);

        gridLayout_3->addWidget(prevRemainderEdit, 1, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 6, 0, 1, 1);

        line_2 = new QFrame(sumGrb);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_2, 7, 0, 1, 4);

        label_2 = new QLabel(sumGrb);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 2);

        remainderEdit = new QLineEdit(sumGrb);
        remainderEdit->setObjectName(QStringLiteral("remainderEdit"));
        remainderEdit->setReadOnly(true);

        gridLayout_3->addWidget(remainderEdit, 14, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 1, 3, 1, 1);

        label_3 = new QLabel(sumGrb);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_3->addWidget(label_3, 2, 0, 1, 2);

        label_6 = new QLabel(sumGrb);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 13, 0, 1, 1);

        deletePaymentBtn = new QPushButton(sumGrb);
        deletePaymentBtn->setObjectName(QStringLiteral("deletePaymentBtn"));

        gridLayout_3->addWidget(deletePaymentBtn, 6, 3, 1, 1);

        overrunEdit = new QLineEdit(sumGrb);
        overrunEdit->setObjectName(QStringLiteral("overrunEdit"));
        overrunEdit->setReadOnly(true);

        gridLayout_3->addWidget(overrunEdit, 15, 2, 1, 1);

        label_8 = new QLabel(sumGrb);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_3->addWidget(label_8, 15, 0, 1, 1);

        withdrawalTableView = new QTableView(sumGrb);
        withdrawalTableView->setObjectName(QStringLiteral("withdrawalTableView"));

        gridLayout_3->addWidget(withdrawalTableView, 9, 0, 1, 4);


        gridLayout_2->addWidget(sumGrb, 8, 0, 1, 8);

        tabWidget->addTab(oneDocTab, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_4 = new QGridLayout(tab);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 2, 0, 1, 1);

        addEntryBtn = new QPushButton(tab);
        addEntryBtn->setObjectName(QStringLiteral("addEntryBtn"));

        gridLayout_4->addWidget(addEntryBtn, 1, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_7, 1, 0, 1, 1);

        deleteEntryBtn = new QPushButton(tab);
        deleteEntryBtn->setObjectName(QStringLiteral("deleteEntryBtn"));

        gridLayout_4->addWidget(deleteEntryBtn, 1, 2, 1, 1);

        entryTotalSumEdit = new QLineEdit(tab);
        entryTotalSumEdit->setObjectName(QStringLiteral("entryTotalSumEdit"));
        entryTotalSumEdit->setReadOnly(true);

        gridLayout_4->addWidget(entryTotalSumEdit, 2, 1, 1, 2);

        entryTableView = new QTableView(tab);
        entryTableView->setObjectName(QStringLiteral("entryTableView"));

        gridLayout_4->addWidget(entryTableView, 0, 0, 1, 3);

        tabWidget->addTab(tab, QString());
        severalDocTab = new QWidget();
        severalDocTab->setObjectName(QStringLiteral("severalDocTab"));
        gridLayout_5 = new QGridLayout(severalDocTab);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        addItemBtn = new QPushButton(severalDocTab);
        addItemBtn->setObjectName(QStringLiteral("addItemBtn"));

        gridLayout_5->addWidget(addItemBtn, 1, 1, 1, 1);

        deleteItemBtn = new QPushButton(severalDocTab);
        deleteItemBtn->setObjectName(QStringLiteral("deleteItemBtn"));

        gridLayout_5->addWidget(deleteItemBtn, 1, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_8, 1, 0, 1, 1);

        label_13 = new QLabel(severalDocTab);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_5->addWidget(label_13, 2, 0, 1, 1);

        itemSumEdit = new QLineEdit(severalDocTab);
        itemSumEdit->setObjectName(QStringLiteral("itemSumEdit"));

        gridLayout_5->addWidget(itemSumEdit, 2, 1, 1, 2);

        itemTableView = new QTableView(severalDocTab);
        itemTableView->setObjectName(QStringLiteral("itemTableView"));

        gridLayout_5->addWidget(itemTableView, 0, 0, 1, 3);

        tabWidget->addTab(severalDocTab, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(CreateAccountableRep);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CreateAccountableRep);
    } // setupUi

    void retranslateUi(QDialog *CreateAccountableRep)
    {
        CreateAccountableRep->setWindowTitle(QApplication::translate("CreateAccountableRep", "Create/Update accountable report", 0));
        okBtn->setText(QApplication::translate("CreateAccountableRep", "OK", 0));
        cancelBtn->setText(QApplication::translate("CreateAccountableRep", "Cancel", 0));
        BranchLb->setText(QApplication::translate("CreateAccountableRep", "Branch:", 0));
        headerLb->setText(QApplication::translate("CreateAccountableRep", "Accountable report \342\204\226 ", 0));
        branchPh->setText(QString());
        positionLb->setText(QApplication::translate("CreateAccountableRep", "Position:", 0));
        datelb->setText(QApplication::translate("CreateAccountableRep", "Select reprot date:", 0));
        reportNumberPh->setText(QString());
        positionPh->setText(QString());
        rolePh->setText(QString());
        expenseLb->setText(QApplication::translate("CreateAccountableRep", "Appointment:", 0));
        companyPh->setText(QString());
        companyLb->setText(QApplication::translate("CreateAccountableRep", "Company name:", 0));
        cmpBtn->setText(QApplication::translate("CreateAccountableRep", "Select company", 0));
        roleLb->setText(QApplication::translate("CreateAccountableRep", "Role:", 0));
        reprotDateEdit->setDisplayFormat(QApplication::translate("CreateAccountableRep", "dd.MM.yyyy HH:mm", 0));
        approveLb->setText(QApplication::translate("CreateAccountableRep", "Select approve date:", 0));
        approveDateEdit->setDisplayFormat(QApplication::translate("CreateAccountableRep", "dd.MM.yyyy HH:mm", 0));
        statusPh->setText(QString());
        directorLb->setText(QApplication::translate("CreateAccountableRep", "Director:", 0));
        directorPh->setText(QString());
        accontantBtn->setText(QApplication::translate("CreateAccountableRep", "Select accountant", 0));
        directorBtn->setText(QApplication::translate("CreateAccountableRep", "Select director", 0));
        label_10->setText(QApplication::translate("CreateAccountableRep", "Accountant:", 0));
        label_9->setText(QApplication::translate("CreateAccountableRep", "Status name:", 0));
        stsBtn->setText(QApplication::translate("CreateAccountableRep", "Select staus", 0));
        curLb->setText(QApplication::translate("CreateAccountableRep", "Select currency:", 0));
        label->setText(QApplication::translate("CreateAccountableRep", "Employee:", 0));
        employeePh->setText(QString());
        empBtn->setText(QApplication::translate("CreateAccountableRep", "Select accountable", 0));
        accountantPh->setText(QString());
        sumGrb->setTitle(QApplication::translate("CreateAccountableRep", "Indicator name", 0));
        spentEdit->setText(QApplication::translate("CreateAccountableRep", "0", 0));
        label_5->setText(QApplication::translate("CreateAccountableRep", "Total sum:", 0));
        label_7->setText(QApplication::translate("CreateAccountableRep", "Remainder:", 0));
        totalEdit->setText(QApplication::translate("CreateAccountableRep", "0", 0));
        label_12->setText(QApplication::translate("CreateAccountableRep", "Returned remainder to cashbox", 0));
        addPaymentBtn->setText(QApplication::translate("CreateAccountableRep", "Add advance", 0));
        deleteWithdrawalBtn->setText(QApplication::translate("CreateAccountableRep", "Delete return", 0));
        addWithdrawalBtn->setText(QApplication::translate("CreateAccountableRep", "Add return", 0));
        prevLb->setText(QApplication::translate("CreateAccountableRep", "Previous advance", 0));
        label_4->setText(QApplication::translate("CreateAccountableRep", "Advances from cashbox", 0));
        prevOverrunEdit->setText(QApplication::translate("CreateAccountableRep", "0", 0));
        prevRemainderEdit->setText(QApplication::translate("CreateAccountableRep", "0", 0));
        label_2->setText(QApplication::translate("CreateAccountableRep", "Previous remainder value:", 0));
        remainderEdit->setText(QApplication::translate("CreateAccountableRep", "0", 0));
        label_3->setText(QApplication::translate("CreateAccountableRep", "Previous overrun:", 0));
        label_6->setText(QApplication::translate("CreateAccountableRep", "Spent sum:", 0));
        deletePaymentBtn->setText(QApplication::translate("CreateAccountableRep", "Delete advance", 0));
        overrunEdit->setText(QApplication::translate("CreateAccountableRep", "0", 0));
        label_8->setText(QApplication::translate("CreateAccountableRep", "Overrun:", 0));
        tabWidget->setTabText(tabWidget->indexOf(oneDocTab), QApplication::translate("CreateAccountableRep", "Header document", 0));
        label_11->setText(QApplication::translate("CreateAccountableRep", "TotalSum", 0));
        addEntryBtn->setText(QApplication::translate("CreateAccountableRep", "Add entry", 0));
        deleteEntryBtn->setText(QApplication::translate("CreateAccountableRep", "Delete entry", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("CreateAccountableRep", "Accounting records", 0));
        addItemBtn->setText(QApplication::translate("CreateAccountableRep", "Add item", 0));
        deleteItemBtn->setText(QApplication::translate("CreateAccountableRep", "Delete item", 0));
        label_13->setText(QApplication::translate("CreateAccountableRep", "Total sum", 0));
        tabWidget->setTabText(tabWidget->indexOf(severalDocTab), QApplication::translate("CreateAccountableRep", "Expense document", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateAccountableRep: public Ui_CreateAccountableRep {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEACCBLREPDLG_H
