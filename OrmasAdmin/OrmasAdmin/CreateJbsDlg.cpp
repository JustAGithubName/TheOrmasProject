#include "stdafx.h"
#include "CreateJbsDlg.h"
#include "DataForm.h"



CreateJbsDlg::CreateJbsDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	employeeEdit->setValidator(vInt);
	countEdit->setValidator(vDouble);
	productEdit->setValidator(vInt);
	countEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateJbsDlg::EditJobsheet);
	}
	else
	{
		dateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreateJbsDlg::CreateJobsheet);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateJbsDlg::Close);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreateJbsDlg::OpenEmpDlg);
	QObject::connect(productBtn, &QPushButton::released, this, &CreateJbsDlg::OpenProdDlg);
	QObject::connect(countEdit, &QLineEdit::textChanged, this, &CreateJbsDlg::TextEditChanged);
}

CreateJbsDlg::~CreateJbsDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateJbsDlg::SetID(int ID, QString childName)
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

			if (childName == QString("employeeForm"))
			{
				employeeEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					empNamePh->setText(user.GetName().c_str());
					empSurnamePh->setText(user.GetSurname().c_str());
					empPhonePh->setText(user.GetPhone().c_str());
				}
			}
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
		}
	}
}

void CreateJbsDlg::SetJobsheetParams(QString jDate, double jCount, int pID, int eID, int id)
{
	jobsheet->SetDate(jDate.toUtf8().constData());
	jobsheet->SetCount(jCount);
	jobsheet->SetProductID(pID);
	jobsheet->SetEmployeeID(eID);
	jobsheet->SetID(id);
}

void CreateJbsDlg::FillEditElements(QString jDate, double jCount, int pID, int eID)
{
	dateEdit->setDate(QDate::fromString(jDate, "dd.MM.yyyy"));
	countEdit->setText(QString::number(jCount, 'f', 3));
	productEdit->setText(QString::number(pID));
	employeeEdit->setText(QString::number(eID));
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
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), eID, errorMessage))
	{
		empNamePh->setText(user.GetName().c_str());
		empSurnamePh->setText(user.GetSurname().c_str());
		empPhonePh->setText(user.GetPhone().c_str());
	}
}

bool CreateJbsDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetJobsheetParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 6)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 6)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateJbsDlg::CreateJobsheet()
{
	errorMessage.clear();
	if (0 != employeeEdit->text().toInt() && 0.0 != countEdit->text().toDouble() && 0 != productEdit->text().toInt()
		&& !dateEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetJobsheetParams(dateEdit->text(), countEdit->text().toDouble(), productEdit->text().toInt(), employeeEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateJobsheet(jobsheet, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Employee *employee = new BusinessLayer::Employee;
					BusinessLayer::Product *product = new BusinessLayer::Product;
					if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobsheet->GetEmployeeID(), errorMessage)
						|| !product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobsheet->GetProductID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete employee;
						delete product;
						return;
					}

					BusinessLayer::Measure *measure = new BusinessLayer::Measure;
					if (!measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetMeasureID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete measure;
						return;
					}

					QList<QStandardItem*> jobsheetItem;
					jobsheetItem << new QStandardItem(QString::number(jobsheet->GetID()))
						<< new QStandardItem(jobsheet->GetDate().c_str())
						<< new QStandardItem(employee->GetName().c_str())
						<< new QStandardItem(employee->GetSurname().c_str())
						<< new QStandardItem(employee->GetPhone().c_str())
						<< new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(jobsheet->GetCount(), 'f', 3))
						<< new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(QString::number(jobsheet->GetProductID()))
						<< new QStandardItem(QString::number(jobsheet->GetEmployeeID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(jobsheetItem);

					delete product;
					delete employee;
					delete measure;
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
			QString(tr("Please fill user, value, date and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateJbsDlg::EditJobsheet()
{
	errorMessage.clear();
	if (0 != employeeEdit->text().toInt() && 0.0 != countEdit->text().toDouble() && 0 != productEdit->text().toInt()
		&& !dateEdit->text().isEmpty())
	{
		if (QString(jobsheet->GetDate().c_str()) != dateEdit->text() || jobsheet->GetEmployeeID() != employeeEdit->text().toInt()
			|| jobsheet->GetCount() != countEdit->text().toDouble() || jobsheet->GetProductID() != productEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetJobsheetParams(dateEdit->text(), countEdit->text().toDouble(), productEdit->text().toInt(), employeeEdit->text().toInt(), jobsheet->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateJobsheet(jobsheet, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Employee *employee = new BusinessLayer::Employee;
						BusinessLayer::Product *product = new BusinessLayer::Product;
						if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobsheet->GetEmployeeID(), errorMessage)
							|| !product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobsheet->GetProductID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete employee;
							delete product;
							return;
						}

						BusinessLayer::Measure *measure = new BusinessLayer::Measure;
						if (!measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetMeasureID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete measure;
							return;
						}

						itemModel->item(mIndex.row(), 1)->setText(jobsheet->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(employee->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(employee->GetSurname().c_str());
						itemModel->item(mIndex.row(), 4)->setText(employee->GetPhone().c_str());
						itemModel->item(mIndex.row(), 5)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 6)->setText(QString::number(jobsheet->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 7)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 8)->setText(QString::number(jobsheet->GetProductID()));
						itemModel->item(mIndex.row(), 9)->setText(QString::number(jobsheet->GetEmployeeID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete product;
						delete employee;
						delete measure;
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

void CreateJbsDlg::Close()
{
	this->parentWidget()->close();
}

void CreateJbsDlg::OpenEmpDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Employees"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::EmployeeView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("employeeForm");
		dForm->QtConnect<BusinessLayer::EmployeeView>();
		QMdiSubWindow *employeeWindow = new QMdiSubWindow;
		employeeWindow->setWidget(dForm);
		employeeWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(employeeWindow);
		employeeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All employees are shown");
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

void CreateJbsDlg::OpenProdDlg()
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

void CreateJbsDlg::TextEditChanged()
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
