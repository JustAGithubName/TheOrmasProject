#ifndef DATAFORM_H
#define DATAFORM_H

#include "ui_DataForm.h"
#include "OrmasBL.h"
#include <QStandardItem>
#include <QStringList>
#include <QDialog>


class DataForm : public QWidget, public Ui::DataForm
{
	Q_OBJECT
public:
	DataForm(BusinessLayer::OrmasBL *ormasBL, QWidget *parent = 0);
	~DataForm(){};
	
	template<class T>
	void FillTable(std::string& errorMessage, std::string filter = "")
	{
		QStringList header = GetTableHeader<T>();
		//QStandardItem *item;
		SetColumnFilter(header);
		SetTypeFilter();
		QStandardItemModel *itemModel = new QStandardItemModel(this);
		itemModel->setHorizontalHeaderLabels(header);
		tableView->setModel(itemModel);
		std::vector<T> dataVector = dataFormBL->GetAllDataForClass<T>(errorMessage, filter);
		if (!dataVector.empty())
		{
			for (unsigned int i = 0; i < dataVector.size();i++)
			{
				itemModel->appendRow(GetDataFromClass<T>(dataVector[i]));
			}
		}
	}

	template<class T>
	void QtConnect();

	template<class T>
	QStringList GetTableHeader();

	void SetColumnFilter(QStringList);
	void SetTypeFilter();
	

	template<class T>
	QList<QStandardItem*> GetDataFromClass(T& data);

	QWidget* GetParent();
	void SetDecoration();
private:
	void DisableButtons();
	void EnableButtons();
private slots:
	void OpenList(int, int);
	void Refresh();

	void CrtAccDlg();
	void UdpAccDlg();
	void DelAccDlg();
	bool SearchInAccForm(std::string searchFilter);

	void CrtAcctblDlg();
	void UdpAcctblDlg();
	void DelAcctblDlg();
	bool SearchInAcctblForm(std::string searchFilter);

	void CrtAccblDocDlg();
	void UdpAccblDocDlg();
	void DelAccblDocDlg();
	void ViewAccblDocDlg();
	bool SearchInAccblDocForm(std::string searchFilter);
	
	void CrtAccTpDlg();
	void UdpAccTpDlg();
	void DelAccTpDlg();
	bool SearchInAccTpForm(std::string searchFilter);

	void CrtAcsDlg();
	void UdpAcsDlg();
	void DelAcsDlg();
	bool SearchInAccessForm(std::string searchFilter);

	void CrtAcsItemDlg();
	void UdpAcsItemDlg();
	void DelAcsItemDlg();
	bool SearchInAcsItemForm(std::string searchFilter);

	void CrtAmGrDlg();
	void UdpAmGrDlg();
	void DelAmGrDlg();
	bool SearchInAmGrForm(std::string searchFilter);

	void CrtAmTypeDlg();
	void UdpAmTypeDlg();
	void DelAmTypeDlg();
	bool SearchInAmTypeForm(std::string searchFilter);

	void CrtBlcDlg();
	void UdpBlcDlg();
	void DelBlcDlg();
	bool SearchInBlcForm(std::string searchFilter);

	void CrtBrhDlg();
	void UdpBrhDlg();
	void DelBrhDlg();
	bool SearchInBrhForm(std::string searchFilter);

	void CrtBrSAccDlg();
	void UdpBrSAccDlg();
	void DelBrSAccDlg();
	bool SearchInBrSAccForm(std::string searchFilter);

	void CrtBrwDlg();
	void UdpBrwDlg();
	void DelBrwDlg();
	bool SearchInBrwForm(std::string searchFilter);
	
	void CrtCbxDlg();
	void UdpCbxDlg();
	void DelCbxDlg();
	bool SearchInCbxForm(std::string searchFilter);

	void CrtCASHERDlg();
	void UdpCASHERDlg();
	void DelCASHERDlg();
	bool SearchInCASHERForm(std::string searchFilter);

	void CrtCltDlg();
	void UdpCltDlg();
	void DelCltDlg();
	bool SearchInCltForm(std::string searchFilter);

