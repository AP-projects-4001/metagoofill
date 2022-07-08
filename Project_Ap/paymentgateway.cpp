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
    ui->spinBox->setMinimum(1000);
    ui->spinBox->setMaximum(999999999);
    ui->spinBox_2->setMinimum(100);
    ui->spinBox_2->setMaximum(9999);
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
        emit PaymentStatusOnThePaymentGateWayPage(1);
        this->close();
    }
}

void PaymentGateWay::on_pushButton_2_clicked()//دکمه انصراف از پرداخت
{
    QMessageBox::information(this,"توجه","عملیات پرداخت لغو شد");
    emit PaymentStatusOnThePaymentGateWayPage(0);
    this->close();
}
