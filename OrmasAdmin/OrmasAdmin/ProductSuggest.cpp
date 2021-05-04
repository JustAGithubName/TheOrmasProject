#include "stdafx.h"
#include "ProductSuggest.h"
#include "OrmasBL.h"
#include "CreateProdConRListDlg.h"
#include "CreateConRListDlg.h"
#include "CreateOrdRListDlg.h"


PSuggestCompletion::PSuggestCompletion(QLineEdit *parent) : QObject(parent), editor(parent)
{
	if ((QDialog *)parent->parent()->objectName().compare("CreateProdConRList")==0)
		dialogParent = (CreateProdConRListDlg *)parent->parent();
	if ((QDialog *)parent->parent()->objectName().compare("CreateConRList") == 0)
		dialogParent = (CreateConRListDlg *)parent->parent();
	if ((QDialog *)parent->parent()->objectName().compare("CreateOrdRList") == 0)
		dialogParent = (CreateConRListDlg *)parent->parent();
	dataFormParent = (DataForm *) dialogParent->parentWidget();

	popup = new QTreeWidget;
	popup->setWindowFlags(Qt::Popup);
	popup->setFocusPolicy(Qt::NoFocus);
	popup->setFocusProxy(parent);
	popup->setMouseTracking(true);

	popup->setColumnCount(1);
	popup->setUniformRowHeights(true);
	popup->setRootIsDecorated(false);
	popup->setEditTriggers(QTreeWidget::NoEditTriggers);
	popup->setSelectionBehavior(QTreeWidget::SelectRows);
	popup->setFrameStyle(QFrame::Box | QFrame::Plain);
	popup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	popup->header()->hide();

	popup->installEventFilter(this);

	QObject::connect(popup, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
		SLOT(doneCompletion()));
	
	QObject::connect(this, SIGNAL(ProductIsChosen(int)), dialogParent, SLOT(SetProductData(int)));

}

PSuggestCompletion::~PSuggestCompletion()
{
	delete popup;
}

bool PSuggestCompletion::eventFilter(QObject *obj, QEvent *ev)
{
	if (obj != popup)
		return false;

	if (ev->type() == QEvent::MouseButtonPress) {
		popup->hide();
		editor->setFocus();
		return true;
	}

	if (ev->type() == QEvent::KeyPress) {
		bool consumed = false;
		int key = static_cast<QKeyEvent*>(ev)->key();
		switch (key) {
		case Qt::Key_Enter:
		case Qt::Key_Return:
			doneCompletion();
			consumed = true;
			break;

		case Qt::Key_Escape:
			editor->setFocus();
			popup->hide();
			consumed = true;
			break;

		case Qt::Key_Up:
		case Qt::Key_Down:
		case Qt::Key_Home:
		case Qt::Key_End:
		case Qt::Key_PageUp:
		case Qt::Key_PageDown:
			break;

		default:
			editor->setFocus();
			editor->event(ev);
			popup->hide();
			break;
		}

		return consumed;
	}

	return false;
}

void PSuggestCompletion::showCompletion(QMap<QString,int> &choices)
{
	if (choices.isEmpty())
		return;

	const QPalette &pal = editor->palette();
	QColor color = pal.color(QPalette::Disabled, QPalette::WindowText);

	popup->setUpdatesEnabled(false);
	popup->clear();

	int breaker = 0;
	for (auto e : choices.toStdMap())
	{
		auto item = new QTreeWidgetItem(popup);
		item->setText(0, e.first);
		item->setData(0, Qt::ToolTipRole, e.second);
		item->setForeground(0, color);
		if (breaker == 20)
			break;
		breaker++;
	}

	popup->setCurrentItem(popup->topLevelItem(0));
	popup->resizeColumnToContents(0);
	popup->setUpdatesEnabled(true);

	popup->move(editor->mapToGlobal(QPoint(0, editor->height())));
	popup->setFocus();
	popup->show();
}

void PSuggestCompletion::doneCompletion()
{
	popup->hide();
	
	QTreeWidgetItem *item = popup->currentItem();
	if (item) 
	{
		emit ProductIsChosen(item->data(0, Qt::ToolTipRole).toInt());
		QMetaObject::invokeMethod(editor, "returnPressed");
	}
}

void PSuggestCompletion::autoSuggest()
{
	std::string errorMessage = "";
	BusinessLayer::ProductType pType;
	pType.SetCode("RAW");
	std::string pTypeFilter = pType.GenerateFilter(dataFormParent->dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::ProductType> pTypeVector = dataFormParent->dataFormBL->GetAllDataForClass<BusinessLayer::ProductType>(errorMessage, pTypeFilter);
	if (pTypeVector.size() == 0)
	{
		QString message = tr("Sorry could not find product type with \"Raw\" code!");
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	BusinessLayer::Product product;
	std::string productNameFilter = product.GenerateLikeFilter(dataFormParent->dataFormBL->globalVar, dataFormParent->dataFormBL->GetOrmasDal(), editor->text().toStdString());
	std::vector<std::string> filterList;
	product.SetProductTypeID(pTypeVector.at(0).GetID());
	std::string productFilter = product.GenerateFilter(dataFormParent->dataFormBL->GetOrmasDal());
	filterList.push_back(productFilter);
	filterList.push_back(productNameFilter);
	std::string totalFilter = dataFormParent->dataFormBL->ConcatenateFilters(filterList);
	std::vector<BusinessLayer::ProductView> productVector = dataFormParent->dataFormBL->GetAllDataForClass<BusinessLayer::ProductView>(errorMessage, totalFilter);
	if (productVector.size() == 0)
	{
		QString message = tr("Sorry could not find product!");
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		editor->setText("");
		return;
	}
	QMap<QString, int> choices;
	for each (auto productItem in productVector)
	{
		choices.insert(productItem.GetName().c_str(), productItem.GetID());
	}
	showCompletion(choices);
}

	