#include "cart.h"
#include "ui_cart.h"
#include "goodslist.h"
#include <fstream>
#include <QMessageBox>

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
    if(flag_cart==0 && get_number_orders()==0){
        save_number_orders();
    }
    if(flag_cart==1){
        cansel_reserve_products();
        flag_cart=0;
    }
    delete ui;
}

void cart::add_to_factor()
{
    int len_cart;
    int type;
    int ptr_product;
    int number_orders;

    fstream database_numbers("numbers.txt", ios::in | ios::out | ios::binary);
    database_numbers.seekg((4-1)*sizeof(int));
    database_numbers.read((char*)&number_factors, sizeof(int));

    fstream  database_factor("database_factors.txt",ios::in | ios::out | ios::binary);
    database_factor.seekg( number_factors*sizeof(Factor));

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.get_ID()-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));

    fstream database_product(data_product,  ios::in | ios::out | ios::binary);

    for(int i=0;i<len_cart;i++){
        database_cart.read((char*)&type, sizeof(int));
        database_cart.read((char*)&ptr_product, sizeof(int));
        database_cart.read((char*)&number_orders, sizeof(int));
        factor.type=type;
        factor.ptr_product=ptr_product;
        factor.number=number_orders;

        database_product.seekg(ptr_product);
        database_product.read((char*)&product, sizeof(Product));
        factor.price=prices[i];
        factor.ID_customer=product.get_ID_customer();
        factor.ID_client=clie.get_ID();

        database_factor.write((char*)&factor,sizeof(Factor));
        number_factors++;
    }

    database_numbers.seekp((4-1)*sizeof(int));
    database_numbers.write((char*)&number_factors, sizeof(int));

    database_factor.close();
    database_cart.close();
    database_product.close();
    database_numbers.close();
}


void cart::add_to_buys()
{
    int len_cart;
    int ptr_factor;
    int ptr_next_buy;

    fstream  database_buys("database_buys.txt",ios::in | ios::out | ios::binary);

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.get_ID()-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));

    ptr_next_buy=(number_factors-len_cart)*sizeof(int)*2;
    if(clie.get_number_mybuys()!=0){
        database_buys.seekp(clie.get_ptr_end_mybuys()+sizeof(int));
        database_buys.write((char*)&ptr_next_buy,sizeof(int));
    }
    else{
        clie.set_ptr_start_mybuys(ptr_next_buy);
        clie.set_ptr_end_mybuys( ptr_next_buy);
    }
    database_buys.seekg((number_factors-len_cart)*sizeof(int)*2);
    for(int i=0;i<len_cart;i++){
        ptr_factor=((number_factors-len_cart)+i)* sizeof(Factor);
        ptr_next_buy+=(sizeof(int)*2);
        database_buys.write((char*)&ptr_factor,sizeof(int));
        database_buys.write((char*)&ptr_next_buy,sizeof(int));

        clie.set_number_mybuys(clie.get_number_mybuys()+1);
    }
    clie.set_ptr_end_mybuys( ptr_next_buy-(sizeof(int)*2));

    fstream database_clients("clients.txt", ios::in | ios::out | ios::binary);
    database_clients.seekp((clie.get_ID()-1)*sizeof(client));
    database_clients.write((char*)&clie,sizeof(client));
    database_clients.close();

    database_buys.close();
    database_cart.close();
}

void cart::add_to_sells()
{
    int len_cart;
    int ptr_factor;
    int ptr_next_sell;

    fstream database_customers("customers.txt", ios::in | ios::out | ios::binary);
    fstream  database_factor("database_factors.txt",ios::in | ios::out | ios::binary);
    fstream  database_sells("database_sells.txt",ios::in | ios::out | ios::binary);

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.get_ID()-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));

    for(int i=0;i<len_cart;i++){
        ptr_factor=(number_factors-len_cart+i)*sizeof(Factor);
        database_sells.seekp((number_factors-len_cart+i)*sizeof(int)*2);
        database_sells.write((char*)&ptr_factor,sizeof(int));

        database_factor.seekg(ptr_factor);
        database_factor.read((char*)&factor,sizeof(Factor));

        database_customers.seekg((factor.ID_customer-1)*sizeof(customer));
        database_customers.read((char*)&cust,sizeof(customer));

        ptr_next_sell=(number_factors-len_cart+i)*sizeof(int)*2;
        if(cust.get_number_mysells()!=0){
            database_sells.seekp(cust.get_ptr_end_mysells()+sizeof(int));
            database_sells.write((char*)&ptr_next_sell,sizeof(int));
        }
        else{
            cust.set_ptr_start_mysells(ptr_next_sell);
        }
        cust.set_ptr_end_mysells(ptr_next_sell);
        cust.set_number_mysells(cust.get_number_mysells()+1);
        cust.set_Wallet_balance(cust.get_Wallet_balance()+(factor.number*factor.price));
        database_customers.seekp((factor.ID_customer-1)*sizeof(customer));
        database_customers.write((char*)&cust,sizeof(customer));
    }

    database_sells.close();
    database_cart.close();
    database_customers.close();
    database_factor.close();
}

