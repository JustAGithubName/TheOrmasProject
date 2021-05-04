#include "stdafx.h"

#include "CreateSpecListDlg.h"
#include "DataForm.h"


CreateSpecListDlg::CreateSpecListDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	specificationID = ((DataForm*)parent)->specificationID;
	vDouble = new QDoubleValidator(0.00, 1000000000.00000, 5, this);
	vInt = new QIntValidator(0, 1000000000, this);
	productEdit->setValidator(vInt);
	countEdit->setValidator(vDouble);
	countEdit->setMaxLength(24);
	specEdit->setValidator(vInt);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(addBtn, &QPushButton::released, this, &CreateSpecListDlg::EditProductInList);
	}
	else
	{
		specEdit->setText("0");
		countEdit->setText("0");
		productEdit->setText("0");
		QObject::connect(addBtn, &QPushButton::released, this, &CreateSpecListDlg::AddProductToList);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateSpecListDlg::Close);
	QObject::connect(specBtn, &QPushButton::released, this, &CreateSpecListDlg::OpenSpecDlg);
	QObject::connect(productBtn, &QPushButton::released, this, &CreateSpecListDlg::OpenProdDlg);
	QObject::connect(countEdit, &QLineEdit::textChanged, this, &CreateSpecListDlg::TextEditChanged);
	QObject::connect(this, SIGNAL(DataIsChanged()), ((DataForm*)parent), SLOT(OnRowsNumberChanged()));
}

CreateSpecListDlg::~CreateSpecListDlg()
{
	delete vDouble;
	delete vInt;
}

void CreateSpecListDlg::SetID(int ID, QString childName)
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
					prodNamePh->setText(product.GetName().c_str());
					volumePh->setText(QString::number(product.GetVolume()));
					BusinessLayer::Measure measure;
					if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
					{
						measurePh->setText(measure.GetName().c_str());
					}
				}
			}
			if (childName == QString("specificationForm"))
			{
				specEdit->setText(QString::number(ID));
			}
		}
	}
}

void CreateSpecListDlg::SetSpecificationListParams(int sID, int pID, double slCount, int id)
{
	specificationList->SetSpecificationID(sID);
	specificationList->SetProductID(pID);
	specificationList->SetCount(slCount);
	specificationList->SetID(id);
}

void CreateSpecListDlg::FillEditElements(int sID, int pID, double slCount)

{
	specEdit->setText(QString::number(sID));
	productEdit->setText(QString::number(pID));
	countEdit->setText(QString::number(slCount, 'f', 3));
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pID, errorMessage))
	{
		prodNamePh->setText(product.GetName().c_str());
		volumePh->setText(QString::number(product.GetVolume()));
		BusinessLayer::Measure measure;
		if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			measurePh->setText(measure.GetName().c_str());
		}
	}
}

bool CreateSpecListDlg::FillDlgElements(QTableView* oTable)
{
	QModelIndex mIndex = oTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetSpecificationListParams(oTable->model()->data(oTable->model()->index(mIndex.row(), 1)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 5)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 3)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(oTable->model()->data(oTable->model()->index(mIndex.row(), 1)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 5)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 3)).toDouble());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateSpecListDlg::AddProductToList()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() || 0 != countEdit->text().toDouble())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		BusinessLayer::Product *product = new BusinessLayer::Product();
		BusinessLayer::Measure *measure = new BusinessLayer::Measure();

		if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productEdit->text().toInt(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage.clear();
			delete product;			
			return;
		}
		
		if(!measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage.clear();
			delete measure;
			return;
		}

		SetSpecificationListParams(specificationID, productEdit->text().toInt(), countEdit->text().toDouble());

		if (dialogBL->CreateSpecificationList(specificationList, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> productListItem;
					productListItem << new QStandardItem(QString::number(specificationList->GetID()));
					if (0 != specificationList)
					{
						productListItem << new QStandardItem(QString::number(specificationID));
					}
					else
					{
						productListItem << new QStandardItem(QString::number(0));
					}
					productListItem << new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(specificationList->GetCount(), 'f', 3))
						<< new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(QString::number(specificationList->GetProductID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(productListItem);
				}
			}
			delete measure;
			delete product;
			Close();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("This product is not valid! Please delete it!")),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateSpecListDlg::EditProductInList()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() || 0 != countEdit->text().toDouble())
	{
		if (productEdit->text().toInt() != specificationList->GetProductID() || countEdit->text().toDouble() != specificationList->GetCount()
			|| specEdit->text().toInt() != specificationList->GetSpecificationID())
		{
			BusinessLayer::Product *product = new BusinessLayer::Product();
			if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productEdit->text().toInt(), errorMessage))
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				delete product;
				return;
			}
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetSpecificationListParams(specEdit->text().toInt(), productEdit->text().toInt(), countEdit->text().toDouble(), specificationList->GetID());
			if (dialogBL->UpdateSpecificationList(specificationList, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Measure *measure = new BusinessLayer::Measure();
						if (!measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetMeasureID(), errorMessage))
						{
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete measure;
							return;
						}

						
						itemModel->item(mIndex.row(), 1)->setText(QString::number(specificationList->GetSpecificationID()));
						itemModel->item(mIndex.row(), 2)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(specificationList->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 4)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(QString::number(specificationList->GetProductID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						emit DataIsChanged();
						delete measure;
					}
				}
				delete product;
				
				Close();
			}
			else
			{
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
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateSpecListDlg::Close()
{
	this->parentWidget()->close();
}

void CreateSpecListDlg::OpenProdDlg()
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
	pType->SetCode("RAW");
	std::string pTypeFilter = dialogBL->GenerateFilter<BusinessLayer::ProductType>(pType);
	std::vector<BusinessLayer::ProductType> pTypeVector = dialogBL->GetAllDataForClass<BusinessLayer::ProductType>(errorMessage, pTypeFilter);
	if (pTypeVector.size() == 0)
	{
		delete pType;
		QString message = tr("Sorry could not find product type with \"Raw\" code!");
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
		QString message = tr("Sorry could not find product with \"Product\" code!");
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


void CreateSpecListDlg::OpenSpecDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Specifications"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::SpecificationView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("SpecificationForm");
		dForm->QtConnect<BusinessLayer::SpecificationView>();
		QMdiSubWindow *specificationWindow = new QMdiSubWindow;
		specificationWindow->setWidget(dForm);
		specificationWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(specificationWindow);
		specificationWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All Specifications are shown");
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

void CreateSpecListDlg::TextEditChanged()
{
	if (countEdit->text().contains(","))
	{
		countEdit->setText(countEdit->text().replace(",", "."));
	}
	if (countEdit->text().contains(".."))
	{
		countEdit->setText(countEdit->text().replace("..", "."));
	}
}