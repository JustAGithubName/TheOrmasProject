#include "stdafx.h"
#include "CreatePrdBrnDlg.h"
#include "DataForm.h"



CreatePrdBrnDlg::CreatePrdBrnDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vInt = new QIntValidator(0, 1000000000, this);
	branchEdit->setValidator(vInt);
	productEdit->setValidator(vInt);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePrdBrnDlg::EditProductBranch);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePrdBrnDlg::CreateProductBranch);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreatePrdBrnDlg::Close);
	QObject::connect(branchBtn, &QPushButton::released, this, &CreatePrdBrnDlg::OpenBrnDlg);
	QObject::connect(productBtn, &QPushButton::released, this, &CreatePrdBrnDlg::OpenProdDlg);
}

CreatePrdBrnDlg::~CreatePrdBrnDlg()
{
	delete vInt;
}


void CreatePrdBrnDlg::SetID(int ID, QString childName)
{
	if (0 != ID)
	{
		if (0 != childName.length())
		{
			this->hide();
			this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
			this->show();
			this->raise();
			this->activateWindow();
			QApplication::setActiveWindow(this);

			if (childName == QString("branchForm"))
			{
				branchEdit->setText(QString::number(ID));
			}
			BusinessLayer::Branch branch;
			if (branch.GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
			{
				branchNamePh->setText(branch.GetName().c_str());
				addressPh->setText(branch.GetAddress().c_str());
			}
			if (childName == QString("productForm"))
			{
				productEdit->setText(QString::number(ID));
			}
			BusinessLayer::Product product;
			if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
			{
				productNamePh->setText(product.GetName().c_str());
				pricePh->setText(QString::number(product.GetPrice(), 'f', 2));
			}
		}
	}
}


void CreatePrdBrnDlg::SetProductBranchParams(int pProductID, int pBranchID, int id)
{
	productBranch->SetProductID(pProductID);
	productBranch->SetBranchID(pBranchID);
	productBranch->SetID(id);
}

void CreatePrdBrnDlg::FillEditElements(int pProductID, int pBranchID)
{
	branchEdit->setText(QString::number(pBranchID));
	productEdit->setText(QString::number(pProductID));
	BusinessLayer::Branch branch;
	if (branch.GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pBranchID, errorMessage))
	{
		branchNamePh->setText(branch.GetName().c_str());
		addressPh->setText(branch.GetAddress().c_str());
	}
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pProductID, errorMessage))
	{
		productNamePh->setText(product.GetName().c_str());
		pricePh->setText(QString::number(product.GetPrice(), 'f', 2));
	}
}

bool CreatePrdBrnDlg::FillDlgElements(QTableView* aTable)
{
	QModelIndex mIndex = aTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetProductBranchParams(aTable->model()->data(aTable->model()->index(mIndex.row(), 5)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 6)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(aTable->model()->data(aTable->model()->index(mIndex.row(), 5)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 6)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreatePrdBrnDlg::CreateProductBranch()
{
	errorMessage.clear();
	if (0 != branchEdit->text().toInt() && 0 != productEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetProductBranchParams(productEdit->text().toInt(), branchEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateProductBranchRelation(productBranch, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Branch *branch = new BusinessLayer::Branch();
					BusinessLayer::Product *product = new BusinessLayer::Product();
					if (!branch->GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productBranch->GetBranchID(), errorMessage)
						|| !product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productBranch->GetProductID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete product;
						delete branch;
						return;
					}
					QList<QStandardItem*> ProductBranchItem;
					ProductBranchItem << new QStandardItem(QString::number(productBranch->GetID()))
						<< new QStandardItem(branch->GetName().c_str())
						<< new QStandardItem(branch->GetAddress().c_str())
						<< new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(product->GetPrice(), 'f', 2))
						<< new QStandardItem(QString::number(productBranch->GetProductID()))
						<< new QStandardItem(QString::number(productBranch->GetBranchID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(ProductBranchItem);

					delete product;
					delete branch;
				}
			}
			if (!dialogBL->CommitTransaction(errorMessage))
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
			}


			Close();
		}
		else
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));

			errorMessage.clear();
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please fill company, product fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePrdBrnDlg::EditProductBranch()
{
	errorMessage.clear();
	if (0 != branchEdit->text().toInt() && 0 != productEdit->text().toInt())
	{
		if (productBranch->GetProductID() != productEdit->text().toInt() || productBranch->GetBranchID() != branchEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetProductBranchParams(productEdit->text().toInt(), branchEdit->text().toInt(), productBranch->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateProductBranchRelation(productBranch, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Branch *branch = new BusinessLayer::Branch();
						BusinessLayer::Product *product = new BusinessLayer::Product();
						if (!branch->GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productBranch->GetBranchID(), errorMessage)
							|| !product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productBranch->GetProductID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete product;
							delete branch;
							return;
						}

						
						itemModel->item(mIndex.row(), 1)->setText(branch->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(branch->GetAddress().c_str());
						itemModel->item(mIndex.row(), 3)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(product->GetPrice(), 'f', 2));
						itemModel->item(mIndex.row(), 5)->setText(QString::number(productBranch->GetProductID()));
						itemModel->item(mIndex.row(), 6)->setText(QString::number(productBranch->GetBranchID()));;
						emit itemModel->dataChanged(mIndex, mIndex);
						delete branch;
						delete product;
					}
				}
				if (!dialogBL->CommitTransaction(errorMessage))
				{
					dialogBL->CancelTransaction(errorMessage);
					QMessageBox::information(NULL, QString(tr("Warning")),
						QString(tr(errorMessage.c_str())),
						QString(tr("Ok")));
				}

				Close();
			}
			else
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
			}
		}
		else
		{
			Close();
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please enter employee and company item!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePrdBrnDlg::Close()
{
	this->parentWidget()->close();
}

void CreatePrdBrnDlg::OpenBrnDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Branches"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::Branch>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("branchForm");
		dForm->QtConnect<BusinessLayer::Branch>();
		QMdiSubWindow *branchWindow = new QMdiSubWindow;
		branchWindow->setWidget(dForm);
		branchWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(branchWindow);
		branchWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All branches are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}


void CreatePrdBrnDlg::OpenProdDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Products"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::ProductView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("productForm");
		dForm->QtConnect<BusinessLayer::ProductView>();
		QMdiSubWindow *productWindow = new QMdiSubWindow;
		productWindow->setWidget(dForm);
		productWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(productWindow);
		productWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All products are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}

}