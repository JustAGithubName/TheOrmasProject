#include "stdafx.h"
#include "DocForm.h"
#include "MainForm.h"
#include <QFile>
#include <QFileDialog>

DocForm::DocForm(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QWidget(parent)
{
	setupUi(this);
	dialogBL = ormasBL;

	QObject::connect(saveBtn, &QPushButton::released, this, &DocForm::Save);
	QObject::connect(closeBtn, &QPushButton::released, this, &DocForm::Close);
}

DocForm::~DocForm()
{
	
}



void DocForm::Save()
{
	QList<QUrl> urls;
	urls << QUrl::fromLocalFile("/Users/reports/")
		<< QUrl::fromLocalFile(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first());

	
	QFileDialog dialog;
	dialog.setSidebarUrls(urls);
	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setNameFilter(tr("HTLM (*.html)"));
	if (dialog.exec()) {
		QFile file(dialog.selectedFiles().first());
		if (!file.open(QFile::WriteOnly | QFile::Text)) {
			QMessageBox::warning(this, tr("Application"),
				tr("Cannot write file %1:\n%2.")
				.arg(QDir::toNativeSeparators(dialog.selectedFiles().first()),
				file.errorString()));
			return;
		}
		QTextStream out(&file);
		out.setCodec("UTF-8");
		out << content;
	}
	Close();
}

void DocForm::Close()
{
	this->parentWidget()->close();
}

void DocForm::SetContent(QString cont)
{
	content = cont;
}
