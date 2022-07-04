#include "cart.h"
#include "ui_cart.h"
#include <fstream>

#define data_product "database_products.txt"
using namespace std;
cart::cart(client _clie,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cart)
{
    ui->setupUi(this);

    clie=_clie;

    start_cart();
    next_to_cart(9);
    show_cart();
}

cart::~cart()
{
    delete ui;
}

void cart::add_to_factor()
{
    int len_cart;
    int type;
    int ptr_product;
    int number_orders;

    number_factors=0;

    fstream  database_factor("database_factors.txt",ios::in | ios::out | ios::binary);
    database_factor.seekg( number_factors*sizeof(Factor));

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

        database_factor.write((char*)&factor,sizeof(Factor));
        number_factors++;
    }


    //save number_factors

    database_factor.close();
    database_cart.close();
    database_product.close();
}


void cart::add_to_buys()
{
    int len_cart;
    int ptr_factor;
    int ptr_next_buy;

    number_buys=0;

    fstream  database_buys("database_buys.txt",ios::in | ios::out | ios::binary);

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.ID-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));

    ptr_next_buy=number_buys*sizeof(int)*2;
    if(clie.number_mybuys!=0){
        database_buys.seekp(clie.ptr_end_mybuys+sizeof(int));
        database_buys.write((char*)&ptr_next_buy,sizeof(int));
    }
    else{
        clie.ptr_start_mybuys=ptr_next_buy;
        clie.ptr_end_mybuys= ptr_next_buy;
    }
    database_buys.seekg( number_buys*sizeof(int)*2);
    for(int i=0;i<len_cart;i++){
        ptr_factor=(number_factors-len_cart+i)* sizeof(Factor);
        ptr_next_buy+=(sizeof(int)*2);
        database_buys.write((char*)&ptr_factor,sizeof(int));
        database_buys.write((char*)&ptr_next_buy,sizeof(int));

        clie.number_mybuys++;
        number_buys++;
    }
    clie.ptr_end_mybuys= ptr_next_buy-(sizeof(int)*2);

    fstream database_clients("clients.txt", ios::in | ios::out | ios::binary);
    database_clients.seekp((clie.ID-1)*sizeof(client));
    database_clients.write((char*)&clie,sizeof(client));
    database_clients.close();

    //save number_buys

    database_buys.close();
    database_cart.close();
}

void cart::add_to_sells()
{
    int len_cart;
    int ptr_factor;
    int ptr_next_sell;

    number_sells=0;

    fstream database_customers("customers.txt", ios::in | ios::out | ios::binary);
    fstream  database_factor("database_factors.txt",ios::in | ios::out | ios::binary);
    fstream  database_sells("database_sells.txt",ios::in | ios::out | ios::binary);

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.ID-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));

    for(int i=0;i<len_cart;i++){
        ptr_factor=(number_factors-len_cart+i)*sizeof(Factor);
        database_sells.seekg( number_sells*sizeof(int)*2);
        database_sells.write((char*)&ptr_factor,sizeof(int));

        database_factor.seekg(ptr_factor);
        database_factor.read((char*)&factor,sizeof(Factor));

        database_customers.seekg((factor.ID_customer-1)*sizeof(customer));
        database_customers.read((char*)&cust,sizeof(customer));

        ptr_next_sell=number_sells*sizeof(int)*2;
        if(cust.number_mysells!=0){
            database_sells.seekp(cust.ptr_end_mysells+sizeof(int));
            database_sells.write((char*)&ptr_next_sell,sizeof(int));
        }
        else{
            cust.ptr_start_mysells=ptr_next_sell;
        }
        cust.ptr_end_mysells=ptr_next_sell;
        cust.number_mysells++;
        database_customers.seekp((factor.ID_customer-1)*sizeof(customer));
        database_customers.write((char*)&cust,sizeof(customer));

        number_sells++;
    }

    //save number_sells

    database_sells.close();
    database_cart.close();
    database_customers.close();
    database_factor.close();
}

void cart::start_cart()
{
    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.ID-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));
    count=0;
    database_cart.close();
}

