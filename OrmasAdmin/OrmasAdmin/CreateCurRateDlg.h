#ifndef CREATECURRATEDLG_H
#define CREATECURRATEDLG_H
#include "ui_CreateCurRateDlg.h"
#include "OrmasBL.h"
#include <QStandardItemModel>

class CreateCurRateDlg : public QDialog, public Ui::CreateCurrencyRate
{
	Q_OBJECT
public:
	CreateCurRateDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateCurRateDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreateCurrencyRate();
	void EditCurrencyRate();
	void DeleteCurrencyRate(){};
	void Close();
	void TextEditChanged();
private:
	BusinessLayer::CurrencyRate *currencyRate = new BusinessLayer::CurrencyRate();
	void SetCurrencyRateParams(int, double, int, double, QString, int = 0);
	void FillEditElements(int, double, int, double, QString);
	QDoubleValidator *vDouble = nullptr;
	QWidget* parentForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
	void InitComboBox();
};
#endif //CREATECURDLG_H