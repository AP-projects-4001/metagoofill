#include "topupwallet.h"
#include "ui_topupwallet.h"
#include "paymentgateway.h"
#include "clientprof.h"
TopUpWallet::TopUpWallet(client _clie, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopUpWallet)
{
    clie=_clie;
    ui->setupUi(this);
    ui->spinBox->setMinimum(1000);
    ui->spinBox->setMaximum(999999999);

}

TopUpWallet::~TopUpWallet()
{
    delete ui;
}

void TopUpWallet::on_pushButton_clicked()
{
    AmountOfInventoryincrease = ui->spinBox->value();
    PaymentGateWay *p = new PaymentGateWay(AmountOfInventoryincrease,this);
    this->hide();
    connect(p, SIGNAL(PaymentStatusOnThePaymentGateWayPage(bool)), this, SLOT(Charging_success(bool)));
    p->show();
}
void TopUpWallet::Charging_success(bool m)
{
    this->show();
    if(m==1)
    {
        clie.Wallet_balance=clie.Wallet_balance + AmountOfInventoryincrease;
    }
}
void TopUpWallet::on_pushButton_refuse_clicked()
{
    this->close();
    clientProf *reprof = new clientProf(clie);
    reprof->show();
}