void cart::start_cart()
{
    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.get_ID()-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));
    database_cart.close();
    count=0;
    end_part_cart=0;
    flag_cart=0;
}

void cart::next_to_cart(int part)
{
    int type;
    int ptr_product;
    int number_orders;

    if(count!=len_cart){
        fstream database_product(data_product,ios::in | ios::out | ios::binary);
        fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);

        database_cart.seekg((count)*(sizeof(int)*3)+(clie.get_ID()-1)*(3*20+1)*sizeof(int)+sizeof(int));
        end_part_cart=len_cart-count;
        if(end_part_cart>=part){end_part_cart=part;}
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

        database_cart.close();
        database_product.close();
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

        database_cart.seekg((count)*(sizeof(int)*3)+(clie.get_ID()-1)*(3*20+1)*sizeof(int)+sizeof(int));
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

        database_cart.close();
        database_product.close();
    }
}

void cart::repet_to_cart(int part)
{
    int type;
    int ptr_product;
    int number_orders;

    count-=end_part_cart;
    fstream database_product(data_product,ios::in | ios::out | ios::binary);
    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);

    end_part_cart=len_cart-count;
    if(end_part_cart>=part){end_part_cart=part;}
    else if(end_part_cart==0){
        if(count>=part){
            count-=part;
            end_part_cart=len_cart-count;
        }
    }
    database_cart.seekg((count)*(sizeof(int)*3)+(clie.get_ID()-1)*(3*20+1)*sizeof(int)+sizeof(int));
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

    database_cart.close();
    database_product.close();
}

void cart::delete_product(int andis)
{
    int type;
    int ptr_product;
    int number_orders;

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((andis)*(sizeof(int)*3)+(clie.get_ID()-1)*(3*20+1)*sizeof(int)+sizeof(int));
    for(int i=andis;i<len_cart-1;i++){
        database_cart.seekg((sizeof(int)*3),ios::cur);
        database_cart.read((char*)&type, sizeof(int));
        database_cart.read((char*)&ptr_product, sizeof(int));
        database_cart.read((char*)&number_orders, sizeof(int));
        database_cart.seekp(-2*(sizeof(int)*3),ios::cur);
        database_cart.write((char*)&type, sizeof(int));
        database_cart.write((char*)&ptr_product, sizeof(int));
        database_cart.write((char*)&number_orders, sizeof(int));
    }
    len_cart--;
    database_cart.seekp((clie.get_ID()-1)*(3*20+1)*sizeof(int));
    database_cart.write((char*)&len_cart, sizeof(int));

    database_cart.close();

}

bool cart::get_number_orders()
{
    bool m;
    m=1;
    if(ui->spinBox_1->value()!=number[0]){
        number[0]=ui->spinBox_1->value();
        m=0;
    }
    if(ui->spinBox_2->value()!=number[1]){
        number[1]=ui->spinBox_2->value();
        m=0;
    }
    if(ui->spinBox_3->value()!=number[2]){
        number[2]=ui->spinBox_3->value();
        m=0;
    }
    if(ui->spinBox_4->value()!=number[3]){
        number[3]=ui->spinBox_4->value();
        m=0;
    }
    if(ui->spinBox_5->value()!=number[4]){
        number[4]=ui->spinBox_5->value();
        m=0;
    }
    if(ui->spinBox_6->value()!=number[5]){
        number[5]=ui->spinBox_6->value();
        m=0;
    }
    if(ui->spinBox_7->value()!=number[6]){
        number[6]=ui->spinBox_7->value();
        m=0;
    }
    if(ui->spinBox_8->value()!=number[7]){
        number[7]=ui->spinBox_8->value();
        m=0;
    }
    if(ui->spinBox_9->value()!=number[8]){
        number[8]=ui->spinBox_9->value();
        m=0;
    }
    return m;
}

void cart::save_number_orders()
{
    int number_orders;
    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);

    count-=end_part_cart;
    database_cart.seekp((count)*(sizeof(int)*3)+(clie.get_ID()-1)*(3*20+1)*sizeof(int)+sizeof(int));
    for(int i=0;i<end_part_cart;i++){
        number_orders=number[i];
        database_cart.seekp(sizeof(int)*2,ios::cur);
        database_cart.write((char*)&number_orders, sizeof(int));
    }
    count+=end_part_cart;

    database_cart.close();
}

