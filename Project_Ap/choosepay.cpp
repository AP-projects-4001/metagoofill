#include "choosepay.h"
#include "ui_choosepay.h"

choosepay::choosepay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choosepay)
{
    ui->setupUi(this);
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
    //go to wallet pay
    method = false;
    emit send_method(method);
}

