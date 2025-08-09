/********************************************************************************
** Form generated from reading UI file 'CreateNcCoeffDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATENCCOEFFDLG_H
#define UI_CREATENCCOEFFDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CreateNetCostCoefficient
{
public:
    QGridLayout *gridLayout;
    QLabel *prNameLb;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QLabel *valueLb;
    QPushButton *productBtn;
    QLineEdit *productEdit;
    QLabel *label;
    QLineEdit *commentEdit;
    QDoubleSpinBox *valueSpBox;
    QLabel *label_2;
    QLabel *prNamePh;

    void setupUi(QDialog *CreateNetCostCoefficient)
    {
        if (CreateNetCostCoefficient->objectName().isEmpty())
            CreateNetCostCoefficient->setObjectName(QStringLiteral("CreateNetCostCoefficient"));
        CreateNetCostCoefficient->resize(700, 176);
        CreateNetCostCoefficient->setMinimumSize(QSize(150, 0));
        CreateNetCostCoefficient->setMaximumSize(QSize(16777215, 16777215));
        CreateNetCostCoefficient->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateNetCostCoefficient->setModal(false);
        gridLayout = new QGridLayout(CreateNetCostCoefficient);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        prNameLb = new QLabel(CreateNetCostCoefficient);
        prNameLb->setObjectName(QStringLiteral("prNameLb"));
        prNameLb->setMinimumSize(QSize(120, 0));
        prNameLb->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(prNameLb, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreateNetCostCoefficient);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(CreateNetCostCoefficient);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 5);

        valueLb = new QLabel(CreateNetCostCoefficient);
        valueLb->setObjectName(QStringLiteral("valueLb"));

        gridLayout->addWidget(valueLb, 2, 0, 1, 1);

        productBtn = new QPushButton(CreateNetCostCoefficient);
        productBtn->setObjectName(QStringLiteral("productBtn"));
        productBtn->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(productBtn, 0, 0, 1, 2);

        productEdit = new QLineEdit(CreateNetCostCoefficient);
        productEdit->setObjectName(QStringLiteral("productEdit"));
        productEdit->setReadOnly(true);

        gridLayout->addWidget(productEdit, 0, 2, 1, 2);

        label = new QLabel(CreateNetCostCoefficient);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        commentEdit = new QLineEdit(CreateNetCostCoefficient);
        commentEdit->setObjectName(QStringLiteral("commentEdit"));
        commentEdit->setMaxLength(100);

        gridLayout->addWidget(commentEdit, 3, 1, 1, 4);

        valueSpBox = new QDoubleSpinBox(CreateNetCostCoefficient);
        valueSpBox->setObjectName(QStringLiteral("valueSpBox"));
        valueSpBox->setDecimals(1);
        valueSpBox->setMinimum(0.1);
        valueSpBox->setMaximum(2);
        valueSpBox->setSingleStep(0.1);
        valueSpBox->setValue(1);

        gridLayout->addWidget(valueSpBox, 2, 1, 1, 1);

        label_2 = new QLabel(CreateNetCostCoefficient);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 2, 1, 3);

        prNamePh = new QLabel(CreateNetCostCoefficient);
        prNamePh->setObjectName(QStringLiteral("prNamePh"));
        prNamePh->setMinimumSize(QSize(100, 0));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        prNamePh->setFont(font);

        gridLayout->addWidget(prNamePh, 1, 1, 1, 4);

        QWidget::setTabOrder(productBtn, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(CreateNetCostCoefficient);

        QMetaObject::connectSlotsByName(CreateNetCostCoefficient);
    } // setupUi

    void retranslateUi(QDialog *CreateNetCostCoefficient)
    {
        CreateNetCostCoefficient->setWindowTitle(QApplication::translate("CreateNetCostCoefficient", "Create/Update net cost coefficient", 0));
        prNameLb->setText(QApplication::translate("CreateNetCostCoefficient", "Product name:", 0));
        okBtn->setText(QApplication::translate("CreateNetCostCoefficient", "OK", 0));
        cancelBtn->setText(QApplication::translate("CreateNetCostCoefficient", "Cancel", 0));
        valueLb->setText(QApplication::translate("CreateNetCostCoefficient", "Value:", 0));
        productBtn->setText(QApplication::translate("CreateNetCostCoefficient", "Select product", 0));
#ifndef QT_NO_TOOLTIP
        productEdit->setToolTip(QApplication::translate("CreateNetCostCoefficient", "<html><head/><body><p>Enter client ID</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("CreateNetCostCoefficient", "Comment:", 0));
        label_2->setText(QApplication::translate("CreateNetCostCoefficient", "Coefficient must be between 0,1 and 2. Standart value is 1", 0));
        prNamePh->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CreateNetCostCoefficient: public Ui_CreateNetCostCoefficient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATENCCOEFFDLG_H
