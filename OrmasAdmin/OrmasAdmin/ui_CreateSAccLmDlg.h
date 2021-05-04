/********************************************************************************
** Form generated from reading UI file 'CreateSAccLmDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATESACCLMDLG_H
#define UI_CREATESACCLMDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CreateSubaccountLimit
{
public:
    QGridLayout *gridLayout;
    QPushButton *sAccBtn;
    QLineEdit *minValueEdit;
    QLabel *numberLb;
    QLineEdit *sAccEdit;
    QLabel *minLb;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *maxValueEdit;
    QLineEdit *numberEdit;
    QLabel *cBalanceLb;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *CreateSubaccountLimit)
    {
        if (CreateSubaccountLimit->objectName().isEmpty())
            CreateSubaccountLimit->setObjectName(QStringLiteral("CreateSubaccountLimit"));
        CreateSubaccountLimit->resize(593, 154);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CreateSubaccountLimit->sizePolicy().hasHeightForWidth());
        CreateSubaccountLimit->setSizePolicy(sizePolicy);
        CreateSubaccountLimit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateSubaccountLimit->setModal(false);
        gridLayout = new QGridLayout(CreateSubaccountLimit);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        sAccBtn = new QPushButton(CreateSubaccountLimit);
        sAccBtn->setObjectName(QStringLiteral("sAccBtn"));

        gridLayout->addWidget(sAccBtn, 1, 0, 1, 1);

        minValueEdit = new QLineEdit(CreateSubaccountLimit);
        minValueEdit->setObjectName(QStringLiteral("minValueEdit"));
        minValueEdit->setMinimumSize(QSize(150, 0));
        minValueEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(minValueEdit, 2, 1, 1, 1);

        numberLb = new QLabel(CreateSubaccountLimit);
        numberLb->setObjectName(QStringLiteral("numberLb"));
        numberLb->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(numberLb, 0, 0, 1, 1);

        sAccEdit = new QLineEdit(CreateSubaccountLimit);
        sAccEdit->setObjectName(QStringLiteral("sAccEdit"));
        sAccEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(sAccEdit, 1, 1, 1, 1);

        minLb = new QLabel(CreateSubaccountLimit);
        minLb->setObjectName(QStringLiteral("minLb"));

        gridLayout->addWidget(minLb, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        maxValueEdit = new QLineEdit(CreateSubaccountLimit);
        maxValueEdit->setObjectName(QStringLiteral("maxValueEdit"));
        maxValueEdit->setMinimumSize(QSize(150, 0));
        maxValueEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(maxValueEdit, 4, 1, 1, 1);

        numberEdit = new QLineEdit(CreateSubaccountLimit);
        numberEdit->setObjectName(QStringLiteral("numberEdit"));
        numberEdit->setMinimumSize(QSize(150, 0));
        numberEdit->setMaximumSize(QSize(150, 16777215));
        numberEdit->setReadOnly(true);

        gridLayout->addWidget(numberEdit, 0, 1, 1, 1);

        cBalanceLb = new QLabel(CreateSubaccountLimit);
        cBalanceLb->setObjectName(QStringLiteral("cBalanceLb"));

        gridLayout->addWidget(cBalanceLb, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreateSubaccountLimit);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(CreateSubaccountLimit);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 3);

        QWidget::setTabOrder(numberEdit, sAccBtn);
        QWidget::setTabOrder(sAccBtn, minValueEdit);
        QWidget::setTabOrder(minValueEdit, maxValueEdit);
        QWidget::setTabOrder(maxValueEdit, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);
        QWidget::setTabOrder(cancelBtn, sAccEdit);

        retranslateUi(CreateSubaccountLimit);

        QMetaObject::connectSlotsByName(CreateSubaccountLimit);
    } // setupUi

    void retranslateUi(QDialog *CreateSubaccountLimit)
    {
        CreateSubaccountLimit->setWindowTitle(QApplication::translate("CreateSubaccountLimit", "Create/Update subaccount limit", 0));
        sAccBtn->setText(QApplication::translate("CreateSubaccountLimit", "Select subaccount", 0));
#ifndef QT_NO_TOOLTIP
        minValueEdit->setToolTip(QApplication::translate("CreateSubaccountLimit", "<html><head/><body><p>For example: Doe</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        numberLb->setText(QApplication::translate("CreateSubaccountLimit", "Number:", 0));
        minLb->setText(QApplication::translate("CreateSubaccountLimit", "Minimum value:", 0));
#ifndef QT_NO_TOOLTIP
        maxValueEdit->setToolTip(QApplication::translate("CreateSubaccountLimit", "<html><head/><body><p>For example: John.Doe@gmail.com (does not mandatory field)</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        numberEdit->setToolTip(QApplication::translate("CreateSubaccountLimit", "<html><head/><body><p>For example: John</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        cBalanceLb->setText(QApplication::translate("CreateSubaccountLimit", "Maximum value:", 0));
        okBtn->setText(QApplication::translate("CreateSubaccountLimit", "OK", 0));
        cancelBtn->setText(QApplication::translate("CreateSubaccountLimit", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateSubaccountLimit: public Ui_CreateSubaccountLimit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATESACCLMDLG_H
