/********************************************************************************
** Form generated from reading UI file 'CreateFxdAstOperDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEFXDASTOPERDLG_H
#define UI_CREATEFXDASTOPERDLG_H

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

QT_BEGIN_NAMESPACE

class Ui_CreateFxdAstOper
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QRadioButton *inRdb;
    QRadioButton *decRdb;
    QLabel *label;
    QLabel *label_7;
    QPushButton *fxdAstButton;
    QRadioButton *reRdb;
    QLineEdit *fixedAstEdit;
    QDateEdit *operDateEdit;
    QLineEdit *nameEdit;
    QLineEdit *valueEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *CreateFxdAstOper)
    {
        if (CreateFxdAstOper->objectName().isEmpty())
            CreateFxdAstOper->setObjectName(QStringLiteral("CreateFxdAstOper"));
        CreateFxdAstOper->resize(694, 207);
        CreateFxdAstOper->setMinimumSize(QSize(500, 0));
        CreateFxdAstOper->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateFxdAstOper->setModal(false);
        gridLayout = new QGridLayout(CreateFxdAstOper);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 17);
        label_2 = new QLabel(CreateFxdAstOper);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        inRdb = new QRadioButton(CreateFxdAstOper);
        inRdb->setObjectName(QStringLiteral("inRdb"));

        gridLayout->addWidget(inRdb, 1, 1, 1, 1);

        decRdb = new QRadioButton(CreateFxdAstOper);
        decRdb->setObjectName(QStringLiteral("decRdb"));
        decRdb->setChecked(true);

        gridLayout->addWidget(decRdb, 1, 0, 1, 1);

        label = new QLabel(CreateFxdAstOper);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        label_7 = new QLabel(CreateFxdAstOper);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        fxdAstButton = new QPushButton(CreateFxdAstOper);
        fxdAstButton->setObjectName(QStringLiteral("fxdAstButton"));

        gridLayout->addWidget(fxdAstButton, 0, 0, 1, 1);

        reRdb = new QRadioButton(CreateFxdAstOper);
        reRdb->setObjectName(QStringLiteral("reRdb"));

        gridLayout->addWidget(reRdb, 1, 2, 1, 1);

        fixedAstEdit = new QLineEdit(CreateFxdAstOper);
        fixedAstEdit->setObjectName(QStringLiteral("fixedAstEdit"));

        gridLayout->addWidget(fixedAstEdit, 0, 1, 1, 2);

        operDateEdit = new QDateEdit(CreateFxdAstOper);
        operDateEdit->setObjectName(QStringLiteral("operDateEdit"));

        gridLayout->addWidget(operDateEdit, 2, 1, 1, 2);

        nameEdit = new QLineEdit(CreateFxdAstOper);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        gridLayout->addWidget(nameEdit, 3, 1, 1, 2);

        valueEdit = new QLineEdit(CreateFxdAstOper);
        valueEdit->setObjectName(QStringLiteral("valueEdit"));

        gridLayout->addWidget(valueEdit, 4, 1, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreateFxdAstOper);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(CreateFxdAstOper);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 7, 0, 1, 3);

        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(CreateFxdAstOper);

        QMetaObject::connectSlotsByName(CreateFxdAstOper);
    } // setupUi

    void retranslateUi(QDialog *CreateFxdAstOper)
    {
        CreateFxdAstOper->setWindowTitle(QApplication::translate("CreateFxdAstOper", "Create/Update fixed assets operation", 0));
        label_2->setText(QApplication::translate("CreateFxdAstOper", "Operation value:", 0));
        inRdb->setText(QApplication::translate("CreateFxdAstOper", "Increase", 0));
        decRdb->setText(QApplication::translate("CreateFxdAstOper", "Markdown", 0));
        label->setText(QApplication::translate("CreateFxdAstOper", "Operation name:", 0));
        label_7->setText(QApplication::translate("CreateFxdAstOper", "Operation date:", 0));
        fxdAstButton->setText(QApplication::translate("CreateFxdAstOper", "Select fixed assets", 0));
        reRdb->setText(QApplication::translate("CreateFxdAstOper", "Revaluation", 0));
        okBtn->setText(QApplication::translate("CreateFxdAstOper", "Ok", 0));
        cancelBtn->setText(QApplication::translate("CreateFxdAstOper", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateFxdAstOper: public Ui_CreateFxdAstOper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEFXDASTOPERDLG_H
