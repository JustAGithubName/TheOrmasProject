#include "stdafx.h"
#include "CreateStockLmDlg.h"
#include "DataForm.h"

CreateStockLimitDlg::CreateStockLimitDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	productEdit->setValidator(vInt);
	stockEdit->setValidator(vInt);
	minValueEdit->setValidator(vDouble);
	minValueEdit->setMaxLength(20);
	maxValueEdit->setValidator(vDouble);
	maxValueEdit->setMaxLength(17);
	productBtn->hide();
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(addBtn, &QPushButton::released, this, &CreateStockLimitDlg::EditStockLimit);
	}
	else
	{
		productEdit->setText("0");
		minValueEdit->setText("0");
		maxValueEdit->setText("0");
		stockEdit->setText("0");
		QObject::connect(addBtn, &QPushButton::released, this, &CreateStockLimitDlg::AddStockLimit);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateStockLimitDlg::Close);
	QObject::connect(productBtn, &QPushButton::released, this, &CreateStockLimitDlg::OpenProdDlg);
	QObject::connect(stockBtn, &QPushButton::released, this, &CreateStockLimitDlg::OpenStockDlg);
	QObject::connect(minValueEdit, &QLineEdit::textChanged, this, &CreateStockLimitDlg::TextEditChanged);
	QObject::connect(maxValueEdit, &QLineEdit::textChanged, this, &CreateStockLimitDlg::TextEditChanged);
}

CreateStockLimitDlg::~CreateStockLimitDlg()
{
	delete vDouble;
	delete vInt;
}

void CreateStockLimitDlg::SetID(int ID, QString childName)
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
			if (childName == QString("stockForm"))
			{
				stockEdit->setText(QString::number(ID));
				BusinessLayer::Stock stock;
				BusinessLayer::Product product;
				if (stock.GetStockByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					BusinessLayer::Warehouse warehouse;
					if (warehouse.GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stock.GetWarehouseID(), errorMessage))
					{
						warehousePh->setText(warehouse.GetName().c_str());
						if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stock.GetProductID(), errorMessage))
						{
							productEdit->setText(QString::number(stock.GetProductID()));
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
	}
}

void CreateStockLimitDlg::SetStockLimitParams(int sStockID, int sProductID, double sMinValue, double sMaxValue, int id)
{
	stockLimit->SetStockID(sStockID);
	stockLimit->SetProductID(sProductID);
	stockLimit->SetMinValue(sMinValue);
	stockLimit->SetMaxValue(sMaxValue);
	stockLimit->SetID(id);
}

void CreateStockLimitDlg::FillEditElements(int sStockID, int sProductID, double sMinValue, double sMaxValue)
{
	productEdit->setText(QString::number(sProductID));
	minValueEdit->setText(QString::number(sMinValue, 'f', 3));
	maxValueEdit->setText(QString::number(sMaxValue, 'f', 3));
	stockEdit->setText(QString::number(sStockID));
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), sProductID, errorMessage))
	{
		prodNamePh->setText(product.GetName().c_str());
		volumePh->setText(QString::number(product.GetVolume()));
		BusinessLayer::Measure measure;
		if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			measurePh->setText(measure.GetName().c_str());
		}
	}
	BusinessLayer::Stock stock;
	if (stock.GetStockByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), sStockID, errorMessage))
	{
		BusinessLayer::Warehouse warehouse;
		if (warehouse.GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stock.GetWarehouseID(), errorMessage))
		{
			warehousePh->setText(warehouse.GetName().c_str());
			if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stock.GetProductID(), errorMessage))
			{
				productEdit->setText(QString::number(stock.GetProductID()));
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

bool CreateStockLimitDlg::FillDlgElements(QTableView* oTable)
{
	QModelIndex mIndex = oTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetStockLimitParams(oTable->model()->data(oTable->model()->index(mIndex.row(), 5)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 6)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 3)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 4)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(oTable->model()->data(oTable->model()->index(mIndex.row(), 5)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 6)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 3)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 4)).toDouble());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateStockLimitDlg::AddStockLimit()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() || 0 != stockEdit->text().toInt())
	{
		if (minValueEdit->text().toDouble() > maxValueEdit->text().toDouble())
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Minimum value must be litte than maximum value!")),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		DataForm *parentDataForm = (DataForm*)parentForm;
		BusinessLayer::Stock *stock = new BusinessLayer::Stock();
		BusinessLayer::Warehouse *warehouse = new BusinessLayer::Warehouse();
		BusinessLayer::Product *product = new BusinessLayer::Product();
		if (!stock->GetStockByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stockEdit->text().toInt(), errorMessage))
		{
			if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stock->GetProductID(), errorMessage) &&
				!warehouse->GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stock->GetProductID(), errorMessage))
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage.clear();
			delete stock;
			delete warehouse;
			delete product;
			return;
		}
		
		SetStockLimitParams(stock->GetID(), stock->GetProductID(), minValueEdit->text().toDouble(), maxValueEdit->text().toDouble());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateStockLimit(stockLimit, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> productListItem;
					productListItem << new QStandardItem(QString::number(stockLimit->GetID()))
						<< new QStandardItem(warehouse->GetName().c_str())
						<< new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(stockLimit->GetMinValue(), 'f', 3))
						<< new QStandardItem(QString::number(stockLimit->GetMaxValue(), 'f', 3))
						<< new QStandardItem(QString::number(stockLimit->GetStockID()))
						<< new QStandardItem(QString::number(stockLimit->GetProductID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(productListItem);
				}
			}
			delete stock;
			delete product;
			delete warehouse;
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
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("This stock limit is not valid! Please delete it!")),
				QString(tr("Ok")));
			dialogBL->CancelTransaction(errorMessage);
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
		dialogBL->CancelTransaction(errorMessage);
	}
	errorMessage.clear();
}

