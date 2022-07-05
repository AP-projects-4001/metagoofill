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
    flag_cart=0;
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
            flag_status[i]=status_product(products[i],number[i]);
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
            flag_status[i]=status_product(products[i],number[i]);
        }
        count+=end_part_cart;
    }
}

int cart::status_product(Product &product, int number)
{
    if(product.flag_delete_product==1){return 0;}
    else if(product.available==0){return 1;}
    else if(product.available<number){return 2;}
    else{return 3;}
}

void cart::show_cart()
{
    if(flag_cart==0){
        ui->pushButton_filter_2->hide();
        ui->pushButton_filter_4->hide();
        ui->label_type_28->hide();
        ui->label_type_29->hide();
        ui->pushButton_filter->show();
        ui->pushButton_filter_3->show();
    }
    else{
        ui->pushButton_filter_2->show();
        ui->pushButton_filter_4->show();
        ui->label_type_28->show();
        ui->label_type_29->show();
        ui->pushButton_filter->hide();
        ui->pushButton_filter_3->hide();
    }
    string str;
    if(end_part_cart >= 1) {
        ui->label_type_10->show();
        ui->label_price_10->show();
        ui->pushButton_16->show();
        ui->pushButton_g1->show();
        ui->spinBox_1->show();
        ui->label_type_19->show();
        ui->spinBox_1->setValue(number[0]);
        product.char_array_to_string(str,16,products[0].type);
        ui->label_type_10->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_10->setText(QString::number(products[0].price));
            show_status(ui->label_type_19,flag_status[0]);
        }
        else{
            ui->label_price_10->setText(QString::number(prices[count - (end_part_cart-0)]));
            ui->label_type_19->setText("موجود");
        }
    }
    else {
        ui->label_type_10->hide();
        ui->label_price_10->hide();
        ui->pushButton_16->hide();
        ui->pushButton_g1->hide();
        ui->spinBox_1->hide();
        ui->label_type_19->hide();
    }

    if(end_part_cart >= 2) {
        ui->label_type_11->show();
        ui->label_price_11->show();
        ui->pushButton_14->show();
        ui->pushButton_g2->show();
        ui->spinBox_2->show();
        ui->label_type_20->show();
        ui->spinBox_2->setValue(number[1]);
        product.char_array_to_string(str,16,products[1].type);
        ui->label_type_11->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_11->setText(QString::number(products[1].price));
            show_status(ui->label_type_20,flag_status[1]);
        }
        else{
            ui->label_price_11->setText(QString::number(prices[count - (end_part_cart-1)]));
            ui->label_type_20->setText("موجود");
        }
    }
    else {
        ui->label_type_11->hide();
        ui->label_price_11->hide();
        ui->pushButton_14->hide();
        ui->pushButton_g2->hide();
        ui->spinBox_2->hide();
        ui->label_type_20->hide();
    }

    if(end_part_cart >= 3) {
        ui->label_type_12->show();
        ui->label_price_12->show();
        ui->pushButton_15->show();
        ui->pushButton_g3->show();
        ui->spinBox_3->show();
        ui->label_type_21->show();
        ui->spinBox_3->setValue(number[2]);
        product.char_array_to_string(str,16,products[2].type);
        ui->label_type_12->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_12->setText(QString::number(products[2].price));
            show_status(ui->label_type_21,flag_status[2]);
        }
        else{
            ui->label_price_12->setText(QString::number(prices[count - (end_part_cart-2)]));
            ui->label_type_21->setText("موجود");
        }
    }
    else {
        ui->label_type_12->hide();
        ui->label_price_12->hide();
        ui->pushButton_15->hide();
        ui->pushButton_g3->hide();
        ui->spinBox_3->hide();
        ui->label_type_21->hide();
    }

    if(end_part_cart >= 4) {
        ui->label_type_13->show();
        ui->label_price_13->show();
        ui->pushButton_13->show();
        ui->pushButton_g4->show();
        ui->spinBox_4->show();
        ui->label_type_22->show();
        ui->spinBox_4->setValue(number[3]);
        product.char_array_to_string(str,16,products[3].type);
        ui->label_type_13->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_13->setText(QString::number(products[3].price));
            show_status(ui->label_type_22,flag_status[3]);
        }
        else{
            ui->label_price_13->setText(QString::number(prices[count - (end_part_cart-3)]));
            ui->label_type_22->setText("موجود");
        }
    }
    else {
        ui->label_type_13->hide();
        ui->label_price_13->hide();
        ui->pushButton_13->hide();
        ui->pushButton_g4->hide();
        ui->spinBox_4->hide();
        ui->label_type_22->hide();
    }

    if(end_part_cart >= 5) {
        ui->label_type_14->show();
        ui->label_price_14->show();
        ui->pushButton_12->show();
        ui->pushButton_g5->show();
        ui->spinBox_5->show();
        ui->label_type_23->show();
        ui->spinBox_5->setValue(number[4]);
        product.char_array_to_string(str,16,products[4].type);
        ui->label_type_14->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_14->setText(QString::number(products[4].price));
            show_status(ui->label_type_23,flag_status[4]);
        }
        else{
            ui->label_price_14->setText(QString::number(prices[count - (end_part_cart-4)]));
            ui->label_type_23->setText("موجود");
        }
    }
    else {
        ui->label_type_14->hide();
        ui->label_price_14->hide();
        ui->pushButton_12->hide();
        ui->pushButton_g5->hide();
        ui->spinBox_5->hide();
        ui->label_type_23->hide();
    }

    if(end_part_cart >= 6) {
        ui->label_type_15->show();
        ui->label_price_15->show();
        ui->pushButton_17->show();
        ui->pushButton_g6->show();
        ui->spinBox_6->show();
        ui->label_type_24->show();
        ui->spinBox_6->setValue(number[5]);
        product.char_array_to_string(str,16,products[5].type);
        ui->label_type_15->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_15->setText(QString::number(products[5].price));
            show_status(ui->label_type_24,flag_status[5]);
        }
        else{
            ui->label_price_15->setText(QString::number(prices[count - (end_part_cart-5)]));
            ui->label_type_24->setText("موجود");
        }
    }
    else {
        ui->label_type_15->hide();
        ui->label_price_15->hide();
        ui->pushButton_17->hide();
        ui->pushButton_g6->hide();
        ui->spinBox_6->hide();
        ui->label_type_24->hide();
    }

    if(end_part_cart >= 7) {
        ui->label_type_16->show();
        ui->label_price_16->show();
        ui->pushButton_18->show();
        ui->pushButton_g7->show();
        ui->spinBox_7->show();
        ui->label_type_25->show();
        ui->spinBox_7->setValue(number[6]);
        product.char_array_to_string(str,16,products[6].type);
        ui->label_type_16->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_16->setText(QString::number(products[6].price));
            show_status(ui->label_type_25,flag_status[6]);
        }
        else{
            ui->label_price_16->setText(QString::number(prices[count - (end_part_cart-6)]));
            ui->label_type_25->setText("موجود");
        }
    }
    else {
        ui->label_type_16->hide();
        ui->label_price_16->hide();
        ui->pushButton_18->hide();
        ui->pushButton_g7->hide();
        ui->spinBox_7->hide();
        ui->label_type_25->hide();
    }

    if(end_part_cart >= 8) {
        ui->label_type_17->show();
        ui->label_price_17->show();
        ui->pushButton_19->show();
        ui->pushButton_g8->show();
        ui->spinBox_8->show();
        ui->label_type_26->show();
        ui->spinBox_8->setValue(number[7]);
        product.char_array_to_string(str,16,products[7].type);
        ui->label_type_17->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_17->setText(QString::number(products[7].price));
            show_status(ui->label_type_26,flag_status[7]);
        }
        else{
            ui->label_price_17->setText(QString::number(prices[count - (end_part_cart-7)]));
            ui->label_type_26->setText("موجود");
        }
    }
    else {
        ui->label_type_17->hide();
        ui->label_price_17->hide();
        ui->pushButton_19->hide();
        ui->pushButton_g8->hide();
        ui->spinBox_8->hide();
        ui->label_type_26->hide();
    }

    if(end_part_cart >= 9) {
        ui->label_type_18->show();
        ui->label_price_18->show();
        ui->pushButton_20->show();
        ui->pushButton_g9->show();
        ui->spinBox_9->show();
        ui->label_type_27->show();
        ui->spinBox_9->setValue(number[8]);
        product.char_array_to_string(str,16,products[8].type);
        ui->label_type_18->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_18->setText(QString::number(products[8].price));
            show_status(ui->label_type_27,flag_status[8]);
        }
        else{
            ui->label_price_18->setText(QString::number(prices[count - (end_part_cart-8)]));
            ui->label_type_27->setText("موجود");
        }
    }
    else {
        ui->label_type_18->hide();
        ui->label_price_18->hide();
        ui->pushButton_20->hide();
        ui->pushButton_g9->hide();
        ui->spinBox_9->hide();
        ui->label_type_27->hide();
    }
}

