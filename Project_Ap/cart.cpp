#include "cart.h"
#include "ui_cart.h"
#include <fstream>

#define data_product "database_products.txt"
using namespace std;
cart::cart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cart)
{
    ui->setupUi(this);
    fstream database_buys("database_buys.txt",ios::app | ios::binary);
    database_buys.close();

    fstream database_sells("database_sells.txt",ios::app | ios::binary);
    database_sells.close();

    fstream database_cart("database_cart.txt",ios::app | ios::binary);
    database_cart.close();
}

cart::~cart()
{
    delete ui;
}

void cart::on_pushButton_filter_clicked()
{
//    int Price = 0;
//    if(numOfProducts >= 1)
//    {
//        Price += ((ui->spinBox->displayIntegerBase()) * (ui->label_price_10->text().toInt()));
//    }

//    if(numOfProducts >= 2)
//    {
//        Price += ((ui->spinBox_2->displayIntegerBase()) * (ui->label_price_11->text().toInt()));

//    }

//    if(numOfProducts >= 3)
//    {
//        Price += ((ui->spinBox_3->displayIntegerBase()) * (ui->label_price_12->text().toInt()));

//    }

//    if(numOfProducts >= 4)
//    {
//        Price += ((ui->spinBox_4->displayIntegerBase()) * (ui->label_price_13->text().toInt()));

//    }

//    if(numOfProducts >= 5)
//    {
//        Price += ((ui->spinBox_5->displayIntegerBase()) * (ui->label_price_14->text().toInt()));

//    }

//    if(numOfProducts >= 6)
//    {
//        Price += ((ui->spinBox_6->displayIntegerBase()) * (ui->label_price_15->text().toInt()));

//    }

//    if(numOfProducts >= 7)
//    {
//        Price += ((ui->spinBox_7->displayIntegerBase()) * (ui->label_price_16->text().toInt()));

//    }

//    if(numOfProducts >= 8)
//    {
//        Price += ((ui->spinBox_8->displayIntegerBase()) * (ui->label_price_17->text().toInt()));

//    }

//    if(numOfProducts >= 9)
//    {
//        Price += ((ui->spinBox_9->displayIntegerBase()) * (ui->label_price_18->text().toInt()));

//    }


    int price;//it should increase when any buy buttons clicked;

    payMethod = new choosepay(this);
    this->hide();
    payMethod->show();

    connect(payMethod, SIGNAL(send_method(bool)), this, SLOT(rec_method(bool)));
}

void cart::rec_method(bool method)
{
    bool meth = method;
    int price = 0;// این متغیر بعدا با خواندن فایل کالاها بدست خواهد آمد.
    if(meth == true)
    {
        PaymentGateWay *directpay = new PaymentGateWay(price, this);
        directpay->show();
    }

    else
    {
        //show new page of charging wallet.
        TopUpWallet *fromWallet = new TopUpWallet(price, this);
        fromWallet->show();
    }
}

void cart::add_to_factor()
{
    int len_cart;
    int type;
    int ptr_product;
    int number_orders;

    fstream  database_buy_and_sell("database_buy_and_sell.txt",ios::in | ios::out | ios::binary);
    database_buy_and_sell.seekg( number_factors*sizeof(Factor));

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.ID-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));

    fstream database_product(data_product,  ios::in | ios::out | ios::binary);

    for(int i=0;i<len_cart;i++){
        database_cart.read((char*)&type, sizeof(int));
        database_cart.read((char*)&ptr_product, sizeof(int));
        database_cart.read((char*)&number_orders, sizeof(int));
        factor.type=type;
        factor.ptr_product=ptr_product;
        factor.number=number_orders;

        database_product.read((char*)&product, sizeof(int));
        factor.price=product.price;
        factor.ID_customer=product.ID_customer;
        factor.ID_client=clie.ID;

        database_buy_and_sell.write((char*)&factor,sizeof(Factor));
        number_factors++;
    }


    //save number_factors

    database_buy_and_sell.close();
    database_cart.close();
    database_product.close();
}


void cart::add_to_buys()
{
    int len_cart;
    int ptr_factor;
    int ptr_next_buy;

    fstream  database_buys("database_buys.txt",ios::in | ios::out | ios::binary);

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.ID-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));

    ptr_next_buy=number_buys*sizeof(int)*2;
    if(number_mybuys!=0){
        database_buys.seekg(ptr_end_mybuys+sizeof(int));
        database_buys.write((char*)&ptr_next_buy,sizeof(int));
    }
    else{
        ptr_start_mybuys=ptr_next_buy;
        ptr_end_mybuys= ptr_next_buy;
    }
    database_buys.seekg( number_buys*sizeof(int)*2);
    for(int i=0;i<len_cart;i++){
        ptr_factor=(number_factors-len_cart+i)* sizeof(Factor);
        ptr_next_buy+=(sizeof(int)*2);
        database_buys.write((char*)&ptr_factor,sizeof(int));
        database_buys.write((char*)&ptr_next_buy,sizeof(int));

        number_mybuys++;
        number_buys++;
    }
    ptr_end_mybuys= ptr_next_buy-(sizeof(int)*2);

    //save number_buys

    database_buys.close();
    database_cart.close();
}

void cart::add_to_sells()
{
    int len_cart;
    int ptr_factor;
    int ptr_next_sell;

    fstream  database_sells("database_sells.txt",ios::in | ios::out | ios::binary);

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.ID-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));

    ptr_next_sell=number_sells*sizeof(int)*2;
    if(number_mysells!=0){
        database_sells.seekg(ptr_end_mysells+sizeof(int));
        database_sells.write((char*)&ptr_next_sell,sizeof(int));
    }
    else{
        ptr_start_mysells=ptr_next_sell;
        ptr_end_mysells= ptr_next_sell;
    }
    database_sells.seekg( number_sells*sizeof(int)*2);
    for(int i=0;i<len_cart;i++){
        ptr_factor=(number_factors-len_cart+i)* sizeof(Factor);
        ptr_next_sell+=(sizeof(int)*2);
        database_sells.write((char*)&ptr_factor,sizeof(int));
        database_sells.write((char*)&ptr_next_sell,sizeof(int));

        number_mysells++;
        number_sells++;
    }
    ptr_end_mysells= ptr_next_sell-(sizeof(int)*2);

    //save number_sells

    database_sells.close();
    database_cart.close();
}

