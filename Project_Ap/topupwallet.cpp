#include "topupwallet.h"
#include "ui_topupwallet.h"
#include "paymentgateway.h"
#include "clientprof.h"
#include <fstream>
using namespace std;
TopUpWallet::TopUpWallet(client _clie, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopUpWallet)
{

    ui->setupUi(this);
    ui->spinBox->setMinimum(1000);
    ui->spinBox->setMaximum(999999999);
    clie=_clie;

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
        clie.set_Wallet_balance(clie.get_Wallet_balance() + AmountOfInventoryincrease);
        fstream database_clients("clients.txt", ios::in | ios::out | ios::binary);
        database_clients.seekp((clie.get_ID()-1)*sizeof(client));
        database_clients.write((char*)&clie,sizeof(client));
        database_clients.close();
    }
}
void TopUpWallet::on_pushButton_refuse_clicked()
{
    this->close();
}
