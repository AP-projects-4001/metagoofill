#include "paymentgateway.h"
#include "ui_paymentgateway.h"
#include <QMessageBox>
PaymentGateWay::PaymentGateWay(int price, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentGateWay)
{
    ui->setupUi(this);
    prc = price;
}

PaymentGateWay::~PaymentGateWay()
{
    delete ui;
}

void PaymentGateWay::on_pushButton_clicked()
{
    if(ui->textEdit->toPlainText().toStdString().length()!=16)
    {
        QMessageBox::warning(this,"توجه","شماره کارت باید 16 رقم باشد");
        return;
    }
}
