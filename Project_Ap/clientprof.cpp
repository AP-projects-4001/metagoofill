#include "clientprof.h"
#include "ui_clientprof.h"
#include <cstring>
#include "goodslist.h"
#include "purchaserecords.h"
#include "loginpage.h"
#include "topupwallet.h"
#include "cart.h"

using namespace std;
clientProf::clientProf(client cli_info, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clientProf)
{
    ui->setupUi(this);
    clie = cli_info;// ذخیره شی در کلاس
    show_prof();
//    string temp;

//    //set name.
//    cli_info.char_array_to_string(temp, 16, cli_info.get_Name());
//    ui->plainTextEdit_13->setPlainText(QString::fromStdString(temp));

//    //set phonenumber.
//    cli_info.char_array_to_string(temp, 12, cli_info.get_phoneNumber());
//    ui->plainTextEdit_5->setPlainText(QString::fromStdString(temp));

//    //set city.
//    cli_info.char_array_to_string(temp, 11, cli_info.get_city());
//    ui->plainTextEdit_15->setPlainText(QString::fromStdString(temp));

//    //set address.
//    cli_info.char_array_to_string(temp, 31, cli_info.get_Address());
//    ui->plainTextEdit_14->setPlainText(QString::fromStdString(temp));

//    //set hidden password.
//    temp = "*********";//
//    ui->plainTextEdit_17->setPlainText(QString::fromStdString(temp));

//    //set username.
//    cli_info.char_array_to_string(temp, 16, cli_info.get_User());
//    ui->plainTextEdit_16->setPlainText(QString::fromStdString(temp));

//    ui->label->setText(QString::number(cli_info.get_Wallet_balance()));
}

clientProf::~clientProf()
{
    delete ui;
}

void clientProf::on_pushButton_8_clicked()
{
    //تغییر اطلاعات و ذخیره در فایل
    fstream database_clients("clients.txt", ios::in | ios::out | ios::binary);
    database_clients.seekg((clie.get_ID()-1)*sizeof(client));
    database_clients.read((char*)&clie,sizeof(client));

    clie.string_to_char_array(clie.get_Name(), 16, ui->plainTextEdit_13->toPlainText().toStdString());
    clie.string_to_char_array(clie.get_phoneNumber(), 12, ui->plainTextEdit_5->toPlainText().toStdString());
    clie.string_to_char_array(clie.get_city(), 11, ui->plainTextEdit_15->toPlainText().toStdString());
    clie.string_to_char_array(clie.get_Address(), 31, ui->plainTextEdit_14->toPlainText().toStdString());
    clie.string_to_char_array(clie.get_User(), 16, ui->plainTextEdit_16->toPlainText().toStdString());

    database_clients.seekp((clie.get_ID()-1)*sizeof(client));
    database_clients.write((char*)&clie,sizeof(client));
    database_clients.close();

    show_prof();

}


void clientProf::on_pushButton_7_clicked()
{
    //رفتن به فروشگاه
    this->close();
    goodsList *goodslist= new goodsList(clie);
}


void clientProf::on_pushButton_6_clicked()//?
{
    PurchaseRecords *purchaserecords= new PurchaseRecords(clie,this);
    purchaserecords->show();
    this->hide();
}


void clientProf::on_pushButton_4_clicked()
{
    this->close();
    LoginPage *relogin = new LoginPage(1);
    relogin->show();
}



void clientProf::on_pushButton_5_clicked()
{
    //شارژ کیف
    TopUpWallet *walletact = new TopUpWallet(clie, this);
    walletact->show();
}


void clientProf::on_pushButton_9_clicked()
{
    cart *_cart = new cart(clie);
    this->close();
    _cart->show();
}

void clientProf::show_prof()
{
        string temp;

        //set name.
        clie.char_array_to_string(temp, 16, clie.get_Name());
        ui->plainTextEdit_13->setPlainText(QString::fromStdString(temp));

        //set phonenumber.
        clie.char_array_to_string(temp, 12, clie.get_phoneNumber());
        ui->plainTextEdit_5->setPlainText(QString::fromStdString(temp));

        //set city.
        clie.char_array_to_string(temp, 11, clie.get_city());
        ui->plainTextEdit_15->setPlainText(QString::fromStdString(temp));

        //set address.
        clie.char_array_to_string(temp, 31, clie.get_Address());
        ui->plainTextEdit_14->setPlainText(QString::fromStdString(temp));

        //set hidden password.
        temp = "*********";//
        ui->plainTextEdit_17->setPlainText(QString::fromStdString(temp));

        //set username.
        clie.char_array_to_string(temp, 16, clie.get_User());
        ui->plainTextEdit_16->setPlainText(QString::fromStdString(temp));

        ui->label->setText(QString::number(clie.get_Wallet_balance()));
}
