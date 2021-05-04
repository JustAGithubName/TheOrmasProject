#include "stdafx.h"
#include "GenerateFxAstRepDlg.h"
#include "MainForm.h"
#include "DocForm.h"
#include "DataForm.h"

GenerateFxAstRep::GenerateFxAstRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	mainForm = (MainForm *)this->parent();

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateFxAstRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateFxAstRep::Close);
	QObject::connect(allCbx, &QCheckBox::released, this, &GenerateFxAstRep::CheckBoxChanged);
	InitComboBox();
	fixedCbx->setDisabled(true);
}

GenerateFxAstRep::~GenerateFxAstRep()
{
	
}


void GenerateFxAstRep::Generate()
{
	DocForm *docForm = new DocForm(dialogBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print fixed assets report"));
	QMdiSubWindow *generateProfRepWindow = new QMdiSubWindow;
	generateProfRepWindow->setWidget(docForm);
	generateProfRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	generateProfRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	mainForm->mdiArea->addSubWindow(generateProfRepWindow);

	//read template
	QFile file;
	file.setFileName(":/docs/fixed_assets_turnover.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find sales report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	QString documentBody = "";
	QString tableBody = "";

	BusinessLayer::FixedAssetsView fxItem;
	std::vector<BusinessLayer::FixedAssetsView> fxVec;
	std::string filterFx;

	double amortizeSum = 0;
	double primeSum = 0;
	if (allCbx->isChecked())
	{
		if (!accMap.empty())
		{
			for each (auto item in accMap)
			{
				fxItem.Clear();
				fxVec.clear();
				filterFx.clear();
				fxItem.SetPrimaryParentAccID(item.first);
				filterFx = fxItem.GenerateFilter(dialogBL->GetOrmasDal());
				fxVec = dialogBL->GetAllDataForClass<BusinessLayer::FixedAssetsView>(errorMessage, filterFx);

				tableBody += QString::fromWCharArray(L"ОС: ");
				tableBody += item.second.c_str();
				tableBody += "<br/>";

				tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"ID") + "</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование ОС") + "</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Подразделение") + "</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Балансова стоимость") + "</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Начисленная износ") + "</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Остаточная стоимость") + "</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Амартизация(%, год)") + "</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Срок полезного использования, мес.") + "</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Инвентарный номер") + "</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Статус") + "</b></th>";
				
				for each (auto fxItem in fxVec)
				{
					tableBody += "<tr>";
					tableBody += "<td>" + QString::number(fxItem.GetID()) + "</td>";
					tableBody += "<td>" + QString(fxItem.GetName().c_str()) + "</td>";
					tableBody += "<td>" + QString(fxItem.GetDivisionName().c_str()) + "</td>";
					tableBody += "<td>" + QString::number(fxItem.GetPrimaryCost(), 'f', 3) + "</td>";
					tableBody += "<td>" + QString::number(fxItem.GetAmortizeValue()*(-1), 'f', 3) + "</td>";
					tableBody += "<td>" + QString::number(fxItem.GetPrimaryCost() + fxItem.GetAmortizeValue(), 'f', 3) + "</td>";
					tableBody += "<td>" + QString::number(12 * 100 / fxItem.GetServiceLife()) + "</td>";
					tableBody += "<td>" + QString::number(fxItem.GetServiceLife()) + "</td>";
					tableBody += "<td>" + QString(fxItem.GetInventoryNumber().c_str()) + "</td>";
					tableBody += "<td>" + QString(fxItem.GetStatusName().c_str()) + "</td>";
					tableBody += "</tr>";
					amortizeSum += fxItem.GetAmortizeValue();
					primeSum += fxItem.GetPrimaryCost();
				}
				tableBody += "<tr>";
				tableBody += "<td>" + QString::fromWCharArray(L"Суммарно: ") +"</td>";
				tableBody += "<td></td>";
				tableBody += "<td></td>";
				tableBody += "<td>" + QString::number(primeSum, 'f', 3) + "</td>";
				tableBody += "<td>" + QString::number(amortizeSum*(-1), 'f', 3) + "</td>";
				tableBody += "<td>""</td>";
				tableBody += "<td></td>";
				tableBody += "<td></td>";
				tableBody += "<td></td>";
				tableBody += "<td></td>";
				tableBody += "</tr>";
				tableBody += "</table><br/><br/>";
				amortizeSum =0;
				primeSum =0;
				reportText.replace(QString("FixedAssetsInfoPh"), "", Qt::CaseInsensitive);
			}
		}	
	}
	else
	{
		if (fixedCbx->currentData().toInt() != 0)
		{
			fxItem.Clear();
			fxVec.clear();
			filterFx.clear();
			fxItem.SetPrimaryParentAccID(fixedCbx->currentData().toInt());
			filterFx = fxItem.GenerateFilter(dialogBL->GetOrmasDal());
			fxVec = dialogBL->GetAllDataForClass<BusinessLayer::FixedAssetsView>(errorMessage, filterFx);

			tableBody += QString::fromWCharArray(L"ОС: ");
			tableBody += fixedCbx->currentText();
			tableBody += "<br/>";


			reportText.replace(QString("FixedAssetsInfoPh"), fixedCbx->currentText(), Qt::CaseInsensitive);

			tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"ID") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование ОС") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Подразделение") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Балансова стоимость") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Начисленная износ") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Остаточная стоимость") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Амартизация(%, год)") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Срок полезного использования, мес.") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Инвентарный номер") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Статус") + "</b></th>";

			for each (auto fxItem in fxVec)
			{
				tableBody += "<tr>";
				tableBody += "<td>" + QString::number(fxItem.GetID()) + "</td>";
				tableBody += "<td>" + QString(fxItem.GetName().c_str()) + "</td>";
				tableBody += "<td>" + QString(fxItem.GetDivisionName().c_str()) + "</td>";
				tableBody += "<td>" + QString::number(fxItem.GetPrimaryCost(), 'f', 3) + "</td>";
				tableBody += "<td>" + QString::number(fxItem.GetAmortizeValue()*(-1), 'f', 3) + "</td>";
				tableBody += "<td>" + QString::number(fxItem.GetPrimaryCost() + fxItem.GetAmortizeValue(), 'f', 3) + "</td>";
				tableBody += "<td>" + QString::number(12 * 100 / fxItem.GetServiceLife()) + "</td>";
				tableBody += "<td>" + QString::number(fxItem.GetServiceLife()) + "</td>";
				tableBody += "<td>" + QString(fxItem.GetInventoryNumber().c_str()) + "</td>";
				tableBody += "<td>" + QString(fxItem.GetStatusName().c_str()) + "</td>";
				tableBody += "</tr>";
				amortizeSum += fxItem.GetAmortizeValue();
				primeSum += fxItem.GetPrimaryCost();
			}
			tableBody += "<tr>";
			tableBody += "<td>" + QString::fromWCharArray(L"Суммарно: ") +"</td>";
			tableBody += "<td></td>";
			tableBody += "<td></td>";
			tableBody += "<td>" + QString::number(primeSum, 'f', 3) + "</td>";
			tableBody += "<td>" + QString::number(amortizeSum*(-1), 'f', 3) + "</td>";
			tableBody += "<td>""</td>";
			tableBody += "<td></td>";
			tableBody += "<td></td>";
			tableBody += "<td></td>";
			tableBody += "<td></td>";
			tableBody += "</tr>";
			tableBody += "</table><br/><br/>";
			tableBody += "</table><br/><br/>";
		}
	}

	documentBody += tableBody;

	QDate currentDate = QDate::currentDate();
	reportText.replace(QString("fromDatePh"), currentDate.toString("dd.MM.yyyy"), Qt::CaseInsensitive);
	reportText.replace(QString("TablePh"), documentBody, Qt::CaseInsensitive);
	reportText.replace(QString("ReportDatePh"), currentDate.toString("dd.MM.yyyy"), Qt::CaseInsensitive);
	reportText.replace(QString("UserNamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
	reportText.replace(QString("UserSurnamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();

	Close();
}

void GenerateFxAstRep::Close()
{
	this->parentWidget()->close();
}

void GenerateFxAstRep::InitComboBox()
{
	BusinessLayer::Account account11010;
	BusinessLayer::Account account11020;
	BusinessLayer::Account account11030;
	BusinessLayer::Account account11040;
	BusinessLayer::Account account11050;
	BusinessLayer::Account account11060;
	BusinessLayer::Account account11070;
	BusinessLayer::Account account11080;
	BusinessLayer::Account account11090;

	BusinessLayer::ChartOfAccounts chao;

	if (!account11010.GetAccountByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11010", errorMessage))
		return;
	if (!account11020.GetAccountByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11020", errorMessage))
		return;
	if (!account11030.GetAccountByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11030", errorMessage))
		return;
	if (!account11040.GetAccountByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11040", errorMessage))
		return;
	if (!account11050.GetAccountByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11050", errorMessage))
		return;
	if (!account11060.GetAccountByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11060", errorMessage))
		return;
	if (!account11070.GetAccountByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11070", errorMessage))
		return;
	if (!account11080.GetAccountByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11080", errorMessage))
		return;
	if (!account11090.GetAccountByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11090", errorMessage))
		return;

	chao.Clear();
	chao.GetChartOfAccountsByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11010", errorMessage);
	fixedCbx->addItem(chao.GetName().c_str(), QVariant(account11010.GetID()));
	accMap.insert(std::make_pair(account11010.GetID(), chao.GetName().c_str()));
	chao.Clear();
	chao.GetChartOfAccountsByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11020", errorMessage);
	fixedCbx->addItem(chao.GetName().c_str(), QVariant(account11020.GetID()));
	accMap.insert(std::make_pair(account11020.GetID(), chao.GetName().c_str()));
	chao.Clear();
	chao.GetChartOfAccountsByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11030", errorMessage);
	fixedCbx->addItem(chao.GetName().c_str(), QVariant(account11030.GetID()));
	accMap.insert(std::make_pair(account11030.GetID(), chao.GetName().c_str()));
	chao.Clear();
	chao.GetChartOfAccountsByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11040", errorMessage);
	fixedCbx->addItem(chao.GetName().c_str(), QVariant(account11040.GetID()));
	accMap.insert(std::make_pair(account11040.GetID(), chao.GetName().c_str()));
	chao.Clear();
	chao.GetChartOfAccountsByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11050", errorMessage);
	fixedCbx->addItem(chao.GetName().c_str(), QVariant(account11050.GetID()));
	accMap.insert(std::make_pair(account11050.GetID(), chao.GetName().c_str()));
	chao.Clear();
	chao.GetChartOfAccountsByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11060", errorMessage);
	fixedCbx->addItem(chao.GetName().c_str(), QVariant(account11060.GetID()));
	accMap.insert(std::make_pair(account11060.GetID(), chao.GetName().c_str()));
	chao.Clear();
	chao.GetChartOfAccountsByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11070", errorMessage);
	fixedCbx->addItem(chao.GetName().c_str(), QVariant(account11070.GetID()));
	accMap.insert(std::make_pair(account11070.GetID(), chao.GetName().c_str()));
	chao.Clear();
	chao.GetChartOfAccountsByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11080", errorMessage);
	fixedCbx->addItem(chao.GetName().c_str(), QVariant(account11080.GetID()));
	accMap.insert(std::make_pair(account11080.GetID(), chao.GetName().c_str()));
	chao.Clear();
	chao.GetChartOfAccountsByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "11090", errorMessage);
	fixedCbx->addItem(chao.GetName().c_str(), QVariant(account11090.GetID()));
	accMap.insert(std::make_pair(account11090.GetID(), chao.GetName().c_str()));
}

void GenerateFxAstRep::CheckBoxChanged()
{
	if (allCbx->isChecked())
	{
		fixedCbx->setDisabled(true);

	}
	else
	{
		fixedCbx->setEnabled(true);
	}
}