void cart::show_status(QLabel* label_status, int flag_status)
{
    if(flag_status==0){label_status->setText("حذفی");}
    else if(flag_status==1){label_status->setText("ناموجود");}
    else if(flag_status==2){label_status->setText("ناکافی");}
    else if(flag_status==3){label_status->setText("موجود");}
}

bool cart::status_cart(int sum)
{
    sum=0;
    int type;
    int ptr_product;
    int number_orders;

    fstream database_product(data_product,ios::in | ios::out | ios::binary);
    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);

    database_cart.seekg((clie.ID-1)*(3*20+1)*sizeof(int)+sizeof(int));

    for(int i=0;i<len_cart;i++){
        database_cart.read((char*)&type, sizeof(int));
        database_cart.read((char*)&ptr_product, sizeof(int));
        database_cart.read((char*)&number_orders, sizeof(int));
        database_product.seekg(ptr_product);
        database_product.read((char*)&product, sizeof(Product));
        prices[i]=product.price;
        sum+=(number_orders*prices[i]);
        if(status_product(product,number_orders)!=3){return 0;}
    }
    return 1;
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
    int sum=0;
    if(status_cart(sum)==1){
        flag_cart=1;
        show_cart();
    }
    else{}
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

void cart::on_pushButton_filter_2_clicked()
{
    choosepay *payMethod = new choosepay(this);
    payMethod->show();

    connect(payMethod, SIGNAL(send_method(bool)), this, SLOT(rec_method(bool)));
    //connect(payMethod, SIGNAL(status_payment()), this, SLOT(status_payment()));
    transaction();
}

void cart::rec_method(bool method)
{
    if(method == 1)
    {
        //Show Payment GateWay Page
        PaymentGateWay *directpay = new PaymentGateWay(sum, this);
        this->hide();
        connect(directpay, SIGNAL(PaymentStatusOnThePaymentGateWayPage(bool)), this, SLOT(status_payment(bool)));
        directpay->show();
    }

    else//بر روی دکمه شارژ کیف پول کلیک شده
    {
        //show new page of charging wallet.
        TopUpWallet *fromWallet = new TopUpWallet(clie, this);
        fromWallet->show();
    }
}

void cart::status_payment()
{
    this->show();
}