	void CrtCmpDlg();
	void UdpCmpDlg();
	void DelCmpDlg();
	bool SearchInCmpForm(std::string searchFilter);

	void CrtCARDlg();
	void UdpCARDlg();
	void DelCARDlg();
	bool SearchInCARForm(std::string searchFilter);

	void CrtCERDlg();
	void UdpCERDlg();
	void DelCERDlg();
	bool SearchInCERForm(std::string searchFilter);

	void CrtCOADlg();
	void UdpCOADlg();
	void DelCOADlg();
	bool SearchInCOADForm(std::string searchFilter);
	
	void CrtConPDlg();
	void UdpConPDlg();
	void DelConPDlg();
	bool SearchInConPForm(std::string searchFilter);
	void ViewConPDlg();

	void CrtConPListDlg();
	void UdpConPListDlg();
	void DelConPListDlg();

	void CrtConOthStDlg();
	void UdpConOthStDlg();
	void DelConOthStDlg();
	bool SearchInConOthForm(std::string searchFilter);
	void ViewConOthStDlg();

	void CrtConOthStListDlg();
	void UdpConOthStListDlg();
	void DelConOthStListDlg();

	void CrtConRDlg();
	void UdpConRDlg();
	void DelConRDlg();
	bool SearchInConRForm(std::string searchFilter);
	void ViewConRDlg();

	void CrtConRListDlg();
	void UdpConRListDlg();
	void DelConRListDlg();

	void CrtCurDlg();
	void UdpCurDlg();
	void DelCurDlg();
	bool SearchInCurForm(std::string searchFilter);

	void CrtCurRateDlg();
	void UdpCurRateDlg();
	void DelCurRateDlg();
	bool SearchInCurRateForm(std::string searchFilter);

	void CrtDivDlg();
	void UdpDivDlg();
	void DelDivDlg();
	bool SearchInDivForm(std::string searchFilter);

	void CrtDivAccDlg();
	void UdpDivAccDlg();
	void DelDivAccDlg();
	bool SearchInDivAccForm(std::string searchFilter);

	void CrtEmpDlg();
	void UdpEmpDlg();
	void DelEmpDlg();
	bool SearchInEmpForm(std::string searchFilter);

	void CrtEmpPrdDlg();
	void UdpEmpPrdDlg();
	void DelEmpPrdDlg();
	bool SearchInEmpPrdForm(std::string searchFilter);

	void CrtEtrDlg();
	void UdpEtrDlg();
	void DelEtrDlg();
	bool SearchInEtrForm(std::string searchFilter);

	void CrtEtrRtDlg();
	void UdpEtrRtDlg();
	void DelEtrRtDlg();
	bool SearchInEtrRtForm(std::string searchFilter);

	void CrtFxdAstDlg();
	void UdpFxdAstDlg();
	void DelFxdAstDlg();
	bool SearchInFxdAstForm(std::string searchFilter);
	void ViewFxdAstDlg();

	void CrtFxdAstOperDlg();
	void UdpFxdAstOperDlg();
	void DelFxdAstOperDlg(); 
	bool SearchInAstOperForm(std::string searchFilter);

	void CrtInveDlg();
	void UdpInveDlg();
	void DelInveDlg();
	bool SearchInInveForm(std::string searchFilter);

	void CrtInvDlg();
	void UdpInvDlg();
	void DelInvDlg();
	bool SearchInInvForm(std::string searchFilter);
	void ViewInvDlg();

	void CrtInvListDlg();
	void UdpInvListDlg();
	void DelInvListDlg();


	void CrtGroupDlg();
	void UdpGroupDlg();
	void DelGroupDlg();
	bool SearchInGroupForm(std::string searchFilter);

	void CrtJbpDlg();
	void UdpJbpDlg();
	void DelJbpDlg();
	bool SearchInJbpForm(std::string searchFilter);

	void CrtJbsDlg();
	void UdpJbsDlg();
	void DelJbsDlg();
	bool SearchInJbsForm(std::string searchFilter);