void CreateStockLimitDlg::EditStockLimit()
{
	errorMessage.clear();
	if (0 != stockEdit->text().toInt() || 0 != stockEdit->text().toDouble())
	{
		if (stockEdit->text().toInt() != stockLimit->GetProductID() || minValueEdit->text().toDouble() != stockLimit->GetMinValue()
			|| maxValueEdit->text().toDouble() != stockLimit->GetMinValue())
		{
			if (minValueEdit->text().toDouble() > maxValueEdit->text().toDouble())
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr("Minimum value must be litte than maximum value!")),
					QString(tr("Ok")));
				errorMessage.clear();
				return;
			}

			BusinessLayer::Stock *stock = new BusinessLayer::Stock();
			BusinessLayer::Warehouse *warehouse = new BusinessLayer::Warehouse();
			BusinessLayer::Product *product = new BusinessLayer::Product();
			if (!stock->GetStockByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stockEdit->text().toInt(), errorMessage))
			{
				if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stock->GetProductID(), errorMessage) &&
					!warehouse->GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stock->GetProductID(), errorMessage))
					QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				delete stock;
				delete warehouse;
				delete product;
				return;
			}

			DataForm *parentDataForm = (DataForm*)parentForm;
			SetStockLimitParams(stockEdit->text().toInt(), productEdit->text().toInt(), minValueEdit->text().toDouble(), maxValueEdit->text().toDouble(), stockLimit->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateStockLimit(stockLimit, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(warehouse->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(stockLimit->GetMinValue(), 'f', 3));
						itemModel->item(mIndex.row(), 4)->setText(QString::number(stockLimit->GetMaxValue(), 'f', 3));
						itemModel->item(mIndex.row(), 5)->setText(QString::number(stock->GetID()));
						itemModel->item(mIndex.row(), 6)->setText(QString::number(product->GetID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete product;
						delete warehouse;
						delete stock;
						if (!dialogBL->CommitTransaction(errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
						}
					}
				}

				Close();
			}
			else
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				dialogBL->CancelTransaction(errorMessage);
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
		dialogBL->CancelTransaction(errorMessage);
	}
	errorMessage.clear();
}

void CreateStockLimitDlg::Close()
{
	this->parentWidget()->close();
}

void CreateStockLimitDlg::OpenStockDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Stock"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::StockView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("stockForm");
		dForm->QtConnect<BusinessLayer::StockView>();
		QMdiSubWindow *stockWindow = new QMdiSubWindow;
		stockWindow->setWidget(dForm);
		stockWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(stockWindow);
		stockWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->SetDecoration();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All stocks are shown");
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

void CreateStockLimitDlg::OpenProdDlg()
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



void CreateStockLimitDlg::TextEditChanged()
{
	if (minValueEdit->text().contains(","))
	{
		minValueEdit->setText(minValueEdit->text().replace(",", "."));
	}
	if (minValueEdit->text().contains(".."))
	{
		minValueEdit->setText(minValueEdit->text().replace("..", "."));
	}
	if (maxValueEdit->text().contains(","))
	{
		maxValueEdit->setText(maxValueEdit->text().replace(",", "."));
	}
	if (maxValueEdit->text().contains(".."))
	{
		maxValueEdit->setText(maxValueEdit->text().replace("..", "."));
	}
}
