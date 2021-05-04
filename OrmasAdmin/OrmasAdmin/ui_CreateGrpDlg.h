/********************************************************************************
** Form generated from reading UI file 'CreateGrpDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEGRPDLG_H
#define UI_CREATEGRPDLG_H

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

class Ui_CreateGroup
{
public:
    QGridLayout *gridLayout;
    QLineEdit *defenitionEdit;
    QLabel *definitionLb;
    QLineEdit *nameEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLabel *nameLb;

    void setupUi(QDialog *CreateGroup)
    {
        if (CreateGroup->objectName().isEmpty())
            CreateGroup->setObjectName(QStringLiteral("CreateGroup"));
        CreateGroup->resize(461, 99);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CreateGroup->sizePolicy().hasHeightForWidth());
        CreateGroup->setSizePolicy(sizePolicy);
        CreateGroup->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateGroup->setModal(false);
        gridLayout = new QGridLayout(CreateGroup);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        defenitionEdit = new QLineEdit(CreateGroup);
        defenitionEdit->setObjectName(QStringLiteral("defenitionEdit"));

        gridLayout->addWidget(defenitionEdit, 1, 1, 1, 1);

        definitionLb = new QLabel(CreateGroup);
        definitionLb->setObjectName(QStringLiteral("definitionLb"));

        gridLayout->addWidget(definitionLb, 1, 0, 1, 1);

        nameEdit = new QLineEdit(CreateGroup);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        gridLayout->addWidget(nameEdit, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreateGroup);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(CreateGroup);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 2);

        nameLb = new QLabel(CreateGroup);
        nameLb->setObjectName(QStringLiteral("nameLb"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nameLb->sizePolicy().hasHeightForWidth());
        nameLb->setSizePolicy(sizePolicy1);
        nameLb->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(nameLb, 0, 0, 1, 1);

        QWidget::setTabOrder(nameEdit, defenitionEdit);
        QWidget::setTabOrder(defenitionEdit, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(CreateGroup);

        QMetaObject::connectSlotsByName(CreateGroup);
    } // setupUi

    void retranslateUi(QDialog *CreateGroup)
    {
        CreateGroup->setWindowTitle(QApplication::translate("CreateGroup", "Create/Update group", 0));
#ifndef QT_NO_TOOLTIP
        defenitionEdit->setToolTip(QApplication::translate("CreateGroup", "<html><head/><body><p>For example: Main St. 99</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        definitionLb->setText(QApplication::translate("CreateGroup", "Definition:", 0));
#ifndef QT_NO_TOOLTIP
        nameEdit->setToolTip(QApplication::translate("CreateGroup", "<html><head/><body><p>For example: &quot;River Co.&quot;</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        okBtn->setText(QApplication::translate("CreateGroup", "OK", 0));
        cancelBtn->setText(QApplication::translate("CreateGroup", "Cancel", 0));
        nameLb->setText(QApplication::translate("CreateGroup", "Name:", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateGroup: public Ui_CreateGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEGRPDLG_H
