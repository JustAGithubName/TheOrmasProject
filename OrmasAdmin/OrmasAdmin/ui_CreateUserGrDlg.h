/********************************************************************************
** Form generated from reading UI file 'CreateUserGrDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEUSERGRDLG_H
#define UI_CREATEUSERGRDLG_H

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

class Ui_CreateUserGroup
{
public:
    QGridLayout *gridLayout;
    QLabel *grLb;
    QLabel *userNameLB;
    QLabel *userSurnameLb;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QPushButton *groupBtn;
    QLabel *userLB;
    QPushButton *userBtn;
    QLineEdit *userEdit;
    QLineEdit *groupEdit;
    QLabel *userSLb;
    QLabel *groupNameLb;

    void setupUi(QDialog *CreateUserGroup)
    {
        if (CreateUserGroup->objectName().isEmpty())
            CreateUserGroup->setObjectName(QStringLiteral("CreateUserGroup"));
        CreateUserGroup->resize(590, 173);
        CreateUserGroup->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateUserGroup->setModal(false);
        gridLayout = new QGridLayout(CreateUserGroup);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        grLb = new QLabel(CreateUserGroup);
        grLb->setObjectName(QStringLiteral("grLb"));

        gridLayout->addWidget(grLb, 1, 0, 1, 1);

        userNameLB = new QLabel(CreateUserGroup);
        userNameLB->setObjectName(QStringLiteral("userNameLB"));
        userNameLB->setMinimumSize(QSize(120, 0));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        userNameLB->setFont(font);

        gridLayout->addWidget(userNameLB, 3, 1, 1, 1);

        userSurnameLb = new QLabel(CreateUserGroup);
        userSurnameLb->setObjectName(QStringLiteral("userSurnameLb"));
        userSurnameLb->setMinimumSize(QSize(120, 0));
        userSurnameLb->setFont(font);

        gridLayout->addWidget(userSurnameLb, 3, 4, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreateUserGroup);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(CreateUserGroup);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 5);

        groupBtn = new QPushButton(CreateUserGroup);
        groupBtn->setObjectName(QStringLiteral("groupBtn"));
        groupBtn->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(groupBtn, 0, 0, 1, 1);

        userLB = new QLabel(CreateUserGroup);
        userLB->setObjectName(QStringLiteral("userLB"));

        gridLayout->addWidget(userLB, 3, 0, 1, 1);

        userBtn = new QPushButton(CreateUserGroup);
        userBtn->setObjectName(QStringLiteral("userBtn"));

        gridLayout->addWidget(userBtn, 2, 0, 1, 1);

        userEdit = new QLineEdit(CreateUserGroup);
        userEdit->setObjectName(QStringLiteral("userEdit"));
        userEdit->setReadOnly(true);

        gridLayout->addWidget(userEdit, 2, 2, 1, 1);

        groupEdit = new QLineEdit(CreateUserGroup);
        groupEdit->setObjectName(QStringLiteral("groupEdit"));
        groupEdit->setReadOnly(true);

        gridLayout->addWidget(groupEdit, 0, 2, 1, 1);

        userSLb = new QLabel(CreateUserGroup);
        userSLb->setObjectName(QStringLiteral("userSLb"));

        gridLayout->addWidget(userSLb, 3, 2, 1, 1);

        groupNameLb = new QLabel(CreateUserGroup);
        groupNameLb->setObjectName(QStringLiteral("groupNameLb"));
        groupNameLb->setFont(font);

        gridLayout->addWidget(groupNameLb, 1, 1, 1, 2);

        QWidget::setTabOrder(groupBtn, userBtn);
        QWidget::setTabOrder(userBtn, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(CreateUserGroup);

        QMetaObject::connectSlotsByName(CreateUserGroup);
    } // setupUi

    void retranslateUi(QDialog *CreateUserGroup)
    {
        CreateUserGroup->setWindowTitle(QApplication::translate("CreateUserGroup", "Create/Update user-group relation", 0));
        grLb->setText(QApplication::translate("CreateUserGroup", "Group name:", 0));
        userNameLB->setText(QString());
        userSurnameLb->setText(QString());
        okBtn->setText(QApplication::translate("CreateUserGroup", "OK", 0));
        cancelBtn->setText(QApplication::translate("CreateUserGroup", "Cancel", 0));
        groupBtn->setText(QApplication::translate("CreateUserGroup", "Select group", 0));
        userLB->setText(QApplication::translate("CreateUserGroup", "User name:", 0));
        userBtn->setText(QApplication::translate("CreateUserGroup", "Select user", 0));
#ifndef QT_NO_TOOLTIP
        groupEdit->setToolTip(QApplication::translate("CreateUserGroup", "Must not be empty", 0));
#endif // QT_NO_TOOLTIP
        userSLb->setText(QApplication::translate("CreateUserGroup", "User surname:", 0));
        groupNameLb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CreateUserGroup: public Ui_CreateUserGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEUSERGRDLG_H
