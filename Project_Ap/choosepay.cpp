#include "choosepay.h"
#include "ui_choosepay.h"
#include <QMessageBox>
choosepay::choosepay(int _sum,client _clie,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choosepay)
{
    ui->setupUi(this);
    this->sum=_sum;
    this->clie=_clie;
}

choosepay::~choosepay()
{
    delete ui;
}

void choosepay::on_pushButton_difectpay_clicked()
{
    //go to payment gateway;
    method = true;
    emit send_method(method);
}

void choosepay::on_pushButton_wallet_clicked()
{
    bool check = clie.Wallet_balance>=sum;
    if(check==1)
        emit send_status_payment_from_wallet();
    else
    {
        QMessageBox::about(this,"توجه","کیف پول خودرا شارژ کنید");
    }
}


void choosepay::on_pushButton_wallet_2_clicked()
{
    method = false;
    emit send_method(method);
}

void choosepay::on_pushButton_refuse_clicked()
{
    this->close();
}
