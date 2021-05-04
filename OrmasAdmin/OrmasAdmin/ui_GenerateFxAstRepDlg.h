/********************************************************************************
** Form generated from reading UI file 'GenerateFxAstRepDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEFXASTREPDLG_H
#define UI_GENERATEFXASTREPDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_GenerateFixedAssetsReport
{
public:
    QGridLayout *gridLayout;
    QCheckBox *allCbx;
    QLabel *label_2;
    QLabel *empSurnamePh;
    QLabel *empNamePh;
    QLabel *empPhonePh;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QComboBox *fixedCbx;

    void setupUi(QDialog *GenerateFixedAssetsReport)
    {
        if (GenerateFixedAssetsReport->objectName().isEmpty())
            GenerateFixedAssetsReport->setObjectName(QStringLiteral("GenerateFixedAssetsReport"));
        GenerateFixedAssetsReport->resize(645, 139);
        GenerateFixedAssetsReport->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GenerateFixedAssetsReport->setModal(false);
        gridLayout = new QGridLayout(GenerateFixedAssetsReport);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        allCbx = new QCheckBox(GenerateFixedAssetsReport);
        allCbx->setObjectName(QStringLiteral("allCbx"));
        allCbx->setChecked(true);

        gridLayout->addWidget(allCbx, 0, 1, 1, 1);

        label_2 = new QLabel(GenerateFixedAssetsReport);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        empSurnamePh = new QLabel(GenerateFixedAssetsReport);
        empSurnamePh->setObjectName(QStringLiteral("empSurnamePh"));
        empSurnamePh->setMinimumSize(QSize(100, 0));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        empSurnamePh->setFont(font);

        gridLayout->addWidget(empSurnamePh, 2, 3, 1, 1);

        empNamePh = new QLabel(GenerateFixedAssetsReport);
        empNamePh->setObjectName(QStringLiteral("empNamePh"));
        empNamePh->setMinimumSize(QSize(100, 0));
        empNamePh->setFont(font);

        gridLayout->addWidget(empNamePh, 2, 2, 1, 1);

        empPhonePh = new QLabel(GenerateFixedAssetsReport);
        empPhonePh->setObjectName(QStringLiteral("empPhonePh"));
        empPhonePh->setMinimumSize(QSize(100, 0));
        empPhonePh->setFont(font);

        gridLayout->addWidget(empPhonePh, 2, 4, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okBtn = new QPushButton(GenerateFixedAssetsReport);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(GenerateFixedAssetsReport);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout, 4, 1, 1, 4);

        fixedCbx = new QComboBox(GenerateFixedAssetsReport);
        fixedCbx->setObjectName(QStringLiteral("fixedCbx"));

        gridLayout->addWidget(fixedCbx, 1, 2, 1, 3);

        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(GenerateFixedAssetsReport);

        QMetaObject::connectSlotsByName(GenerateFixedAssetsReport);
    } // setupUi

    void retranslateUi(QDialog *GenerateFixedAssetsReport)
    {
        GenerateFixedAssetsReport->setWindowTitle(QApplication::translate("GenerateFixedAssetsReport", "Generate agent", 0));
        allCbx->setText(QApplication::translate("GenerateFixedAssetsReport", "For all fixed assets", 0));
        label_2->setText(QApplication::translate("GenerateFixedAssetsReport", "Select fixed asset group", 0));
        empSurnamePh->setText(QString());
        empNamePh->setText(QString());
        empPhonePh->setText(QString());
        okBtn->setText(QApplication::translate("GenerateFixedAssetsReport", "OK", 0));
        cancelBtn->setText(QApplication::translate("GenerateFixedAssetsReport", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateFixedAssetsReport: public Ui_GenerateFixedAssetsReport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEFXASTREPDLG_H
