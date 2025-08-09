#include "stdafx.h"
#include "CreateAccblExpDlg.h"
#include "DataForm.h"



CreateAccblExpDlg::CreateAccblExpDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	CreateAccblRepDlg *dataFormParent = (CreateAccblRepDlg *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->parent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	sumEdit->setValidator(vDouble);
	countEdit->setValidator(vDouble);
	countEdit->setMaxLength(17);
	sumEdit->setMaxLength(17);
	deleteBtn->hide();
	QObject::connect(addBtn, &QPushButton::released, this, &CreateAccblExpDlg::CreateExpose);
	QObject::connect(deleteBtn, &QPushButton::released, this, &CreateAccblExpDlg::DeleteExpose);
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateAccblExpDlg::Close);
	QObject::connect(countEdit, &QLineEdit::textChanged, this, &CreateAccblExpDlg::TextEditChanged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreateAccblExpDlg::TextEditChanged);
	QObject::connect(this, SIGNAL(IncrementItemEditChanged(double)), dataFormParent, SLOT(IncrementItemSum(double)));
	QObject::connect(this, SIGNAL(DecrementItemEditChanged(double)), dataFormParent, SLOT(DecrementItemSum(double)));
	InitComboBox();
}

CreateAccblExpDlg::~CreateAccblExpDlg()
{
	delete vInt;
	delete vDouble;
}



void CreateAccblExpDlg::SetExposeParams(QString eName, double eCount, double eSum, int mID, int cID, int id)
{
	eDoc->SetExpenseName(eName.toUtf8().constData());
	eDoc->SetCount(eCount);
	eDoc->SetSum(eSum);
	eDoc->SetMeasureID(mID);
	eDoc->SetCurrencyID(cID);
	eDoc->SetID(id);
}

void CreateAccblExpDlg::FillEditElements(QString eName, double eCount, double eSum, int mID, int cID)
{
	expenseTextEdit->setText(eName);
	countEdit->setText(QString::number(eCount));
	sumEdit->setText(QString::number(eSum));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(cID)));
	measureCmb->setCurrentIndex(measureCmb->findData(QVariant(mID)));
}

bool CreateAccblExpDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetExposeParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateAccblExpDlg::CreateExpose()
{
	errorMessage.clear();
	if (0 != countEdit->text().toInt() && 0.0 != sumEdit->text().toDouble() && !expenseTextEdit->toPlainText().isEmpty())
	{
		CreateAccblRepDlg *parentDataForm = (CreateAccblRepDlg*)parentForm;
		SetExposeParams(expenseTextEdit->toPlainText(), countEdit->text().toInt(), sumEdit->text().toDouble(), measureCmb->currentData().toInt(), currencyCmb->currentData().toInt());
		if (parentDataForm != nullptr)
		{
			QList<QStandardItem*> exposeItem;
				exposeItem << new QStandardItem(QString::number(eDoc->GetID()))
					<< new QStandardItem(eDoc->GetExpenseName().c_str())
					<< new QStandardItem(QString::number(eDoc->GetCount(), 'f', 3))
					<< new QStandardItem(QString::number(eDoc->GetSum(), 'f', 3))
					<< new QStandardItem(QString::number(eDoc->GetMeasureID()))
					<< new QStandardItem(QString::number(eDoc->GetCurrencyID()));
				
				QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->itemTableView->model();
				itemModel->appendRow(exposeItem);

				emit IncrementItemEditChanged(eDoc->GetSum());
			Close();
		}
		else
		{

			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));

			errorMessage.clear();
		}

	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please fill user, value, date and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateAccblExpDlg::DeleteExpose()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irrExpievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";

	((CreateAccblRepDlg *)this->parent())->itemTableView->model()->removeRow(((CreateAccblRepDlg *)this->parent())->itemTableView->selectionModel()->currentIndex().row());

}

void CreateAccblExpDlg::Close()
{
	this->parentWidget()->close();
}



void CreateAccblExpDlg::TextEditChanged()
{
	if (countEdit->text().contains(","))
	{
		countEdit->setText(countEdit->text().replace(",", "."));
	}
	if (countEdit->text().contains(".."))
	{
		countEdit->setText(countEdit->text().replace("..", "."));
	}
	if (sumEdit->text().contains(","))
	{
		sumEdit->setText(sumEdit->text().replace(",", "."));
	}
	if (sumEdit->text().contains(".."))
	{
		sumEdit->setText(sumEdit->text().replace("..", "."));
	}
}

void CreateAccblExpDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			if(curVector[i].GetMainTrade() == true)
				currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}
	std::vector<BusinessLayer::Measure> meaVector = dialogBL->GetAllDataForClass<BusinessLayer::Measure>(errorMessage);
	if (!meaVector.empty())
	{
		for (unsigned int i = 0; i < meaVector.size(); i++)
		{
			measureCmb->addItem(meaVector[i].GetShortName().c_str(), QVariant(meaVector[i].GetID()));
		}
	}
}