	void CrtLowValStockDlg();
	void UdpLowValStockDlg();
	void DelLowValStockDlg();
	bool SearchInLowValStockForm(std::string searchFilter);

	void CrtLcnDlg();
	void UdpLcnDlg();
	void DelLcnDlg();
	bool SearchInLcnForm(std::string searchFilter);

	void CrtMsrDlg();
	void UdpMsrDlg();
	void DelMsrDlg();
	bool SearchInMsrForm(std::string searchFilter);

	void CrtMcurDlg();
	void UdpMcurDlg();
	void DelMcurDlg();
	bool SearchInMcurForm(std::string searchFilter);

	void CrtNetCDlg();
	void UdpNetCDlg();
	void DelNetCDlg();
	bool SearchInNetCForm(std::string searchFilter);

	void CrtNetCostCoeffDlg();
	void UdpNetCostCoeffDlg();
	void DelNetCostCoeffDlg();
	bool SearchInNetCCoeffForm(std::string searchFilter);

	void CrtOrdDlg();
	void UdpOrdDlg();
	void DelOrdDlg();
	void ViewOrdDlg();
	bool SearchInOrderForm(std::string searchFilter);

	void CrtOrdListDlg();
	void UdpOrdListDlg();
	void DelOrdListDlg();

	void CrtOrdRDlg();
	void UdpOrdRDlg();
	void DelOrdRDlg();
	void ViewOrdRDlg();
	bool SearchInOrdRForm(std::string searchFilter);

	void CrtOrdRListDlg();
	void UdpOrdRListDlg();
	void DelOrdRListDlg();

	void CrtOthStDlg();
	void UdpOthStDlg();
	void DelOthStDlg();
	bool SearchInOthStForm(std::string searchFilter);

	void CrtOthStTypeDlg();
	void UdpOthStTypeDlg();
	void DelOthStTypeDlg();
	bool SearchInOthStTypeForm(std::string searchFilter){ return false; };

	void CrtPcrDlg();
	void UdpPcrDlg();
	void DelPcrDlg();
	bool SearchInPcrForm(std::string searchFilter);

	void CrtPrExDlg();
	void UdpPrExDlg();
	void DelPrExDlg();
	bool SearchInPrExForm(std::string searchFilter);

	void CrtPhotoDlg();
	void UdpPhotoDlg();
	void DelPhotoDlg();
	bool SearchInPhotoForm(std::string searchFilter){ return false; };

	void CrtPmtDlg();
	void UdpPmtDlg();
	void DelPmtDlg();
	void ViewPmtDlg();
	bool SearchInPmtForm(std::string searchFilter);

	void CrtPosDlg();
	void UdpPosDlg();
	void DelPosDlg();
	bool SearchInPosForm(std::string searchFilter);

	void CrtPrcDlg();
	void UdpPrcDlg();
	void DelPrcDlg();
	bool SearchInPrcForm(std::string searchFilter);

	void CrtProdTpDlg();
	void UdpProdTpDlg();
	void DelProdTpDlg();
	bool SearchInProdTpForm(std::string searchFilter);

	void CrtPrdBrnDlg();
	void UdpPrdBrnDlg();
	void DelPrdBrnDlg();
	bool SearchInPrdBrnForm(std::string searchFilter);

	void CrtProdDlg();
	void UdpProdDlg();
	void DelProdDlg();
	bool SearchInProdForm(std::string searchFilter);

	void CrtProdnDlg();
	void UdpProdnDlg();
	void DelProdnDlg();
	void ViewProdnDlg();
	bool SearchInProdnForm(std::string searchFilter);

	void CrtProdConRDlg();
	void UdpProdConRDlg();
	void DelProdConRDlg();
	void ViewProdConRDlg();
	bool SearchInProdConRForm(std::string searchFilter);

	void CrtProdConRListDlg();
	void UdpProdConRListDlg();
	void DelProdConRListDlg();

	void CrtProdnListDlg();
	void UdpProdnListDlg();
	void DelProdnListDlg();

