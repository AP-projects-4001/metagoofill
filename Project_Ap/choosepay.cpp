#include "choosepay.h"
#include "ui_choosepay.h"
#include <QMessageBox>
#include <fstream>
using namespace std;
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
    this->close();
}

void choosepay::on_pushButton_wallet_clicked()
{
    fstream database_clients("clients.txt", ios::in | ios::out | ios::binary);
    database_clients.seekg((clie.get_ID()-1)*sizeof(client));
    database_clients.read((char*)&clie,sizeof(client));
    bool check = clie.get_Wallet_balance()>=sum;
    if(check==1){
        clie.set_Wallet_balance(clie.get_Wallet_balance() - sum);
        database_clients.seekp((clie.get_ID()-1)*sizeof(client));
        database_clients.write((char*)&clie,sizeof(client));
        database_clients.close();
        emit send_status_payment_from_wallet(1);
        this->close();
    }
    else
    {
        QMessageBox::about(this,"توجه","کیف پول خودرا شارژ کنید");
        database_clients.close();
    }
}


void choosepay::on_pushButton_wallet_2_clicked()
{
    method = false;
    emit send_method(method);
    this->close();
}

void choosepay::on_pushButton_refuse_clicked()
{
    this->close();
}
