#include "stdafx.h"

#include "ReworkRawDlg.h"
#include "DataForm.h"


ReworkRawDlg::ReworkRawDlg(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	mainForm = (MainForm *)this->parentForm;
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	countEdit->setValidator(vDouble);
	countEdit->setMaxLength(20);
	
	QObject::connect(createBtn, &QPushButton::released, this, &ReworkRawDlg::Rework);
	QObject::connect(cancelBtn, &QPushButton::released, this, &ReworkRawDlg::Close);
	QObject::connect(productBtn, &QPushButton::released, this, &ReworkRawDlg::OpenProdDlg);
	QObject::connect(countEdit, &QLineEdit::textChanged, this, &ReworkRawDlg::TextEditChanged);
}

ReworkRawDlg::~ReworkRawDlg()
{
	delete vDouble;
}

void ReworkRawDlg::SetID(int ID, QString childName)
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
				if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					if(spec.GetSpecificationByProductID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
					{
						productEdit->setText(QString::number(ID));
						prodNamePh->setText(product.GetName().c_str());
						volumePh->setText(QString::number(product.GetVolume()));
						BusinessLayer::Measure measure;
						if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
						{
							measurePh->setText(measure.GetName().c_str());
						}
					}
					else
					{
						product.Clear();
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr("Cannot rework this raw, because cannot find it in specification")),
							QString(tr("Ok")));
						errorMessage.clear();
						return;
					}
				}
			}
		}
	}
}

void ReworkRawDlg::Rework()
{
	errorMessage.clear();
	
	if (0 != productEdit->text().toInt() || 0 != countEdit->text().toDouble())
	{
		if (!product.IsEmpty() && !spec.IsEmpty())
		{
			BusinessLayer::SpecificationListView *specList = new BusinessLayer::SpecificationListView();
			specList->SetSpecificationID(spec.GetID());
			std::string filter = dialogBL->GenerateFilter<BusinessLayer::SpecificationList>(specList);
			std::vector<BusinessLayer::SpecificationListView> sListVector = dialogBL->GetAllDataForClass<BusinessLayer::SpecificationListView>(errorMessage, filter);
			if (sListVector.size() > 0)
			{
				BusinessLayer::Product curProduct;
				BusinessLayer::ProductionStock pStock;
				double curCount = 0;
				double curSum = 0;
				double totalSum = 0;
				dialogBL->StartIsolatedTransaction(errorMessage);
				for each (auto item in sListVector)
				{
					curCount = 0;
					curSum = 0;
					if (curProduct.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
					{
						curCount = round(countEdit->text().toDouble() * item.GetCount() *1000)/1000;
						curSum = round(item.GetCount()* curProduct.GetPrice() * 1000) / 1000;
						if (!pStock.ChangingByReworkRawDec(dialogBL->globalVar, dialogBL->GetOrmasDal(), curProduct.GetID(), curCount, curSum, errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							return;
						}
						totalSum += curSum;
					}
					else
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr("Cannot rework this raw, because specification is wrong!")),
							QString(tr("Ok")));
						errorMessage.clear();
						return;
					}
				}
				if (!pStock.ChangingByReworkRawInc(dialogBL->globalVar, dialogBL->GetOrmasDal(), curProduct.GetID(), countEdit->text().toDouble(), totalSum, errorMessage))
				{
					dialogBL->CancelTransaction(errorMessage);
					QMessageBox::information(NULL, QString(tr("Warning")),
						QString(tr(errorMessage.c_str())),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
				else
				{
					product.SetPrice(totalSum);
					if (!product.UpdateProduct(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						return;
					}
					else
					{
						if (!dialogBL->CommitTransaction(errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
						}
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr("Reworking the raw is successfully ended!")),
							QString(tr("Ok")));
						errorMessage.clear();
						return;
					}
				}
			}

		}
	}

	errorMessage.clear();
}

void ReworkRawDlg::Close()
{
	this->parentWidget()->close();
}

void ReworkRawDlg::OpenProdDlg()
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
		QString message = tr("Sorry could not find product with \"Raw\" code!");
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

void ReworkRawDlg::TextEditChanged()
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