	void CrtPPlanDlg();
	void UdpPPlanDlg();
	void DelPPlanDlg();
	void ViewPPlanDlg(){};
	bool SearchInPPlanConRForm(std::string searchFilter);

	void CrtPPlanListDlg();
	void UdpPPlanListDlg();
	void DelPPlanListDlg();

	void CrtPspDlg();
	void UdpPspDlg();
	void DelPspDlg();
	bool SearchInPspForm(std::string searchFilter);

	void CrtPurDlg();
	void UdpPurDlg();
	void DelPurDlg();
	bool SearchInPurForm(std::string searchFilter);

	void CrtRelDlg();
	void UdpRelDlg();
	void DelRelDlg();
	bool SearchInRelForm(std::string searchFilter);

	void CrtRelTypeDlg();
	void UdpRelTypeDlg();
	void DelRelTypeDlg();
	bool SearchInRelTypeForm(std::string searchFilter);

	void CrtRoleDlg();
	void UdpRoleDlg();
	void DelRoleDlg();
	bool SearchInRoleForm(std::string searchFilter);

	void CrtRcpOthStDlg();
	void UdpRcpOthStDlg();
	void DelRcpOthStDlg();
	void ViewRcpOthStDlg();
	bool SearchInRcpOthStForm(std::string searchFilter);

	void CrtRcpOthStListDlg();
	void UdpRcpOthStListDlg();
	void DelRcpOthStListDlg();

	void CrtRcpPDlg();
	void UdpRcpPDlg();
	void DelRcpPDlg();
	void ViewRcpPDlg();
	bool SearchInRcpPForm(std::string searchFilter);

	void CrtRcpPListDlg();
	void UdpRcpPListDlg();
	void DelRcpPListDlg();

	void CrtStockTrDlg();
	void UdpStockTrDlg();
	void DelStockTrDlg();
	void ViewStockTrDlg();
	bool SearchInStockTrForm(std::string searchFilter);

	void CrtStockLmDlg();
	void UdpStockLmDlg();
	void DelStockLmDlg();
	bool SearchInStockLmForm(std::string searchFilter);

	void CrtStockTrListDlg();
	void UdpStockTrListDlg();
	void DelStockTrListDlg();

	void CrtRfdDlg();
	void UdpRfdDlg();
	void DelRfdDlg();
	bool SearchInRfdForm(std::string searchFilter);

	void CrtRtrnDlg();
	void UdpRtrnDlg();
	void DelRtrnDlg();
	void ViewRtrnDlg();
	bool SearchInRtrnForm(std::string searchFilter);

	void CrtRtrnListDlg();
	void UdpRtrnListDlg();
	void DelRtrnListDlg();

	void CrtSlrDlg();
	void UdpSlrDlg();
	void DelSlrDlg();
	bool SearchInSlrForm(std::string searchFilter);

	void CrtSlrTypeDlg();
	void UdpSlrTypeDlg();
	void DelSlrTypeDlg();
	bool SearchInSlrTypeForm(std::string searchFilter);

	void CrtStsDlg();
	void UdpStsDlg();
	void DelStsDlg();
	bool SearchInStsForm(std::string searchFilter);

	void CrtStsRuleDlg();
	void UdpStsRuleDlg();
	void DelStsRuleDlg();
	bool SearchInStsRuleForm(std::string searchFilter);

	void CrtSpecDlg();
	void UdpSpecDlg();
	void DelSpecDlg();
	void ViewSpecDlg();
	bool SearchInSpecForm(std::string searchFilter);
	
	void CrtSpecListDlg();
	void UdpSpecListDlg();
	void DelSpecListDlg();

	void CrtSplDlg();
	void UdpSplDlg();
	void DelSplDlg();
	void ViewSplDlg();
	bool SearchInSplForm(std::string searchFilter);

	void CrtSplListDlg();
	void UdpSplListDlg();
	void DelSplListDlg();

	void CrtStockDlg();
	void UdpStockDlg();
	void DelStockDlg();
	bool SearchInStockForm(std::string searchFilter);

