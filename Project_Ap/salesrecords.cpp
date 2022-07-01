#include "salesrecords.h"
#include "ui_salesrecords.h"

SalesRecords::SalesRecords(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalesRecords)
{
    ui->setupUi(this);
    QString content = "اسم کالا\tتعداد\tقیمت";
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
}

SalesRecords::~SalesRecords()
{
    delete ui;
}
