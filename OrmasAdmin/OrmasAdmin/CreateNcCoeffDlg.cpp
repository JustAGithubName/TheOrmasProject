#include "stdafx.h"
#include "CreateNcCoeffDlg.h"
#include "DataForm.h"



CreateNcCoeffDlg::CreateNcCoeffDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	

	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateNcCoeffDlg::EditNetCostCoefficient);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateNcCoeffDlg::CreateNetCostCoefficient);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateNcCoeffDlg::Close);
	QObject::connect(productBtn, &QPushButton::released, this, &CreateNcCoeffDlg::OpenPrdDlg);
}

CreateNcCoeffDlg::~CreateNcCoeffDlg()
{
}


void CreateNcCoeffDlg::SetID(int ID, QString childName)
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

			if (childName == QString("productForm"))
			{
				productEdit->setText(QString::number(ID));
				BusinessLayer::Product product;
				if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					prNamePh->setText(product.GetName().c_str());
					
				}
			}
		}
	}
}

void CreateNcCoeffDlg::SetNetCostCoefficientParams(double nCoeff, int nProductID, QString nComment, int id)
{
	netCostCoefficient->SetValue(nCoeff);
	netCostCoefficient->SetProductID(nProductID);
	netCostCoefficient->SetComment(nComment.toUtf8().constData());
	netCostCoefficient->SetID(id);
}

void CreateNcCoeffDlg::FillEditElements(double nCoeff, int nProductID, QString nComment)
{
	commentEdit->setText(nComment);
	valueSpBox->setValue(nCoeff);
	productEdit->setText(QString::number(nProductID));
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), nProductID, errorMessage))
	{
		prNamePh->setText(product.GetName().c_str());
	}
}

bool CreateNcCoeffDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetNetCostCoefficientParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateNcCoeffDlg::CreateNetCostCoefficient()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetNetCostCoefficientParams(valueSpBox->value(), productEdit->text().toInt(), commentEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateNetCostCoefficient(netCostCoefficient, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Product *product = new BusinessLayer::Product;
					if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), netCostCoefficient->GetProductID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete product;
						return;
					}

					QList<QStandardItem*> NetCostCoefficientItem;
					NetCostCoefficientItem << new QStandardItem(QString::number(netCostCoefficient->GetID()))
						<< new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(netCostCoefficient->GetValue()))
						<< new QStandardItem(QString::number(netCostCoefficient->GetProductID()))
						<< new QStandardItem(netCostCoefficient->GetComment().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(NetCostCoefficientItem);

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

			errorMessage.clear();
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please fill product, value!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateNcCoeffDlg::EditNetCostCoefficient()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt())
	{
		if (netCostCoefficient->GetProductID() != productEdit->text().toInt()
			|| netCostCoefficient->GetValue() != valueSpBox->value() || QString(netCostCoefficient->GetComment().c_str()) != commentEdit->text())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetNetCostCoefficientParams(valueSpBox->value(), productEdit->text().toInt(), commentEdit->text(), netCostCoefficient->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateNetCostCoefficient(netCostCoefficient, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Product *product = new BusinessLayer::Product;
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), netCostCoefficient->GetProductID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete product;
							return;
						}

						itemModel->item(mIndex.row(), 1)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(netCostCoefficient->GetValue()));
						itemModel->item(mIndex.row(), 3)->setText(QString::number(netCostCoefficient->GetProductID()));
						itemModel->item(mIndex.row(), 4)->setText(netCostCoefficient->GetComment().c_str());
						
						emit itemModel->dataChanged(mIndex, mIndex);
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
			QString(tr("Please fill user, value and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateNcCoeffDlg::Close()
{
	this->parentWidget()->close();
}

void CreateNcCoeffDlg::OpenPrdDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Products"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	BusinessLayer::ProductType *pType = new BusinessLayer::ProductType();
	pType->SetCode("PRODUCT");
	std::string pTypeFilter = dialogBL->GenerateFilter<BusinessLayer::ProductType>(pType);
	std::vector<BusinessLayer::ProductType> pTypeVector = dialogBL->GetAllDataForClass<BusinessLayer::ProductType>(errorMessage, pTypeFilter);
	if (pTypeVector.size() == 0)
	{
		delete pType;
		QString message = tr("Sorry could not find product type with \"Product\" code!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	BusinessLayer::Product *product = new BusinessLayer::Product();
	product->SetProductTypeID(pTypeVector.at(0).GetID());
	std::string productFilter = dialogBL->GenerateFilter<BusinessLayer::Product>(product);
	std::vector<BusinessLayer::ProductView> productVector = dialogBL->GetAllDataForClass<BusinessLayer::ProductView>(errorMessage, productFilter);
	if (productVector.size() == 0)
	{
		delete product;
		QString message = tr("Sorry could not find product with \"product\" code!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}
	dForm->FillTable<BusinessLayer::ProductView>(errorMessage, productFilter);
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