void cart::next_to_cart(int part)
{
    int type;
    int ptr_product;
    int number_orders;

    if(count!=len_cart){
        fstream database_product(data_product,ios::in | ios::out | ios::binary);
        fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);

        database_cart.seekg((count)*(sizeof(int)*3)+(clie.ID-1)*(3*20+1)*sizeof(int)+sizeof(int));
        end_part_cart=len_cart-count;
        if(end_part_cart>=part-1){end_part_cart=part;}
        for(int i=0;i<end_part_cart;i++){
            database_cart.read((char*)&type, sizeof(int));
            database_cart.read((char*)&ptr_product, sizeof(int));
            database_cart.read((char*)&number_orders, sizeof(int));
            database_product.seekg(ptr_product);
            database_product.read((char*)&products[i], sizeof(Product));
            number[i]=number_orders;
        }
        count+=end_part_cart;
    }
}

void cart::preview_to_cart(int part)
{
    int type;
    int ptr_product;
    int number_orders;

    if(count>=(end_part_cart+part)){
        count-=end_part_cart;
        count-=part;
        end_part_cart=part;
        fstream database_product(data_product,ios::in | ios::out | ios::binary);
        fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);

        database_cart.seekg((count)*(sizeof(int)*3)+(clie.ID-1)*(3*20+1)*sizeof(int)+sizeof(int));
        for(int i=0;i<end_part_cart;i++){
            database_cart.read((char*)&type, sizeof(int));
            database_cart.read((char*)&ptr_product, sizeof(int));
            database_cart.read((char*)&number_orders, sizeof(int));
            database_product.seekg(ptr_product);
            database_product.read((char*)&products[i], sizeof(Product));
            number[i]=number_orders;
        }
        count+=end_part_cart;
    }
}