int cart::status_product(Product &product, int number)
{
    if(product.get_flag_delete_product()==1){return 0;}
    else if(product.get_available()==0){return 1;}
    else if(product.get_available()<number){return 2;}
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
        ui->label_type_29->setText(QString::number(sum_buy));
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
        product.char_array_to_string(str,16,products[0].get_type());
        ui->label_type_10->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_10->setText(QString::number(products[0].get_price()));
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
        product.char_array_to_string(str,16,products[1].get_type());
        ui->label_type_11->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_11->setText(QString::number(products[1].get_price()));
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
        product.char_array_to_string(str,16,products[2].get_type());
        ui->label_type_12->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_12->setText(QString::number(products[2].get_price()));
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
        product.char_array_to_string(str,16,products[3].get_type());
        ui->label_type_13->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_13->setText(QString::number(products[3].get_price()));
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
        product.char_array_to_string(str,16,products[4].get_type());
        ui->label_type_14->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_14->setText(QString::number(products[4].get_price()));
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
        product.char_array_to_string(str,16,products[5].get_type());
        ui->label_type_15->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_15->setText(QString::number(products[5].get_price()));
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
        product.char_array_to_string(str,16,products[6].get_type());
        ui->label_type_16->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_16->setText(QString::number(products[6].get_price()));
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
        product.char_array_to_string(str,16,products[7].get_type());
        ui->label_type_17->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_17->setText(QString::number(products[7].get_price()));
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
        product.char_array_to_string(str,16,products[8].get_type());
        ui->label_type_18->setText(QString::fromStdString(str));
        if(flag_cart==0){
            ui->label_price_18->setText(QString::number(products[8].get_price()));
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

bool cart::status_cart()
{
    sum_sell=0;
    int type;
    int ptr_product;
    int number_orders;

    fstream database_product(data_product,ios::in | ios::out | ios::binary);
    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);

    database_cart.seekg((clie.get_ID()-1)*(3*20+1)*sizeof(int)+sizeof(int));

    for(int i=0;i<len_cart;i++){
        database_cart.read((char*)&type, sizeof(int));
        database_cart.read((char*)&ptr_product, sizeof(int));
        database_cart.read((char*)&number_orders, sizeof(int));
        database_product.seekg(ptr_product);
        database_product.read((char*)&product, sizeof(Product));
        prices[i]=product.get_price();
        sum_sell+=(number_orders*prices[i]);
        if(status_product(product,number_orders)!=3){
            database_cart.close();
            database_product.close();
            return 0;
        }
    }
    database_cart.close();
    database_product.close();
    return 1;
}

void cart::delete_cart()
{
    len_cart=0;
    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekp((clie.get_ID()-1)*(3*20+1)*sizeof(int));
    database_cart.write((char*)&len_cart, sizeof(int));
    database_cart.close();
    count=0;
    end_part_cart=0;
}

void cart::reserve_products()
{
    int type;
    int ptr_product;
    int number_orders;

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.get_ID()-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));

    fstream database_product(data_product,  ios::in | ios::out | ios::binary);

    for(int i=0;i<len_cart;i++){
        database_cart.read((char*)&type, sizeof(int));
        database_cart.read((char*)&ptr_product, sizeof(int));
        database_cart.read((char*)&number_orders, sizeof(int));

        database_product.seekg(ptr_product);
        database_product.read((char*)&product, sizeof(Product));
        product.set_available(product.get_available()-number_orders);
        database_product.seekp(ptr_product);
        database_product.write((char*)&product, sizeof(Product));

    }

    database_cart.close();
    database_product.close();
}

void cart::cansel_reserve_products()
{
    int type;
    int ptr_product;
    int number_orders;

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.get_ID()-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));

    fstream database_product(data_product,  ios::in | ios::out | ios::binary);

    for(int i=0;i<len_cart;i++){
        database_cart.read((char*)&type, sizeof(int));
        database_cart.read((char*)&ptr_product, sizeof(int));
        database_cart.read((char*)&number_orders, sizeof(int));

        database_product.seekg(ptr_product);
        database_product.read((char*)&product, sizeof(Product));
        product.set_available(product.get_available()+number_orders);
        database_product.seekp(ptr_product);
        database_product.write((char*)&product, sizeof(Product));
    }

    database_cart.close();
    database_product.close();
}

void cart::transaction_admin()
{
    Admin admin;
    fstream database_admin("admin.txt",ios::in | ios::out | ios::binary);
    admin.set_Wallet_balance(admin.get_Wallet_balance()+(sum_buy-sum_sell));
    database_admin.seekp(0);
    database_admin.write((char*)&admin, sizeof(Admin));
    database_admin.close();
}

