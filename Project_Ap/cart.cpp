#include "cart.h"
#include "ui_cart.h"

cart::cart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cart)
{
    ui->setupUi(this);
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