	void CrtSAccDlg();
	void UdpSAccDlg();
	void DelSAccDlg();
	bool SearchInSAccForm(std::string searchFilter);

	void CrtSAccLmDlg();
	void UdpSAccLmDlg();
	void DelSAccLmDlg();
	bool SearchInSAccLmForm(std::string searchFilter);

	void CrtTmsDlg();
	void UdpTmsDlg();
	void DelTmsDlg();
	bool SearchInTmsForm(std::string searchFilter);

	void CrtTrsDlg();
	void UdpTrsDlg();
	void DelTrsDlg();
	void ViewTrsDlg();
	bool SearchInTrsForm(std::string searchFilter);

	void CrtTrsListDlg();
	void UdpTrsListDlg();
	void DelTrsListDlg();

	void CrtUserDlg();
	void UdpUserDlg();
	void DelUserDlg();
	bool SearchInUserForm(std::string searchFilter);

	void CrtUserGrDlg();
	void UdpUserGrDlg();
	void DelUserGrDlg();
	bool SearchInUserGrForm(std::string searchFilter);

	void CrtWrhDlg();
	void UdpWrhDlg();
	void DelWrhDlg();
	bool SearchInWrhForm(std::string searchFilter);

	void CrtWrhTpDlg();
	void UdpWrhTpDlg();
	void DelWrhTpDlg();
	bool SearchInWrhTpForm(std::string searchFilter);

	void CrtWERDlg();
	void UdpWERDlg();
	void DelWERDlg();
	bool SearchInWERForm(std::string searchFilter);

	void CrtWdwDlg();
	void UdpWdwDlg();
	void DelWdwDlg();
	void ViewWdwDlg();
	bool SearchInwWdwForm(std::string searchFilter);

	void CrtWOffDlg();
	void UdpWOffDlg();
	void DelWOffDlg();
	void ViewWOffDlg();
	bool SearchInWOffForm(std::string searchFilter);

	void CrtWOffListDlg();
	void UdpWOffListDlg();
	void DelWOffListDlg();

	void CrtWOffRDlg();
	void UdpWOffRDlg();
	void DelWOffRDlg();
	void ViewWOffRDlg();
	bool SearchInWOffRawForm(std::string searchFilter);

	void CrtWOffRListDlg();
	void UdpWOffRListDlg();
	void DelWOffRListDlg();

	void ChangeBtnState();
	void GetIDValue(QModelIndex index);
	void OnRowsNumberChanged();
	void AcsDenied();

	void Search(QString);
	void Filter();
	void ClearFilter();
	void FilterSearchInBase();
	
	
	public slots:
	void CloseDataForm();
	
	signals:
	void SendID(int ID, QString childName);
	
public:
	BusinessLayer::OrmasBL* dataFormBL;
	QWidget* parentForm;
	QDialog* parentDialog;
	BusinessLayer::User* loggedUser;
	void HideSomeRow();
	void HideAllButtons();
	bool IsClosed();
	
	unsigned int orderID = 0;
	unsigned int returnID = 0;
	unsigned int productionID = 0;
	unsigned int writeOffID = 0;
	unsigned int consumeOtherStocksID = 0;
	unsigned int consumeProductID = 0;
	unsigned int consumeRawID = 0;
	unsigned int inventorizationID = 0;
	unsigned int orderRawID = 0;
	unsigned int productionPlanID = 0;
	unsigned int pConsumeRawID = 0;
	unsigned int receiptOtherStocksID = 0;
	unsigned int receiptProductID = 0;
	unsigned int stockTransferID = 0;
	unsigned int specificationID = 0;
	unsigned int spoilageID = 0;
	unsigned int transportID = 0;
	unsigned int writeOffRawID = 0;
	unsigned int employeeID = 0;
	unsigned int stockEmployeeID = 0;
	unsigned int clientID = 0;
	unsigned int currencyID = 0;
protected:
	virtual void keyPressEvent(QKeyEvent *event);
};
#endif //DATAFORM_H