#include "stdafx.h"
#include "CreateEmpPrdDlg.h"
#include "DataForm.h"



CreateEmpPrdDlg::CreateEmpPrdDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vInt = new QIntValidator(0, 1000000000, this);
	userEdit->setValidator(vInt);
	productEdit->setValidator(vInt);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateEmpPrdDlg::EditEmployeeProduct);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateEmpPrdDlg::CreateEmployeeProduct);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateEmpPrdDlg::Close);
	QObject::connect(userBtn, &QPushButton::released, this, &CreateEmpPrdDlg::OpenEmpDlg);
	QObject::connect(productBtn, &QPushButton::released, this, &CreateEmpPrdDlg::OpenProdDlg);
}

CreateEmpPrdDlg::~CreateEmpPrdDlg()
{
	delete vInt;
}


void CreateEmpPrdDlg::SetID(int ID, QString childName)
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
				userEdit->setText(QString::number(ID));
			}
			BusinessLayer::User user;
			if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
			{
				namePh->setText(user.GetName().c_str());
				surnamePh->setText(user.GetSurname().c_str());
				phonePh->setText(user.GetPhone().c_str());
			}
			if (childName == QString("productForm"))
			{
				productEdit->setText(QString::number(ID));
			}
			BusinessLayer::Product product;
			if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
			{
				productNamePh->setText(product.GetName().c_str());
				pricePh->setText(QString::number(product.GetPrice(),'f', 2));
			}
		}
	}
}


void CreateEmpPrdDlg::SetEmployeeProductParams(int eEmployeeID, int eProductID, int id)
{
	employeeProduct->SetEmployeeID(eEmployeeID);
	employeeProduct->SetProductID(eProductID);
	employeeProduct->SetID(id);
}

void CreateEmpPrdDlg::FillEditElements(int eEmployeeID, int eProductID)
{
	userEdit->setText(QString::number(eEmployeeID));
	productEdit->setText(QString::number(eProductID));
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), eEmployeeID, errorMessage))
	{
		namePh->setText(user.GetName().c_str());
		surnamePh->setText(user.GetSurname().c_str());
		phonePh->setText(user.GetPhone().c_str());
	}
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), eProductID, errorMessage))
	{
		productNamePh->setText(product.GetName().c_str());
		pricePh->setText(QString::number(product.GetPrice(),'f',2));
	}
}

bool CreateEmpPrdDlg::FillDlgElements(QTableView* aTable)
{
	QModelIndex mIndex = aTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetEmployeeProductParams(aTable->model()->data(aTable->model()->index(mIndex.row(), 6)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 7)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(aTable->model()->data(aTable->model()->index(mIndex.row(), 6)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 7)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateEmpPrdDlg::CreateEmployeeProduct()
{
	errorMessage.clear();
	if (0 != userEdit->text().toInt() && 0 != productEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetEmployeeProductParams(userEdit->text().toInt(), productEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateEmployeeProductRelation(employeeProduct, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					BusinessLayer::Product *product = new BusinessLayer::Product();
					if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeProduct->GetEmployeeID(), errorMessage)
						|| !product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeProduct->GetProductID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete product;
						delete employee;
						return;
					}
					QList<QStandardItem*> employeeProductItem;
					employeeProductItem << new QStandardItem(QString::number(employeeProduct->GetID()))
						<< new QStandardItem(employee->GetName().c_str())
						<< new QStandardItem(employee->GetSurname().c_str())
						<< new QStandardItem(employee->GetPhone().c_str())
						<< new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(product->GetPrice(),'f',2))
						<< new QStandardItem(QString::number(employeeProduct->GetEmployeeID()))
						<< new QStandardItem(QString::number(employeeProduct->GetProductID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(employeeProductItem);

					delete product;
					delete employee;
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
			QString(tr("Please fill product, employee fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateEmpPrdDlg::EditEmployeeProduct()
{
	errorMessage.clear();
	if (0 != userEdit->text().toInt() && 0 != productEdit->text().toInt())
	{
		if (employeeProduct->GetEmployeeID() != userEdit->text().toInt() || employeeProduct->GetProductID() != productEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetEmployeeProductParams(userEdit->text().toInt(), productEdit->text().toInt(), employeeProduct->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateEmployeeProductRelation(employeeProduct, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Employee *employee = new BusinessLayer::Employee();
						BusinessLayer::Product *product = new BusinessLayer::Product();
						if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeProduct->GetEmployeeID(), errorMessage)
							|| !product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeProduct->GetProductID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete product;
							delete employee;
							return;
						}

						itemModel->item(mIndex.row(), 1)->setText(employee->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(employee->GetSurname().c_str());
						itemModel->item(mIndex.row(), 3)->setText(employee->GetPhone().c_str());
						itemModel->item(mIndex.row(), 4)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(QString::number(product->GetPrice(),'f',2));
						itemModel->item(mIndex.row(), 6)->setText(QString::number(employeeProduct->GetEmployeeID()));
						itemModel->item(mIndex.row(), 7)->setText(QString::number(employeeProduct->GetProductID()));;
						emit itemModel->dataChanged(mIndex, mIndex);
						delete employee;
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
			QString(tr("Please enter employee and product item!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateEmpPrdDlg::Close()
{
	this->parentWidget()->close();
}

void CreateEmpPrdDlg::OpenEmpDlg()
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

	BusinessLayer::Role *role = new BusinessLayer::Role();
	role->SetName("EXPEDITOR");
	std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
	std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);

	if (roleVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not define the role for this employee!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	BusinessLayer::Employee *employee = new BusinessLayer::Employee();
	employee->SetRoleID(roleVector.at(0).GetID());
	std::string employeeFilter = dialogBL->GenerateFilter<BusinessLayer::Employee>(employee);
	std::vector<BusinessLayer::EmployeeView> employeeVector = dialogBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, employeeFilter);
	if (employeeVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not find employee with \"expeditor\" role!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	dForm->FillTable<BusinessLayer::EmployeeView>(errorMessage, employeeFilter);
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

void CreateEmpPrdDlg::OpenProdDlg()
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