/********************************************************************************
** Form generated from reading UI file 'CreateStockLmDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATESTOCKLMDLG_H
#define UI_CREATESTOCKLMDLG_H

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

class Ui_CreateStockLimit
{
public:
    QGridLayout *gridLayout;
    QLabel *measureLb;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *addBtn;
    QPushButton *cancelBtn;
    QLabel *prodNameLb;
    QLabel *volumeLb;
    QLabel *prodNamePh;
    QLineEdit *productEdit;
    QLabel *volumePh;
    QLineEdit *minValueEdit;
    QPushButton *stockBtn;
    QLabel *warehousePh;
    QLineEdit *stockEdit;
    QLabel *minLb;
    QLabel *warehouseLb_2;
    QLabel *countLb;
    QLabel *measurePh;
    QPushButton *productBtn;
    QLineEdit *maxValueEdit;

    void setupUi(QDialog *CreateStockLimit)
    {
        if (CreateStockLimit->objectName().isEmpty())
            CreateStockLimit->setObjectName(QStringLiteral("CreateStockLimit"));
        CreateStockLimit->resize(636, 215);
        CreateStockLimit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        CreateStockLimit->setModal(false);
        gridLayout = new QGridLayout(CreateStockLimit);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 17);
        measureLb = new QLabel(CreateStockLimit);
        measureLb->setObjectName(QStringLiteral("measureLb"));

        gridLayout->addWidget(measureLb, 4, 4, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addBtn = new QPushButton(CreateStockLimit);
        addBtn->setObjectName(QStringLiteral("addBtn"));

        horizontalLayout->addWidget(addBtn);

        cancelBtn = new QPushButton(CreateStockLimit);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 8, 0, 1, 6);

        prodNameLb = new QLabel(CreateStockLimit);
        prodNameLb->setObjectName(QStringLiteral("prodNameLb"));
        prodNameLb->setMinimumSize(QSize(70, 0));
        prodNameLb->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(prodNameLb, 4, 0, 1, 1);

        volumeLb = new QLabel(CreateStockLimit);
        volumeLb->setObjectName(QStringLiteral("volumeLb"));
        volumeLb->setMinimumSize(QSize(70, 0));
        volumeLb->setMaximumSize(QSize(70, 16777215));

        gridLayout->addWidget(volumeLb, 4, 2, 1, 1);

        prodNamePh = new QLabel(CreateStockLimit);
        prodNamePh->setObjectName(QStringLiteral("prodNamePh"));
        prodNamePh->setMinimumSize(QSize(100, 0));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        prodNamePh->setFont(font);

        gridLayout->addWidget(prodNamePh, 4, 1, 1, 1);

        productEdit = new QLineEdit(CreateStockLimit);
        productEdit->setObjectName(QStringLiteral("productEdit"));
        productEdit->setReadOnly(true);

        gridLayout->addWidget(productEdit, 3, 3, 1, 1);

        volumePh = new QLabel(CreateStockLimit);
        volumePh->setObjectName(QStringLiteral("volumePh"));
        volumePh->setMinimumSize(QSize(100, 0));
        volumePh->setFont(font);

        gridLayout->addWidget(volumePh, 4, 3, 1, 1);

        minValueEdit = new QLineEdit(CreateStockLimit);
        minValueEdit->setObjectName(QStringLiteral("minValueEdit"));
        minValueEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(minValueEdit, 5, 3, 1, 1);

        stockBtn = new QPushButton(CreateStockLimit);
        stockBtn->setObjectName(QStringLiteral("stockBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stockBtn->sizePolicy().hasHeightForWidth());
        stockBtn->setSizePolicy(sizePolicy);
        stockBtn->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(stockBtn, 1, 0, 1, 3);

        warehousePh = new QLabel(CreateStockLimit);
        warehousePh->setObjectName(QStringLiteral("warehousePh"));
        warehousePh->setMinimumSize(QSize(120, 0));
        warehousePh->setFont(font);

        gridLayout->addWidget(warehousePh, 2, 3, 1, 3);

        stockEdit = new QLineEdit(CreateStockLimit);
        stockEdit->setObjectName(QStringLiteral("stockEdit"));
        stockEdit->setMaximumSize(QSize(150, 16777215));
        stockEdit->setReadOnly(true);

        gridLayout->addWidget(stockEdit, 1, 3, 1, 1);

        minLb = new QLabel(CreateStockLimit);
        minLb->setObjectName(QStringLiteral("minLb"));
        minLb->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(minLb, 5, 0, 1, 1);

        warehouseLb_2 = new QLabel(CreateStockLimit);
        warehouseLb_2->setObjectName(QStringLiteral("warehouseLb_2"));

        gridLayout->addWidget(warehouseLb_2, 2, 0, 1, 1);

        countLb = new QLabel(CreateStockLimit);
        countLb->setObjectName(QStringLiteral("countLb"));
        countLb->setMinimumSize(QSize(150, 0));

        gridLayout->addWidget(countLb, 7, 0, 1, 1);

        measurePh = new QLabel(CreateStockLimit);
        measurePh->setObjectName(QStringLiteral("measurePh"));
        measurePh->setMinimumSize(QSize(100, 0));
        measurePh->setFont(font);

        gridLayout->addWidget(measurePh, 4, 5, 1, 1);

        productBtn = new QPushButton(CreateStockLimit);
        productBtn->setObjectName(QStringLiteral("productBtn"));

        gridLayout->addWidget(productBtn, 3, 0, 1, 2);

        maxValueEdit = new QLineEdit(CreateStockLimit);
        maxValueEdit->setObjectName(QStringLiteral("maxValueEdit"));

        gridLayout->addWidget(maxValueEdit, 7, 3, 1, 1);

        QWidget::setTabOrder(productBtn, addBtn);
        QWidget::setTabOrder(addBtn, cancelBtn);

        retranslateUi(CreateStockLimit);

        QMetaObject::connectSlotsByName(CreateStockLimit);
    } // setupUi

    void retranslateUi(QDialog *CreateStockLimit)
    {
        CreateStockLimit->setWindowTitle(QApplication::translate("CreateStockLimit", "Create/Update  stock limit", 0));
        measureLb->setText(QApplication::translate("CreateStockLimit", "Measure:", 0));
        addBtn->setText(QApplication::translate("CreateStockLimit", "Add", 0));
        cancelBtn->setText(QApplication::translate("CreateStockLimit", "Cancel", 0));
        prodNameLb->setText(QApplication::translate("CreateStockLimit", "Product name:", 0));
        volumeLb->setText(QApplication::translate("CreateStockLimit", "Volume:", 0));
        prodNamePh->setText(QString());
        volumePh->setText(QString());
#ifndef QT_NO_TOOLTIP
        minValueEdit->setToolTip(QApplication::translate("CreateStockLimit", "<html><head/><body><p>For example: 300 (pedends on currency, in that case 300 USD)</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        stockBtn->setText(QApplication::translate("CreateStockLimit", "Select stock", 0));
        warehousePh->setText(QString());
        minLb->setText(QApplication::translate("CreateStockLimit", "Minimum value:", 0));
        warehouseLb_2->setText(QApplication::translate("CreateStockLimit", "In which warehouse:", 0));
        countLb->setText(QApplication::translate("CreateStockLimit", "Maximum value:", 0));
        measurePh->setText(QString());
        productBtn->setText(QApplication::translate("CreateStockLimit", "Select product", 0));
#ifndef QT_NO_TOOLTIP
        maxValueEdit->setToolTip(QApplication::translate("CreateStockLimit", "<html><head/><body><p>For example: 100</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class CreateStockLimit: public Ui_CreateStockLimit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATESTOCKLMDLG_H