void cart::show_cart()
{
    string str;
    if(end_part_cart >= 1) {
        ui->label_type_10->show();
        ui->label_price_10->show();
        ui->pushButton_16->show();
        ui->pushButton_g1->show();
        ui->spinBox_1->show();
        ui->spinBox_1->setValue(number[0]);
        product.char_array_to_string(str,16,products[0].type);
        ui->label_type_10->setText(QString::fromStdString(str));
        ui->label_price_10->setText(QString::number(products[0].price));
    }
    else {
        ui->label_type_10->hide();
        ui->label_price_10->hide();
        ui->pushButton_16->hide();
        ui->pushButton_g1->hide();
        ui->spinBox_1->hide();
    }

    if(end_part_cart >= 2) {
        ui->label_type_11->show();
        ui->label_price_11->show();
        ui->pushButton_14->show();
        ui->pushButton_g2->show();
        ui->spinBox_2->show();
        ui->spinBox_2->setValue(number[1]);
        product.char_array_to_string(str,16,products[1].type);
        ui->label_type_11->setText(QString::fromStdString(str));
        ui->label_price_11->setText(QString::number(products[1].price));
    }
    else {
        ui->label_type_11->hide();
        ui->label_price_11->hide();
        ui->pushButton_14->hide();
        ui->pushButton_g2->hide();
        ui->spinBox_2->hide();
    }

    if(end_part_cart >= 3) {
        ui->label_type_12->show();
        ui->label_price_12->show();
        ui->pushButton_15->show();
        ui->pushButton_g3->show();
        ui->spinBox_3->show();
        ui->spinBox_3->setValue(number[2]);
        product.char_array_to_string(str,16,products[2].type);
        ui->label_type_12->setText(QString::fromStdString(str));
        ui->label_price_12->setText(QString::number(products[2].price));
    }
    else {
        ui->label_type_12->hide();
        ui->label_price_12->hide();
        ui->pushButton_15->hide();
        ui->pushButton_g3->hide();
        ui->spinBox_3->hide();
    }

    if(end_part_cart >= 4) {
        ui->label_type_13->show();
        ui->label_price_13->show();
        ui->pushButton_13->show();
        ui->pushButton_g4->show();
        ui->spinBox_4->show();
        ui->spinBox_4->setValue(number[3]);
        product.char_array_to_string(str,16,products[3].type);
        ui->label_type_13->setText(QString::fromStdString(str));
        ui->label_price_13->setText(QString::number(products[3].price));
    }
    else {
        ui->label_type_13->hide();
        ui->label_price_13->hide();
        ui->pushButton_13->hide();
        ui->pushButton_g4->hide();
        ui->spinBox_4->hide();
    }

    if(end_part_cart >= 5) {
        ui->label_type_14->show();
        ui->label_price_14->show();
        ui->pushButton_12->show();
        ui->pushButton_g5->show();
        ui->spinBox_5->show();
        ui->spinBox_5->setValue(number[4]);
        product.char_array_to_string(str,16,products[4].type);
        ui->label_type_14->setText(QString::fromStdString(str));
        ui->label_price_14->setText(QString::number(products[4].price));
    }
    else {
        ui->label_type_14->hide();
        ui->label_price_14->hide();
        ui->pushButton_12->hide();
        ui->pushButton_g5->hide();
        ui->spinBox_5->hide();
    }

    if(end_part_cart >= 6) {
        ui->label_type_15->show();
        ui->label_price_15->show();
        ui->pushButton_17->show();
        ui->pushButton_g6->show();
        ui->spinBox_6->show();
        ui->spinBox_6->setValue(number[5]);
        product.char_array_to_string(str,16,products[5].type);
        ui->label_type_15->setText(QString::fromStdString(str));
        ui->label_price_15->setText(QString::number(products[5].price));
    }
    else {
        ui->label_type_15->hide();
        ui->label_price_15->hide();
        ui->pushButton_17->hide();
        ui->pushButton_g6->hide();
        ui->spinBox_6->hide();
    }

    if(end_part_cart >= 7) {
        ui->label_type_16->show();
        ui->label_price_16->show();
        ui->pushButton_18->show();
        ui->pushButton_g7->show();
        ui->spinBox_7->show();
        ui->spinBox_7->setValue(number[6]);
        product.char_array_to_string(str,16,products[6].type);
        ui->label_type_16->setText(QString::fromStdString(str));
        ui->label_price_16->setText(QString::number(products[6].price));
    }
    else {
        ui->label_type_16->hide();
        ui->label_price_16->hide();
        ui->pushButton_18->hide();
        ui->pushButton_g7->hide();
        ui->spinBox_7->hide();
    }

    if(end_part_cart >= 8) {
        ui->label_type_17->show();
        ui->label_price_17->show();
        ui->pushButton_19->show();
        ui->pushButton_g8->show();
        ui->spinBox_8->show();
        ui->spinBox_8->setValue(number[7]);
        product.char_array_to_string(str,16,products[7].type);
        ui->label_type_17->setText(QString::fromStdString(str));
        ui->label_price_17->setText(QString::number(products[7].price));
    }
    else {
        ui->label_type_17->hide();
        ui->label_price_17->hide();
        ui->pushButton_19->hide();
        ui->pushButton_g8->hide();
        ui->spinBox_8->hide();
    }

    if(end_part_cart >= 9) {
        ui->label_type_18->show();
        ui->label_price_18->show();
        ui->pushButton_20->show();
        ui->pushButton_g9->show();
        ui->spinBox_9->show();
        ui->spinBox_9->setValue(number[8]);
        product.char_array_to_string(str,16,products[8].type);
        ui->label_type_18->setText(QString::fromStdString(str));
        ui->label_price_18->setText(QString::number(products[8].price));
    }
    else {
        ui->label_type_18->hide();
        ui->label_price_18->hide();
        ui->pushButton_20->hide();
        ui->pushButton_g9->hide();
        ui->spinBox_9->hide();
    }
}

void cart::transaction()
{

    add_to_factor();
    add_to_buys();
    add_to_sells();
    /*
    len_cart=0;
    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekp((clie.ID-1)*(3*20+1)*sizeof(int));
    database_cart.write((char*)&len_cart, sizeof(int));
    count=0;
    */
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


        //int price;//it should increase when any buy buttons clicked;

        //payMethod = new choosepay(this);
        //this->hide();
        //payMethod->show();

        //connect(payMethod, SIGNAL(send_method(bool)), this, SLOT(rec_method(bool)));
    transaction();
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

void cart::on_pushButton_next_clicked()
{
    next_to_cart(9);
    show_cart();
}

void cart::on_pushButton_prev_clicked()
{
    preview_to_cart(9);
    show_cart();
}
