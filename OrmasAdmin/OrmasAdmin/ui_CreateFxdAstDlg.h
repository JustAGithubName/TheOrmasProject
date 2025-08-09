/********************************************************************************
** Form generated from reading UI file 'CreateFxdAstDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEFXDASTDLG_H
#define UI_CREATEFXDASTDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
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

QT_BEGIN_NAMESPACE

class Ui_CreateFxdAst
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QGroupBox *fixedAssGbx;
    QGridLayout *gridLayout_4;
    QLabel *stopCostLb;
    QDateEdit *startDateEdit;
    QLabel *invLb;
    QLineEdit *stopEdit;
    QLabel *startDateLb;
    QLabel *bayDateLb;
    QDateEdit *endDateEdit;
    QLabel *endDateLb;
    QDateEdit *buyDateEdit;
    QLabel *primCostLb;
    QLineEdit *primaryEdit;
    QLineEdit *invNumberEdit;
    QLabel *label_3;
    QLabel *serLb;
    QLineEdit *serviceLifeEdit;
    QPushButton *statusBtn;
    QLineEdit *statusEdit;
    QLabel *amChbx;
    QCheckBox *isAmChx;
    QGroupBox *fxdAssDtGrpBox;
    QGridLayout *gridLayout_3;
    QComboBox *divisionCmb;
    QComboBox *amGrpCmb;
    QLabel *amGroupLb;
    QComboBox *amTypeCmb;
    QLabel *amTypeLb;
    QLabel *depLb;
    QLineEdit *barcodeEdit;
    QLineEdit *amortizeEdit;
    QLineEdit *primaryCostEdit;
    QLabel *barLb;
    QLabel *amortizeAccLb;
    QLabel *primaryAccLb;
    QLabel *amValueLb;
    QLineEdit *amValueEdit;
    QLineEdit *locationEdit;
    QLabel *locationLb;
    QLabel *percentLb;
    QLineEdit *detailsIDEdit;
    QLabel *label_2;
    QLabel *label_4;
    QComboBox *fAstTypeCmb;
    QGroupBox *sourceGbx;
    QGridLayout *gridLayout_5;
    QPushButton *accableBtn;
    QLabel *surnameLb;
    QPushButton *purveyorBtn;
    QLabel *surLb;
    QLineEdit *accIDEdit;
    QLineEdit *accableIDEdit;
    QPushButton *accountBtn;
    QLabel *accLB;
    QLabel *accountName;
    QLineEdit *purEditID;
    QCheckBox *newFACxb;
    QGroupBox *specGrpBox;
    QGridLayout *gridLayout_2;
    QLabel *nameLB;
    QLabel *documentLb;
    QLineEdit *faNameEdit;
    QLineEdit *factoryNumEdit;
    QLabel *facNumberLb;
    QLineEdit *documentEdit;
    QLabel *objCharLb;
    QLineEdit *objCharEdit;
    QLabel *conditionLb;
    QLineEdit *conditionEdit;
    QCheckBox *existSpecCxb;
    QPushButton *specBtn;
    QLineEdit *specIDEdit;
    QLabel *developerLb;
    QLineEdit *developerEdit;
    QLabel *dateOfConsLb;
    QDateEdit *consDateEdit;
    QLabel *label;

    void setupUi(QDialog *CreateFxdAst)
    {
        if (CreateFxdAst->objectName().isEmpty())
            CreateFxdAst->setObjectName(QStringLiteral("CreateFxdAst"));
        CreateFxdAst->resize(946, 725);
        CreateFxdAst->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateFxdAst->setModal(false);
        gridLayout = new QGridLayout(CreateFxdAst);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 17);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreateFxdAst);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(CreateFxdAst);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 6, 0, 1, 2);

        fixedAssGbx = new QGroupBox(CreateFxdAst);
        fixedAssGbx->setObjectName(QStringLiteral("fixedAssGbx"));
        gridLayout_4 = new QGridLayout(fixedAssGbx);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        stopCostLb = new QLabel(fixedAssGbx);
        stopCostLb->setObjectName(QStringLiteral("stopCostLb"));

        gridLayout_4->addWidget(stopCostLb, 2, 0, 1, 1);

        startDateEdit = new QDateEdit(fixedAssGbx);
        startDateEdit->setObjectName(QStringLiteral("startDateEdit"));

        gridLayout_4->addWidget(startDateEdit, 1, 3, 1, 1);

        invLb = new QLabel(fixedAssGbx);
        invLb->setObjectName(QStringLiteral("invLb"));

        gridLayout_4->addWidget(invLb, 0, 0, 1, 1);

        stopEdit = new QLineEdit(fixedAssGbx);
        stopEdit->setObjectName(QStringLiteral("stopEdit"));

        gridLayout_4->addWidget(stopEdit, 2, 1, 1, 1);

        startDateLb = new QLabel(fixedAssGbx);
        startDateLb->setObjectName(QStringLiteral("startDateLb"));

        gridLayout_4->addWidget(startDateLb, 1, 2, 1, 1);

        bayDateLb = new QLabel(fixedAssGbx);
        bayDateLb->setObjectName(QStringLiteral("bayDateLb"));

        gridLayout_4->addWidget(bayDateLb, 0, 2, 1, 1);

        endDateEdit = new QDateEdit(fixedAssGbx);
        endDateEdit->setObjectName(QStringLiteral("endDateEdit"));

        gridLayout_4->addWidget(endDateEdit, 2, 3, 1, 1);

        endDateLb = new QLabel(fixedAssGbx);
        endDateLb->setObjectName(QStringLiteral("endDateLb"));

        gridLayout_4->addWidget(endDateLb, 2, 2, 1, 1);

        buyDateEdit = new QDateEdit(fixedAssGbx);
        buyDateEdit->setObjectName(QStringLiteral("buyDateEdit"));

        gridLayout_4->addWidget(buyDateEdit, 0, 3, 1, 1);

        primCostLb = new QLabel(fixedAssGbx);
        primCostLb->setObjectName(QStringLiteral("primCostLb"));

        gridLayout_4->addWidget(primCostLb, 1, 0, 1, 1);

        primaryEdit = new QLineEdit(fixedAssGbx);
        primaryEdit->setObjectName(QStringLiteral("primaryEdit"));
        primaryEdit->setAcceptDrops(false);

        gridLayout_4->addWidget(primaryEdit, 1, 1, 1, 1);

        invNumberEdit = new QLineEdit(fixedAssGbx);
        invNumberEdit->setObjectName(QStringLiteral("invNumberEdit"));
        invNumberEdit->setReadOnly(true);

        gridLayout_4->addWidget(invNumberEdit, 0, 1, 1, 1);

        label_3 = new QLabel(fixedAssGbx);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_4->addWidget(label_3, 5, 0, 1, 1);

        serLb = new QLabel(fixedAssGbx);
        serLb->setObjectName(QStringLiteral("serLb"));

        gridLayout_4->addWidget(serLb, 0, 4, 1, 1);

        serviceLifeEdit = new QLineEdit(fixedAssGbx);
        serviceLifeEdit->setObjectName(QStringLiteral("serviceLifeEdit"));
        serviceLifeEdit->setReadOnly(true);

        gridLayout_4->addWidget(serviceLifeEdit, 0, 5, 1, 1);

        statusBtn = new QPushButton(fixedAssGbx);
        statusBtn->setObjectName(QStringLiteral("statusBtn"));
        statusBtn->setMinimumSize(QSize(100, 0));

        gridLayout_4->addWidget(statusBtn, 1, 4, 1, 1);

        statusEdit = new QLineEdit(fixedAssGbx);
        statusEdit->setObjectName(QStringLiteral("statusEdit"));
        statusEdit->setReadOnly(true);

        gridLayout_4->addWidget(statusEdit, 1, 5, 1, 1);

        amChbx = new QLabel(fixedAssGbx);
        amChbx->setObjectName(QStringLiteral("amChbx"));

        gridLayout_4->addWidget(amChbx, 2, 4, 1, 1);

        isAmChx = new QCheckBox(fixedAssGbx);
        isAmChx->setObjectName(QStringLiteral("isAmChx"));
        isAmChx->setEnabled(true);
        isAmChx->setChecked(false);

        gridLayout_4->addWidget(isAmChx, 2, 5, 1, 1);


        gridLayout->addWidget(fixedAssGbx, 5, 0, 1, 2);

        fxdAssDtGrpBox = new QGroupBox(CreateFxdAst);
        fxdAssDtGrpBox->setObjectName(QStringLiteral("fxdAssDtGrpBox"));
        gridLayout_3 = new QGridLayout(fxdAssDtGrpBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        divisionCmb = new QComboBox(fxdAssDtGrpBox);
        divisionCmb->setObjectName(QStringLiteral("divisionCmb"));

        gridLayout_3->addWidget(divisionCmb, 2, 1, 1, 1);

        amGrpCmb = new QComboBox(fxdAssDtGrpBox);
        amGrpCmb->setObjectName(QStringLiteral("amGrpCmb"));
        amGrpCmb->setMinimumSize(QSize(200, 0));
        amGrpCmb->setEditable(false);

        gridLayout_3->addWidget(amGrpCmb, 0, 1, 1, 1);

        amGroupLb = new QLabel(fxdAssDtGrpBox);
        amGroupLb->setObjectName(QStringLiteral("amGroupLb"));

        gridLayout_3->addWidget(amGroupLb, 0, 0, 1, 1);

        amTypeCmb = new QComboBox(fxdAssDtGrpBox);
        amTypeCmb->setObjectName(QStringLiteral("amTypeCmb"));

        gridLayout_3->addWidget(amTypeCmb, 1, 1, 1, 1);

        amTypeLb = new QLabel(fxdAssDtGrpBox);
        amTypeLb->setObjectName(QStringLiteral("amTypeLb"));

        gridLayout_3->addWidget(amTypeLb, 1, 0, 1, 1);

        depLb = new QLabel(fxdAssDtGrpBox);
        depLb->setObjectName(QStringLiteral("depLb"));

        gridLayout_3->addWidget(depLb, 2, 0, 1, 1);

        barcodeEdit = new QLineEdit(fxdAssDtGrpBox);
        barcodeEdit->setObjectName(QStringLiteral("barcodeEdit"));

        gridLayout_3->addWidget(barcodeEdit, 2, 3, 1, 1);

        amortizeEdit = new QLineEdit(fxdAssDtGrpBox);
        amortizeEdit->setObjectName(QStringLiteral("amortizeEdit"));

        gridLayout_3->addWidget(amortizeEdit, 1, 3, 1, 1);

        primaryCostEdit = new QLineEdit(fxdAssDtGrpBox);
        primaryCostEdit->setObjectName(QStringLiteral("primaryCostEdit"));
        primaryCostEdit->setReadOnly(true);

        gridLayout_3->addWidget(primaryCostEdit, 0, 3, 1, 1);

        barLb = new QLabel(fxdAssDtGrpBox);
        barLb->setObjectName(QStringLiteral("barLb"));

        gridLayout_3->addWidget(barLb, 2, 2, 1, 1);

        amortizeAccLb = new QLabel(fxdAssDtGrpBox);
        amortizeAccLb->setObjectName(QStringLiteral("amortizeAccLb"));

        gridLayout_3->addWidget(amortizeAccLb, 1, 2, 1, 1);

        primaryAccLb = new QLabel(fxdAssDtGrpBox);
        primaryAccLb->setObjectName(QStringLiteral("primaryAccLb"));

        gridLayout_3->addWidget(primaryAccLb, 0, 2, 1, 1);

        amValueLb = new QLabel(fxdAssDtGrpBox);
        amValueLb->setObjectName(QStringLiteral("amValueLb"));

        gridLayout_3->addWidget(amValueLb, 1, 5, 1, 1);

        amValueEdit = new QLineEdit(fxdAssDtGrpBox);
        amValueEdit->setObjectName(QStringLiteral("amValueEdit"));

        gridLayout_3->addWidget(amValueEdit, 1, 6, 1, 1);

        locationEdit = new QLineEdit(fxdAssDtGrpBox);
        locationEdit->setObjectName(QStringLiteral("locationEdit"));

        gridLayout_3->addWidget(locationEdit, 0, 6, 1, 1);

        locationLb = new QLabel(fxdAssDtGrpBox);
        locationLb->setObjectName(QStringLiteral("locationLb"));

        gridLayout_3->addWidget(locationLb, 0, 5, 1, 1);

        percentLb = new QLabel(fxdAssDtGrpBox);
        percentLb->setObjectName(QStringLiteral("percentLb"));
        percentLb->setMaximumSize(QSize(10, 16777215));

        gridLayout_3->addWidget(percentLb, 1, 7, 1, 1);

        detailsIDEdit = new QLineEdit(fxdAssDtGrpBox);
        detailsIDEdit->setObjectName(QStringLiteral("detailsIDEdit"));

        gridLayout_3->addWidget(detailsIDEdit, 2, 6, 1, 1);

        label_2 = new QLabel(fxdAssDtGrpBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 2, 5, 1, 1);


        gridLayout->addWidget(fxdAssDtGrpBox, 4, 0, 1, 2);

        label_4 = new QLabel(CreateFxdAst);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        fAstTypeCmb = new QComboBox(CreateFxdAst);
        fAstTypeCmb->setObjectName(QStringLiteral("fAstTypeCmb"));
        fAstTypeCmb->setMaximumSize(QSize(600, 16777215));

        gridLayout->addWidget(fAstTypeCmb, 2, 1, 1, 1);

        sourceGbx = new QGroupBox(CreateFxdAst);
        sourceGbx->setObjectName(QStringLiteral("sourceGbx"));
        gridLayout_5 = new QGridLayout(sourceGbx);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        accableBtn = new QPushButton(sourceGbx);
        accableBtn->setObjectName(QStringLiteral("accableBtn"));
        accableBtn->setMinimumSize(QSize(130, 0));

        gridLayout_5->addWidget(accableBtn, 0, 0, 1, 1);

        surnameLb = new QLabel(sourceGbx);
        surnameLb->setObjectName(QStringLiteral("surnameLb"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        surnameLb->setFont(font);

        gridLayout_5->addWidget(surnameLb, 3, 1, 1, 1);

        purveyorBtn = new QPushButton(sourceGbx);
        purveyorBtn->setObjectName(QStringLiteral("purveyorBtn"));
        purveyorBtn->setMinimumSize(QSize(130, 0));

        gridLayout_5->addWidget(purveyorBtn, 0, 2, 1, 1);

        surLb = new QLabel(sourceGbx);
        surLb->setObjectName(QStringLiteral("surLb"));

        gridLayout_5->addWidget(surLb, 3, 0, 1, 1);

        accIDEdit = new QLineEdit(sourceGbx);
        accIDEdit->setObjectName(QStringLiteral("accIDEdit"));
        accIDEdit->setReadOnly(true);

        gridLayout_5->addWidget(accIDEdit, 4, 1, 1, 1);

        accableIDEdit = new QLineEdit(sourceGbx);
        accableIDEdit->setObjectName(QStringLiteral("accableIDEdit"));
        accableIDEdit->setReadOnly(true);

        gridLayout_5->addWidget(accableIDEdit, 0, 1, 1, 1);

        accountBtn = new QPushButton(sourceGbx);
        accountBtn->setObjectName(QStringLiteral("accountBtn"));

        gridLayout_5->addWidget(accountBtn, 4, 0, 1, 1);

        accLB = new QLabel(sourceGbx);
        accLB->setObjectName(QStringLiteral("accLB"));

        gridLayout_5->addWidget(accLB, 5, 0, 1, 1);

        accountName = new QLabel(sourceGbx);
        accountName->setObjectName(QStringLiteral("accountName"));
        accountName->setFont(font);

        gridLayout_5->addWidget(accountName, 5, 1, 1, 1);

        purEditID = new QLineEdit(sourceGbx);
        purEditID->setObjectName(QStringLiteral("purEditID"));
        purEditID->setReadOnly(true);

        gridLayout_5->addWidget(purEditID, 0, 3, 1, 1);


        gridLayout->addWidget(sourceGbx, 1, 0, 1, 2);

        newFACxb = new QCheckBox(CreateFxdAst);
        newFACxb->setObjectName(QStringLiteral("newFACxb"));
        newFACxb->setChecked(true);

        gridLayout->addWidget(newFACxb, 0, 0, 1, 1);

        specGrpBox = new QGroupBox(CreateFxdAst);
        specGrpBox->setObjectName(QStringLiteral("specGrpBox"));
        gridLayout_2 = new QGridLayout(specGrpBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        nameLB = new QLabel(specGrpBox);
        nameLB->setObjectName(QStringLiteral("nameLB"));

        gridLayout_2->addWidget(nameLB, 1, 0, 1, 1);

        documentLb = new QLabel(specGrpBox);
        documentLb->setObjectName(QStringLiteral("documentLb"));

        gridLayout_2->addWidget(documentLb, 4, 0, 1, 1);

        faNameEdit = new QLineEdit(specGrpBox);
        faNameEdit->setObjectName(QStringLiteral("faNameEdit"));

        gridLayout_2->addWidget(faNameEdit, 1, 1, 1, 1);

        factoryNumEdit = new QLineEdit(specGrpBox);
        factoryNumEdit->setObjectName(QStringLiteral("factoryNumEdit"));

        gridLayout_2->addWidget(factoryNumEdit, 2, 1, 1, 1);

        facNumberLb = new QLabel(specGrpBox);
        facNumberLb->setObjectName(QStringLiteral("facNumberLb"));

        gridLayout_2->addWidget(facNumberLb, 2, 0, 1, 1);

        documentEdit = new QLineEdit(specGrpBox);
        documentEdit->setObjectName(QStringLiteral("documentEdit"));

        gridLayout_2->addWidget(documentEdit, 4, 1, 1, 1);

        objCharLb = new QLabel(specGrpBox);
        objCharLb->setObjectName(QStringLiteral("objCharLb"));

        gridLayout_2->addWidget(objCharLb, 1, 2, 1, 1);

        objCharEdit = new QLineEdit(specGrpBox);
        objCharEdit->setObjectName(QStringLiteral("objCharEdit"));

        gridLayout_2->addWidget(objCharEdit, 1, 3, 1, 1);

        conditionLb = new QLabel(specGrpBox);
        conditionLb->setObjectName(QStringLiteral("conditionLb"));

        gridLayout_2->addWidget(conditionLb, 2, 2, 1, 1);

        conditionEdit = new QLineEdit(specGrpBox);
        conditionEdit->setObjectName(QStringLiteral("conditionEdit"));

        gridLayout_2->addWidget(conditionEdit, 2, 3, 1, 1);

        existSpecCxb = new QCheckBox(specGrpBox);
        existSpecCxb->setObjectName(QStringLiteral("existSpecCxb"));

        gridLayout_2->addWidget(existSpecCxb, 0, 0, 1, 1);

        specBtn = new QPushButton(specGrpBox);
        specBtn->setObjectName(QStringLiteral("specBtn"));

        gridLayout_2->addWidget(specBtn, 0, 1, 1, 1);

        specIDEdit = new QLineEdit(specGrpBox);
        specIDEdit->setObjectName(QStringLiteral("specIDEdit"));
        specIDEdit->setReadOnly(true);

        gridLayout_2->addWidget(specIDEdit, 0, 2, 1, 2);

        developerLb = new QLabel(specGrpBox);
        developerLb->setObjectName(QStringLiteral("developerLb"));

        gridLayout_2->addWidget(developerLb, 1, 4, 1, 1);

        developerEdit = new QLineEdit(specGrpBox);
        developerEdit->setObjectName(QStringLiteral("developerEdit"));

        gridLayout_2->addWidget(developerEdit, 1, 5, 1, 1);

        dateOfConsLb = new QLabel(specGrpBox);
        dateOfConsLb->setObjectName(QStringLiteral("dateOfConsLb"));

        gridLayout_2->addWidget(dateOfConsLb, 2, 4, 1, 1);

        consDateEdit = new QDateEdit(specGrpBox);
        consDateEdit->setObjectName(QStringLiteral("consDateEdit"));

        gridLayout_2->addWidget(consDateEdit, 2, 5, 1, 1);

        label = new QLabel(specGrpBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 4, 3, 1, 1);


        gridLayout->addWidget(specGrpBox, 3, 0, 1, 2);

        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(CreateFxdAst);

        QMetaObject::connectSlotsByName(CreateFxdAst);
    } // setupUi

    void retranslateUi(QDialog *CreateFxdAst)
    {
        CreateFxdAst->setWindowTitle(QApplication::translate("CreateFxdAst", "Create/Update fixed assets", 0));
        okBtn->setText(QApplication::translate("CreateFxdAst", "Ok", 0));
        cancelBtn->setText(QApplication::translate("CreateFxdAst", "Cancel", 0));
        fixedAssGbx->setTitle(QApplication::translate("CreateFxdAst", "Fixed assets:", 0));
        stopCostLb->setText(QApplication::translate("CreateFxdAst", "Stop cost:", 0));
        invLb->setText(QApplication::translate("CreateFxdAst", "Inventory number:", 0));
        stopEdit->setText(QApplication::translate("CreateFxdAst", "0", 0));
        startDateLb->setText(QApplication::translate("CreateFxdAst", "Select start of operation date:", 0));
        bayDateLb->setText(QApplication::translate("CreateFxdAst", "Buy date:", 0));
        endDateLb->setText(QApplication::translate("CreateFxdAst", "Select end of operation date:", 0));
        primCostLb->setText(QApplication::translate("CreateFxdAst", "Primary cost*:", 0));
        label_3->setText(QApplication::translate("CreateFxdAst", "* - mandatory fields", 0));
        serLb->setText(QApplication::translate("CreateFxdAst", "Service life*:", 0));
        statusBtn->setText(QApplication::translate("CreateFxdAst", "Select status", 0));
        amChbx->setText(QApplication::translate("CreateFxdAst", "Is amortize?:", 0));
        isAmChx->setText(QApplication::translate("CreateFxdAst", "Yes", 0));
        fxdAssDtGrpBox->setTitle(QApplication::translate("CreateFxdAst", "Fixed assets details:", 0));
        amGroupLb->setText(QApplication::translate("CreateFxdAst", "Choose amortize group*:", 0));
        amTypeLb->setText(QApplication::translate("CreateFxdAst", "Choose amortize type*:", 0));
        depLb->setText(QApplication::translate("CreateFxdAst", "Choose division*:", 0));
        amortizeEdit->setText(QApplication::translate("CreateFxdAst", "0", 0));
        primaryCostEdit->setInputMask(QString());
        primaryCostEdit->setText(QApplication::translate("CreateFxdAst", "0", 0));
        barLb->setText(QApplication::translate("CreateFxdAst", "Barcode:", 0));
        amortizeAccLb->setText(QApplication::translate("CreateFxdAst", "Amortize value:", 0));
        primaryAccLb->setText(QApplication::translate("CreateFxdAst", "Primary cost:", 0));
        amValueLb->setText(QApplication::translate("CreateFxdAst", "Amortize value*:", 0));
        locationLb->setText(QApplication::translate("CreateFxdAst", "Location*:", 0));
        percentLb->setText(QApplication::translate("CreateFxdAst", "%", 0));
        label_2->setText(QApplication::translate("CreateFxdAst", "* - mandatory fields", 0));
        label_4->setText(QApplication::translate("CreateFxdAst", "Select fixed assets type", 0));
        sourceGbx->setTitle(QApplication::translate("CreateFxdAst", "Source account:", 0));
        accableBtn->setText(QApplication::translate("CreateFxdAst", "Select accountable", 0));
        surnameLb->setText(QString());
        purveyorBtn->setText(QApplication::translate("CreateFxdAst", "Select purveyor", 0));
        surLb->setText(QApplication::translate("CreateFxdAst", "Surname:", 0));
        accountBtn->setText(QApplication::translate("CreateFxdAst", "Select account", 0));
        accLB->setText(QApplication::translate("CreateFxdAst", "Account name:", 0));
        accountName->setText(QString());
        newFACxb->setText(QApplication::translate("CreateFxdAst", "Posting a new fixed assets?", 0));
        specGrpBox->setTitle(QApplication::translate("CreateFxdAst", "Fixed assets specification:", 0));
        nameLB->setText(QApplication::translate("CreateFxdAst", "Fixed assets name:*", 0));
        documentLb->setText(QApplication::translate("CreateFxdAst", "Document:", 0));
        facNumberLb->setText(QApplication::translate("CreateFxdAst", "Factory number:", 0));
        objCharLb->setText(QApplication::translate("CreateFxdAst", "Obeject characters:", 0));
        conditionLb->setText(QApplication::translate("CreateFxdAst", "Condition:", 0));
        existSpecCxb->setText(QApplication::translate("CreateFxdAst", "Select form existed", 0));
        specBtn->setText(QApplication::translate("CreateFxdAst", "Select specification", 0));
        developerLb->setText(QApplication::translate("CreateFxdAst", "Developer:", 0));
        dateOfConsLb->setText(QApplication::translate("CreateFxdAst", "Date of construction:", 0));
        label->setText(QApplication::translate("CreateFxdAst", "* - mandatory fields", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateFxdAst: public Ui_CreateFxdAst {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEFXDASTDLG_H
