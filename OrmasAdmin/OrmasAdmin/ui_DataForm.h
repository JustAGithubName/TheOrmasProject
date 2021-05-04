/********************************************************************************
** Form generated from reading UI file 'DataForm.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAFORM_H
#define UI_DATAFORM_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
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

class Ui_DataForm
{
public:
    QGridLayout *gridLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QPushButton *prevBtn;
    QLabel *countLb;
    QLabel *fromLb;
    QLabel *maxCountLb;
    QPushButton *nextBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *refreshBtn;
    QPushButton *viewBtn;
    QPushButton *createBtn;
    QPushButton *editBtn;
    QPushButton *deleteBtn;
    QPushButton *closeBtn;
    QWidget *functionWidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QGridLayout *gridLayout_3;
    QLabel *valueLb;
    QLabel *columnLb;
    QComboBox *columnCmb;
    QComboBox *typeCmb;
    QLineEdit *valueEdit;
    QLabel *filterTypeLb;
    QPushButton *filterBtn;
    QWidget *tab2;
    QGridLayout *gridLayout_4;
    QComboBox *columnSearchCmb;
    QLineEdit *valueSearchEdit;
    QLabel *valueSearchLb;
    QLabel *columnSearchLb;
    QPushButton *searchBtn;
    QWidget *filterWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *currentFilterLb;
    QLabel *filterTextLb;
    QPushButton *clearBtn;

    void setupUi(QWidget *DataForm)
    {
        if (DataForm->objectName().isEmpty())
            DataForm->setObjectName(QStringLiteral("DataForm"));
        DataForm->resize(800, 600);
        DataForm->setMinimumSize(QSize(800, 600));
        DataForm->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(DataForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(12, 12, 12, 12);
        tableView = new QTableView(DataForm);
        tableView->setObjectName(QStringLiteral("tableView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);

        gridLayout->addWidget(tableView, 2, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        prevBtn = new QPushButton(DataForm);
        prevBtn->setObjectName(QStringLiteral("prevBtn"));
        prevBtn->setMinimumSize(QSize(25, 0));
        prevBtn->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(prevBtn);

        countLb = new QLabel(DataForm);
        countLb->setObjectName(QStringLiteral("countLb"));
        countLb->setMinimumSize(QSize(30, 0));
        countLb->setMaximumSize(QSize(16777215, 16777215));
        countLb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(countLb);

        fromLb = new QLabel(DataForm);
        fromLb->setObjectName(QStringLiteral("fromLb"));
        fromLb->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(fromLb);

        maxCountLb = new QLabel(DataForm);
        maxCountLb->setObjectName(QStringLiteral("maxCountLb"));
        maxCountLb->setMinimumSize(QSize(30, 0));
        maxCountLb->setMaximumSize(QSize(16777215, 16777215));
        maxCountLb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(maxCountLb);

        nextBtn = new QPushButton(DataForm);
        nextBtn->setObjectName(QStringLiteral("nextBtn"));
        nextBtn->setMinimumSize(QSize(25, 0));
        nextBtn->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(nextBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        refreshBtn = new QPushButton(DataForm);
        refreshBtn->setObjectName(QStringLiteral("refreshBtn"));

        horizontalLayout->addWidget(refreshBtn);

        viewBtn = new QPushButton(DataForm);
        viewBtn->setObjectName(QStringLiteral("viewBtn"));

        horizontalLayout->addWidget(viewBtn);

        createBtn = new QPushButton(DataForm);
        createBtn->setObjectName(QStringLiteral("createBtn"));
        createBtn->setMinimumSize(QSize(75, 0));

        horizontalLayout->addWidget(createBtn);

        editBtn = new QPushButton(DataForm);
        editBtn->setObjectName(QStringLiteral("editBtn"));
        editBtn->setMinimumSize(QSize(75, 0));

        horizontalLayout->addWidget(editBtn);

        deleteBtn = new QPushButton(DataForm);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));
        deleteBtn->setMinimumSize(QSize(75, 0));

        horizontalLayout->addWidget(deleteBtn);

        closeBtn = new QPushButton(DataForm);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setMinimumSize(QSize(75, 0));

        horizontalLayout->addWidget(closeBtn);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 2);

        functionWidget = new QWidget(DataForm);
        functionWidget->setObjectName(QStringLiteral("functionWidget"));
        functionWidget->setMaximumSize(QSize(16777215, 55));
        gridLayout_2 = new QGridLayout(functionWidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(functionWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        gridLayout_3 = new QGridLayout(tab1);
        gridLayout_3->setSpacing(3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(3, 3, 3, 3);
        valueLb = new QLabel(tab1);
        valueLb->setObjectName(QStringLiteral("valueLb"));
        valueLb->setMaximumSize(QSize(70, 16777215));
        valueLb->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(valueLb, 0, 4, 1, 1);

        columnLb = new QLabel(tab1);
        columnLb->setObjectName(QStringLiteral("columnLb"));
        columnLb->setMaximumSize(QSize(60, 16777215));
        columnLb->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(columnLb, 0, 0, 1, 1);

        columnCmb = new QComboBox(tab1);
        columnCmb->setObjectName(QStringLiteral("columnCmb"));

        gridLayout_3->addWidget(columnCmb, 0, 1, 1, 1);

        typeCmb = new QComboBox(tab1);
        typeCmb->setObjectName(QStringLiteral("typeCmb"));

        gridLayout_3->addWidget(typeCmb, 0, 3, 1, 1);

        valueEdit = new QLineEdit(tab1);
        valueEdit->setObjectName(QStringLiteral("valueEdit"));
        valueEdit->setMaximumSize(QSize(100, 16777215));
        valueEdit->setReadOnly(false);

        gridLayout_3->addWidget(valueEdit, 0, 5, 1, 1);

        filterTypeLb = new QLabel(tab1);
        filterTypeLb->setObjectName(QStringLiteral("filterTypeLb"));
        filterTypeLb->setMaximumSize(QSize(80, 16777215));
        filterTypeLb->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(filterTypeLb, 0, 2, 1, 1);

        filterBtn = new QPushButton(tab1);
        filterBtn->setObjectName(QStringLiteral("filterBtn"));
        filterBtn->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(filterBtn, 0, 6, 1, 1);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        gridLayout_4 = new QGridLayout(tab2);
        gridLayout_4->setSpacing(3);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(3, 3, 3, 3);
        columnSearchCmb = new QComboBox(tab2);
        columnSearchCmb->setObjectName(QStringLiteral("columnSearchCmb"));

        gridLayout_4->addWidget(columnSearchCmb, 0, 1, 1, 1);

        valueSearchEdit = new QLineEdit(tab2);
        valueSearchEdit->setObjectName(QStringLiteral("valueSearchEdit"));
        valueSearchEdit->setMaximumSize(QSize(150, 16777215));

        gridLayout_4->addWidget(valueSearchEdit, 0, 3, 1, 1);

        valueSearchLb = new QLabel(tab2);
        valueSearchLb->setObjectName(QStringLiteral("valueSearchLb"));
        valueSearchLb->setMaximumSize(QSize(100, 16777215));
        valueSearchLb->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(valueSearchLb, 0, 2, 1, 1);

        columnSearchLb = new QLabel(tab2);
        columnSearchLb->setObjectName(QStringLiteral("columnSearchLb"));
        columnSearchLb->setMaximumSize(QSize(100, 16777215));
        columnSearchLb->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(columnSearchLb, 0, 0, 1, 1);

        searchBtn = new QPushButton(tab2);
        searchBtn->setObjectName(QStringLiteral("searchBtn"));
        searchBtn->setMaximumSize(QSize(100, 16777215));

        gridLayout_4->addWidget(searchBtn, 0, 4, 1, 1);

        tabWidget->addTab(tab2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        gridLayout->addWidget(functionWidget, 0, 0, 1, 2);

        filterWidget = new QWidget(DataForm);
        filterWidget->setObjectName(QStringLiteral("filterWidget"));
        filterWidget->setMinimumSize(QSize(0, 18));
        horizontalLayout_2 = new QHBoxLayout(filterWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        currentFilterLb = new QLabel(filterWidget);
        currentFilterLb->setObjectName(QStringLiteral("currentFilterLb"));
        currentFilterLb->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(currentFilterLb);

        filterTextLb = new QLabel(filterWidget);
        filterTextLb->setObjectName(QStringLiteral("filterTextLb"));

        horizontalLayout_2->addWidget(filterTextLb);

        clearBtn = new QPushButton(filterWidget);
        clearBtn->setObjectName(QStringLiteral("clearBtn"));
        clearBtn->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(clearBtn);


        gridLayout->addWidget(filterWidget, 1, 0, 1, 2);

        QWidget::setTabOrder(tableView, createBtn);
        QWidget::setTabOrder(createBtn, editBtn);
        QWidget::setTabOrder(editBtn, deleteBtn);
        QWidget::setTabOrder(deleteBtn, closeBtn);

        retranslateUi(DataForm);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DataForm);
    } // setupUi

    void retranslateUi(QWidget *DataForm)
    {
        DataForm->setWindowTitle(QString());
        prevBtn->setText(QApplication::translate("DataForm", "<", 0));
        countLb->setText(QApplication::translate("DataForm", "0", 0));
        fromLb->setText(QApplication::translate("DataForm", "from", 0));
        maxCountLb->setText(QString());
        nextBtn->setText(QApplication::translate("DataForm", ">", 0));
        refreshBtn->setText(QApplication::translate("DataForm", "Refresh", 0));
        viewBtn->setText(QApplication::translate("DataForm", "View", 0));
        createBtn->setText(QApplication::translate("DataForm", "Create", 0));
        editBtn->setText(QApplication::translate("DataForm", "Edit", 0));
        deleteBtn->setText(QApplication::translate("DataForm", "Delete", 0));
        closeBtn->setText(QApplication::translate("DataForm", "Close", 0));
        valueLb->setText(QApplication::translate("DataForm", "Value:", 0));
        columnLb->setText(QApplication::translate("DataForm", "Column:", 0));
        filterTypeLb->setText(QApplication::translate("DataForm", "Filter type:", 0));
        filterBtn->setText(QApplication::translate("DataForm", "Filter", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("DataForm", "Filter", 0));
        valueSearchLb->setText(QApplication::translate("DataForm", "Vlaue:", 0));
        columnSearchLb->setText(QApplication::translate("DataForm", "Column:", 0));
        searchBtn->setText(QApplication::translate("DataForm", "Search", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("DataForm", "Search", 0));
        currentFilterLb->setText(QApplication::translate("DataForm", "Current filter:", 0));
        filterTextLb->setText(QString());
        clearBtn->setText(QApplication::translate("DataForm", "Clear filter", 0));
    } // retranslateUi

};

namespace Ui {
    class DataForm: public Ui_DataForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAFORM_H