void cart::on_pushButton_next_clicked()
{
    if(flag_cart==0 && get_number_orders()==0){
        save_number_orders();
    }
    next_to_cart(9);
    show_cart();
}

void cart::on_pushButton_prev_clicked()
{
    if(flag_cart==0 && get_number_orders()==0){
        save_number_orders();
    }
    preview_to_cart(9);
    show_cart();
}

void cart::on_pushButton_filter_3_clicked()
{
    if(get_number_orders()==0){
        save_number_orders();
        repet_to_cart(9);
        show_cart();
    }
    if(len_cart>0 && status_cart()==1){ 
        sum_buy=sum_sell+sum_sell*(0.01);
        reserve_products();
        flag_cart=1;
        show_cart();
    }
    else if(status_cart()==0){
        QMessageBox::warning(this, "اخطار", "تمام کالا های سبد خرید شما موجود نمی باشند");
    }
}

void cart::on_pushButton_filter_clicked()
{
    delete_cart();
    show_cart();
}

void cart::on_pushButton_filter_2_clicked()
{
    choosepay *payMethod = new choosepay(sum_buy,clie,this);
    payMethod->show();
    connect(payMethod, SIGNAL(send_method(bool)), this, SLOT(rec_method(bool)));//پرداخت مستقیم یا کیف پول شارژ
    connect(payMethod, SIGNAL(send_status_payment_from_wallet(bool)), this, SLOT(status_payment(bool)));//پرداخت از کیف پول
}

void cart::rec_method(bool method)
{
    if(method == 1)
    {
        //Show Payment GateWay Page
        PaymentGateWay *directpay = new PaymentGateWay(sum_buy, this);
        //this->hide();
        connect(directpay, SIGNAL(PaymentStatusOnThePaymentGateWayPage(bool)), this, SLOT(status_payment(bool)));
        directpay->show();
    }

    else//برروی دکمه شارژ کلیک شده
    {
        TopUpWallet *fromWallet = new TopUpWallet(clie, this);
        fromWallet->show();
    }
}

void cart::status_payment(bool m)
{
    this->show();
    if( m==1)//موفقیت
    {
        transaction_admin();
        add_to_factor();
        add_to_buys();
        add_to_sells();

        delete_cart();
        flag_cart=0;
        show_cart();
        QMessageBox::information(this, "توجه", "خرید با موفقیت انجام شد");
    }
}

void cart::on_pushButton_filter_4_clicked()
{
    cansel_reserve_products();
    flag_cart=0;
    show_cart();
}

void cart::on_pushButton_16_clicked()
{
    if(flag_cart==0){
        int andis = count - (end_part_cart-0);
        delete_product(andis);
        repet_to_cart(9);
        show_cart();
    }
}

void cart::on_pushButton_14_clicked()
{
    if(flag_cart==0){
        int andis = count - (end_part_cart-1);
        delete_product(andis);
        repet_to_cart(9);
        show_cart();
    }
}

void cart::on_pushButton_15_clicked()
{
    if(flag_cart==0){
        int andis = count - (end_part_cart-2);
        delete_product(andis);
        repet_to_cart(9);
        show_cart();
    }
}

void cart::on_pushButton_13_clicked()
{
    if(flag_cart==0){
        int andis = count - (end_part_cart-3);
        delete_product(andis);
        repet_to_cart(9);
        show_cart();
    }
}

void cart::on_pushButton_12_clicked()
{
    if(flag_cart==0){
        int andis = count - (end_part_cart-4);
        delete_product(andis);
        repet_to_cart(9);
        show_cart();
    }
}

void cart::on_pushButton_17_clicked()
{
    if(flag_cart==0){
        int andis = count - (end_part_cart-5);
        delete_product(andis);
        repet_to_cart(9);
        show_cart();
    }
}

void cart::on_pushButton_18_clicked()
{
    if(flag_cart==0){
        int andis = count - (end_part_cart-6);
        delete_product(andis);
        repet_to_cart(9);
        show_cart();
    }
}

void cart::on_pushButton_19_clicked()
{
    if(flag_cart==0){
        int andis = count - (end_part_cart-7);
        delete_product(andis);
        repet_to_cart(9);
        show_cart();
    }
}

void cart::on_pushButton_20_clicked()
{
    if(flag_cart==0){
        int andis = count - (end_part_cart-8);
        delete_product(andis);
        repet_to_cart(9);
        show_cart();
    }
}

void cart::on_pushButton_prev_2_clicked()
{
    this->close();
    goodsList *newlist = new goodsList(clie);


    newlist->show();
}

