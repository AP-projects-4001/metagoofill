#include "purchaserecords.h"
#include "ui_purchaserecords.h"

PurchaseRecords::PurchaseRecords(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PurchaseRecords)
{
    ui->setupUi(this);
    QString content = "ردیف\tاسم کالا\tتعداد\tقیمت";
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
}

PurchaseRecords::~PurchaseRecords()
{
    delete ui;
}
