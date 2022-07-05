#include "paymentgateway.h"
#include "ui_paymentgateway.h"
#include <QMessageBox>
PaymentGateWay::PaymentGateWay(int price, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentGateWay)
{
    ui->setupUi(this);
    prc = price;
    ui->label_6->setText(QString::number(prc));
}

PaymentGateWay::~PaymentGateWay()
{
    delete ui;
}

void PaymentGateWay::on_pushButton_clicked()
{
    if(ui->textEdit->toPlainText().toStdString().length()!=16||ui->spinBox->value()==0||ui->spinBox_2==0)
    {
        QMessageBox::warning(this,"توجه","شماره کارت باید 16 رقم باشد");
        return;
    }
    else//پرداخت موفقیت آمیز
    {
        QMessageBox::information(this,"توجه","پرداخت موفقیت آمیز");
        emit PaymentStatusOnThePaymentGateWayPage();
    }
}

void PaymentGateWay::on_pushButton_2_clicked()//دکمه انصراف از پرداخت
{
    QMessageBox::information(this,"توجه","عملیات پرداخت لغو شد");
    emit PaymentStatusOnThePaymentGateWayPage();
}
