#include "goodslist.h"
#include "ui_goodslist.h"
#include "tech_filter.h"
#include "homeapps_filter.h"
#include "clothes_filter.h"
#include "fruitandveg_filter.h"
#include "super_filter.h"
#include "groupinggoods.h"
#include "cart.h"
#include <fstream>
#include <QMessageBox>
#include "groupinggoods.h"
#include "clientprof.h"
#define data_product "database_products.txt"

using namespace std;
goodsList::goodsList(client _clie ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::goodsList)
{
    ui->setupUi(this);

    clie=_clie;

    groupingGoods *goodsGroup = new groupingGoods(clie, this);
    connect(goodsGroup, SIGNAL(G_type(int)), this, SLOT(recG_type(int)));
    goodsGroup->show();
    this->hide();

}

goodsList::~goodsList()
{
    delete_search();
    delete ui;
}

void goodsList::recG_type(int G_type)
{
    type = G_type;
    this->show();
    flag_filter=0;
    search_by_filter_in_products();
    next_to_search(9);
    show_list_products();
}

void goodsList::on_pushButton_filter_clicked()
{

   if(type == 0)
   {
       tech_filter *filter_0 = new tech_filter(this);//add product class array to constructor.
       filter_0->show();
       //this->hide();
       connect(filter_0, SIGNAL(send_tech_info(others_filter_info)), this, SLOT(rec_other_info(others_filter_info)));
   }

   else if(type == 1)
   {
        homeApps_filter *filter_1 = new homeApps_filter(this);
        filter_1->show();
        //this->hide();
        connect(filter_1, SIGNAL(send_homeapp_info(others_filter_info)), this, SLOT(rec_other_info(others_filter_info)));
   }

   else if(type == 2)
   {
       clothes_filter *filter_2 = new clothes_filter(this);
       filter_2->show();
       //this->hide();
       connect(filter_2, SIGNAL(send_clothes_info(clothes_filter_info)), this, SLOT(rec_clothes_info(clothes_filter_info)));
   }

   else if(type == 3)
   {
       fruitandveg_filter *filter_3 = new fruitandveg_filter(this);
       filter_3->show();
       //this->hide();
       connect(filter_3, SIGNAL(send_fruits_info(fruitandveg_filter_info)), this, SLOT(rec_fruit_info(fruitandveg_filter_info)));
   }

   else if(type == 4)
   {
       super_filter *filter_4 = new super_filter(this);
       filter_4->show();
       //this->hide();
       connect(filter_4, SIGNAL(send_super_info(others_filter_info)), this, SLOT(rec_other_info(others_filter_info)));

   }

   else if(type == 5)
   {
       fruitandveg_filter *filter_5 = new fruitandveg_filter(this);
       filter_5->show();
       //this->hide();
       connect(filter_5, SIGNAL(send_fruits_info(fruitandveg_filter_info)), this, SLOT(rec_fruit_info(fruitandveg_filter_info)));

   }

//   else if(type == 6)
//   {
//       //همه ی ۲۰ کالای پر فروش
   //   }
}

void goodsList::rec_clothes_info(clothes_filter_info clothes_info)
{
     clothes_info_2 = clothes_info;
     this->show();
     delete_search();
     flag_filter=1;
     search_by_filter_in_products();
     next_to_search(9);
     show_list_products();
}

void goodsList::rec_fruit_info(fruitandveg_filter_info fruit_info)
{
    fruit_info_2 = fruit_info;
    this->show();
    delete_search();
    flag_filter=1;
    search_by_filter_in_products();
    next_to_search(9);
    show_list_products();
}

void goodsList::rec_other_info(others_filter_info other_info)
{
    other_info_2 = other_info;
    this->show();
    delete_search();
    flag_filter=1;
    search_by_filter_in_products();
    next_to_search(9);
    show_list_products();
}

void goodsList::search_by_filter_in_products()
{
    int ptr_start_file_product_type;
    int ptr_end_file_product_type;
    int number_product_type;
    int ptr_file;

    fstream database_numbers("numbers.txt", ios::in | ios::out | ios::binary);
    database_numbers.seekg((6-1)*sizeof(int));
    database_numbers.read((char*)&number_search, sizeof(int));
    number_search++;
    database_numbers.seekp((6-1)*sizeof(int));
    database_numbers.write((char*)&number_search, sizeof(int));

    database_numbers.seekg((5-1)*sizeof(int));
    database_numbers.read((char*)&start_search, sizeof(int));

    fstream  database_product_type("database_product_type.txt",ios::in | ios::out | ios::binary);
    database_product_type.seekg(type*3*sizeof(int));
    database_product_type.read((char*)&ptr_start_file_product_type,sizeof(int));
    database_product_type.read((char*)&ptr_end_file_product_type, sizeof(int));
    database_product_type.read((char*)&number_product_type, sizeof(int));

    fstream database_product(data_product,ios::in | ios::out | ios::binary);
    fstream database_search("database_search.txt",ios::in | ios::out | ios::binary);

    len_search=0;
    database_search.seekp(start_search);
    ptr_file=ptr_start_file_product_type;
    for(int i=0;i<number_product_type;i++){
        database_product.seekg(ptr_file);
        database_product.read((char*)&product, sizeof(Product));
        if(filter()==1){
            database_search.write((char *)&ptr_file, sizeof(int));
            len_search++;
        }
        ptr_file=product.get_ptr_file_product_type_next();
    }
    count=0;
    end_part_products = 0;

    start_search+=len_search;
    database_numbers.seekp((5-1)*sizeof(int));
    database_numbers.write((char*)&start_search, sizeof(int));
    database_numbers.close();
    start_search-=len_search;

    database_product.close();
    database_search.close();
    database_product_type.close();
}

void goodsList::delete_search()
{
    fstream database_numbers("numbers.txt", ios::in | ios::out | ios::binary);
    database_numbers.seekg((6-1)*sizeof(int));
    database_numbers.read((char*)&number_search, sizeof(int));
    number_search--;
    database_numbers.seekp((6-1)*sizeof(int));
    database_numbers.write((char*)&number_search, sizeof(int));
    if(number_search==0){
        start_search=0;
        database_numbers.seekp((5-1)*sizeof(int));
        database_numbers.write((char*)&start_search, sizeof(int));
    }
    database_numbers.close();
}

void goodsList::next_to_search(int part)
{
    int ptr_file;
    if(count!=len_search){
        fstream database_product(data_product,ios::in | ios::out | ios::binary);
        fstream database_search("database_search.txt",ios::in | ios::out | ios::binary);

        database_search.seekg(start_search+(count)*sizeof(int));
        end_part_products=len_search-count;
        if(end_part_products>=part){end_part_products=part;}
        for(int i=0;i<end_part_products;i++){
            database_search.read((char *)&ptr_file, sizeof(int));
            database_product.seekg(ptr_file);
            database_product.read((char*)&products[i], sizeof(Product));
        }
        count+=end_part_products;

        database_product.close();
        database_search.close();
    }
}

void goodsList::preview_to_search(int part)
{
    int ptr_file;

    if(count>=(end_part_products+part)){
        count-=end_part_products;
        count-=part;
        end_part_products=part;
        fstream database_product(data_product,ios::in | ios::out | ios::binary);
        fstream database_search("database_search.txt",ios::in | ios::out | ios::binary);

        database_search.seekg(start_search+(count)*sizeof(int));
        for(int i=0;i<end_part_products;i++){
            database_search.read((char *)&ptr_file, sizeof(int));
            database_product.seekg(ptr_file);
            database_product.read((char*)&products[i], sizeof(Product));
        }
        count+=end_part_products;

        database_product.close();
        database_search.close();
    }
}

bool goodsList::filter()
{
    customer cust;
    string str;
    fstream database_customers("customers.txt", ios::in | ios::out | ios::binary);
    if(product.get_flag_delete_product()==1){return 0;}
    if(flag_filter==1){
        if(type==0 || type==1 || type==4){

            if(other_info_2.get_price_from()!=""){
                if(product.get_price()<stoi(other_info_2.get_price_from())){return 0;}
            }
            if(other_info_2.get_price_to()!=""){
                if(product.get_price()>stoi(other_info_2.get_price_to())){return 0;}
            }
            product.char_array_to_string(str,16,product.get_type());
            if(other_info_2.get_name_prod()!="" && other_info_2.get_name_prod()!=str){return 0;}

            product.char_array_to_string(str,16,product.get_color());
            if(other_info_2.get_color()!="" && (other_info_2.get_color()!=str || product.get_flag_color()==0)){return 0;}

            database_customers.seekg((product.get_ID_customer()-1)*sizeof(customer));
            database_customers.read((char*)&cust,sizeof(customer));
            cust.char_array_to_string(str,16,cust.get_Name());
            if(other_info_2.get_customer_name()!="" && other_info_2.get_customer_name()!=str){return 0;}

        }
        else if(type==3 || type==5){

            if(fruit_info_2.get_price_from()!=""){
                if(product.get_price()<stoi(fruit_info_2.get_price_from())){return 0;}
            }
            if(fruit_info_2.get_price_to()!=""){
                if(product.get_price()>stoi(fruit_info_2.get_price_to())){return 0;}
            }
            product.char_array_to_string(str,16,product.get_type());
            if(fruit_info_2.get_name_prod()!="" && fruit_info_2.get_name_prod()!=str){return 0;}

            product.char_array_to_string(str,16,product.get_color());
            if(fruit_info_2.get_color()!="" && (fruit_info_2.get_color()!=str || product.get_flag_color()==0 )){return 0;}

            database_customers.seekg((product.get_ID_customer()-1)*sizeof(customer));
            database_customers.read((char*)&cust,sizeof(customer));
            cust.char_array_to_string(str,16,cust.get_Name());
            if(fruit_info_2.get_customer_name()!="" && fruit_info_2.get_customer_name()!=str){return 0;}

        }
        else if(type==2){

            if(clothes_info_2.get_price_from()!=""){
                if(product.get_price()<stoi(clothes_info_2.get_price_from())){return 0;}
            }
            if(clothes_info_2.get_price_to()!=""){
                if(product.get_price()>stoi(clothes_info_2.get_price_to())){return 0;}
            }
            product.char_array_to_string(str,16,product.get_type());
            if(clothes_info_2.get_name_prod()!="" && clothes_info_2.get_name_prod()!=str){return 0;}

            product.char_array_to_string(str,16,product.get_color());
            if(clothes_info_2.get_color()!="" && (clothes_info_2.get_color()!=str || product.get_flag_color()==0)){return 0;}

            database_customers.seekg((product.get_ID_customer()-1)*sizeof(customer));
            database_customers.read((char*)&cust,sizeof(customer));
            cust.char_array_to_string(str,16,cust.get_Name());
            if(clothes_info_2.get_customer_name()!="" && clothes_info_2.get_customer_name()!=str){return 0;}

        }
    }
    database_customers.close();
    return 1;
}

void goodsList::show_list_products()//first index is 1;
{
    string str;
    if(end_part_products >= 1) {
        ui->label_type_10->show();
        ui->label_price_10->show();
        ui->pushButton_16->show();
        ui->pushButton_g1->show();
        ui->spinBox_1->show();
        ui->spinBox_1->setValue(0);
        product.char_array_to_string(str,16,products[0].get_type());
        ui->label_type_10->setText(QString::fromStdString(str));
        ui->label_price_10->setText(QString::number(products[0].get_price()));
    }
    else {
        ui->label_type_10->hide();
        ui->label_price_10->hide();
        ui->pushButton_16->hide();
        ui->pushButton_g1->hide();
        ui->spinBox_1->hide();
    }

    if(end_part_products >= 2) {
        ui->label_type_11->show();
        ui->label_price_11->show();
        ui->pushButton_14->show();
        ui->pushButton_g2->show();
        ui->spinBox_2->show();
        ui->spinBox_2->setValue(0);
        product.char_array_to_string(str,16,products[1].get_type());
        ui->label_type_11->setText(QString::fromStdString(str));
        ui->label_price_11->setText(QString::number(products[1].get_price()));
    }
    else {
        ui->label_type_11->hide();
        ui->label_price_11->hide();
        ui->pushButton_14->hide();
        ui->pushButton_g2->hide();
        ui->spinBox_2->hide();
    }

    if(end_part_products >= 3) {
        ui->label_type_12->show();
        ui->label_price_12->show();
        ui->pushButton_15->show();
        ui->pushButton_g3->show();
        ui->spinBox_3->show();
        ui->spinBox_3->setValue(0);
        product.char_array_to_string(str,16,products[2].get_type());
        ui->label_type_12->setText(QString::fromStdString(str));
        ui->label_price_12->setText(QString::number(products[2].get_price()));
    }
    else {
        ui->label_type_12->hide();
        ui->label_price_12->hide();
        ui->pushButton_15->hide();
        ui->pushButton_g3->hide();
        ui->spinBox_3->hide();
    }

    if(end_part_products >= 4) {
        ui->label_type_13->show();
        ui->label_price_13->show();
        ui->pushButton_13->show();
        ui->pushButton_g4->show();
        ui->spinBox_4->show();
        ui->spinBox_4->setValue(0);
        product.char_array_to_string(str,16,products[3].get_type());
        ui->label_type_13->setText(QString::fromStdString(str));
        ui->label_price_13->setText(QString::number(products[3].get_price()));
    }
    else {
        ui->label_type_13->hide();
        ui->label_price_13->hide();
        ui->pushButton_13->hide();
        ui->pushButton_g4->hide();
        ui->spinBox_4->hide();
    }

    if(end_part_products >= 5) {
        ui->label_type_14->show();
        ui->label_price_14->show();
        ui->pushButton_12->show();
        ui->pushButton_g5->show();
        ui->spinBox_5->show();
        ui->spinBox_5->setValue(0);
        product.char_array_to_string(str,16,products[4].get_type());
        ui->label_type_14->setText(QString::fromStdString(str));
        ui->label_price_14->setText(QString::number(products[4].get_price()));
    }
    else {
        ui->label_type_14->hide();
        ui->label_price_14->hide();
        ui->pushButton_12->hide();
        ui->pushButton_g5->hide();
        ui->spinBox_5->hide();
    }

    if(end_part_products >= 6) {
        ui->label_type_15->show();
        ui->label_price_15->show();
        ui->pushButton_17->show();
        ui->pushButton_g6->show();
        ui->spinBox_6->show();
        ui->spinBox_6->setValue(0);
        product.char_array_to_string(str,16,products[5].get_type());
        ui->label_type_15->setText(QString::fromStdString(str));
        ui->label_price_15->setText(QString::number(products[5].get_price()));
    }
    else {
        ui->label_type_15->hide();
        ui->label_price_15->hide();
        ui->pushButton_17->hide();
        ui->pushButton_g6->hide();
        ui->spinBox_6->hide();
    }

    if(end_part_products >= 7) {
        ui->label_type_16->show();
        ui->label_price_16->show();
        ui->pushButton_18->show();
        ui->pushButton_g7->show();
        ui->spinBox_7->show();
        ui->spinBox_7->setValue(0);
        product.char_array_to_string(str,16,products[6].get_type());
        ui->label_type_16->setText(QString::fromStdString(str));
        ui->label_price_16->setText(QString::number(products[6].get_price()));
    }
    else {
        ui->label_type_16->hide();
        ui->label_price_16->hide();
        ui->pushButton_18->hide();
        ui->pushButton_g7->hide();
        ui->spinBox_7->hide();
    }

    if(end_part_products >= 8) {
        ui->label_type_17->show();
        ui->label_price_17->show();
        ui->pushButton_19->show();
        ui->pushButton_g8->show();
        ui->spinBox_8->show();
        ui->spinBox_8->setValue(0);
        product.char_array_to_string(str,16,products[7].get_type());
        ui->label_type_17->setText(QString::fromStdString(str));
        ui->label_price_17->setText(QString::number(products[7].get_price()));
    }
    else {
        ui->label_type_17->hide();
        ui->label_price_17->hide();
        ui->pushButton_19->hide();
        ui->pushButton_g8->hide();
        ui->spinBox_8->hide();
    }

    if(end_part_products >= 9) {
        ui->label_type_18->show();
        ui->label_price_18->show();
        ui->pushButton_20->show();
        ui->pushButton_g9->show();
        ui->spinBox_9->show();
        ui->spinBox_9->setValue(0);
        product.char_array_to_string(str,16,products[8].get_type());
        ui->label_type_18->setText(QString::fromStdString(str));
        ui->label_price_18->setText(QString::number(products[8].get_price()));
    }
    else {
        ui->label_type_18->hide();
        ui->label_price_18->hide();
        ui->pushButton_20->hide();
        ui->pushButton_g9->hide();
        ui->spinBox_9->hide();
    }
}


void goodsList::on_pushButton_next_clicked()
{
    next_to_search(9);
    show_list_products();
}


void goodsList::on_pushButton_prev_clicked()
{
    preview_to_search(9);
    show_list_products();
}



void goodsList::on_pushButton_g1_clicked()
{
    details = new goodDetails(products[0], this);
    details->show();
}

void goodsList::on_pushButton_g2_clicked()
{
    details = new goodDetails(products[1], this);
    details->show();
}

void goodsList::on_pushButton_g3_clicked()
{
    details = new goodDetails(products[2], this);
    details->show();
}

void goodsList::on_pushButton_g4_clicked()
{
    details = new goodDetails(products[3], this);
    details->show();
}

void goodsList::on_pushButton_g5_clicked()
{
    details = new goodDetails(products[4], this);
    details->show();
}

void goodsList::on_pushButton_g6_clicked()
{
    details = new goodDetails(products[5], this);
    details->show();
}

void goodsList::on_pushButton_g7_clicked()
{
    details = new goodDetails(products[6], this);
    details->show();
}

void goodsList::on_pushButton_g8_clicked()
{
    details = new goodDetails(products[7], this);
    details->show();
}

void goodsList::on_pushButton_g9_clicked()
{
    details = new goodDetails(products[8], this);
    details->show();
}



void goodsList::on_pushButton_filter_3_clicked()//
{
//    this->hide();
//    groupingGoods *groups = new groupingGoods();
//    groups->show();
    delete_search();
    this->close();
    clientProf *reprof = new clientProf(clie);
    reprof->show();
}


void goodsList::on_pushButton_filter_2_clicked()
{
    //go to cart(sabad kharid)
    delete_search();
    this->close();
    cart *_cart = new cart(clie);
    _cart->show();
}

bool goodsList::add_to_cart(int andis,int number_orders)
{
    int len_cart;
    int ptr_product;

    fstream database_product(data_product,ios::in | ios::out | ios::binary);
    fstream database_search("database_search.txt",ios::in | ios::out | ios::binary);

    fstream  database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekg((clie.get_ID()-1)*(3*20+1)*sizeof(int));
    database_cart.read((char*)&len_cart, sizeof(int));

    if(len_cart<20){
        database_search.seekg(start_search+(andis)*sizeof(int));
        database_search.read((char*)&ptr_product,sizeof(int));
        database_cart.seekp(len_cart*3*sizeof(int),ios::cur);
        database_cart.write((char*)&type, sizeof(int));
        database_cart.write((char*)&ptr_product, sizeof(int));
        database_cart.write((char*)&number_orders, sizeof(int));

        len_cart++;
        database_cart.seekp((clie.get_ID()-1)*(3*20+1)*sizeof(int));
        database_cart.write((char*)&len_cart, sizeof(int));
        return 1;
    }
    else{
        return 0;
    }

    database_cart.close();
    database_search.close();
    database_product.close();
}

void goodsList::on_pushButton_16_clicked()
{
    int andis = count - (end_part_products-0);
    if(ui->spinBox_1->value()==0){}
    else if(add_to_cart(andis,ui->spinBox_1->value())==0)
        QMessageBox::warning(this,"توجه","سبد محصول پر شده لطفا ابتدا سبد را پرداخت کنید");
    else
        QMessageBox::information(this,"توجه","کالا با موفقیت اضافه شد");
}

void goodsList::on_pushButton_14_clicked()
{
    int andis = count - (end_part_products-1);
    if(ui->spinBox_2->value()==0){}
    else if(add_to_cart(andis,ui->spinBox_2->value())==0)
        QMessageBox::warning(this,"توجه","سبد محصول پر شده لطفا ابتدا سبد را پرداخت کنید");
    else
        QMessageBox::information(this,"توجه","کالا با موفقیت اضافه شد");
}

void goodsList::on_pushButton_15_clicked()
{
    int andis = count - (end_part_products-2);
    if(ui->spinBox_3->value()==0){}
    else if(add_to_cart(andis,ui->spinBox_3->value())==0)
        QMessageBox::warning(this,"توجه","سبد محصول پر شده لطفا ابتدا سبد را پرداخت کنید");
    else
        QMessageBox::information(this,"توجه","کالا با موفقیت اضافه شد");
}

void goodsList::on_pushButton_13_clicked()
{
    int andis = count - (end_part_products-3);
    if(ui->spinBox_4->value()==0){}
    else if(add_to_cart(andis,ui->spinBox_4->value())==0)
        QMessageBox::warning(this,"توجه","سبد محصول پر شده لطفا ابتدا سبد را پرداخت کنید");
    else
        QMessageBox::information(this,"توجه","کالا با موفقیت اضافه شد");
}

void goodsList::on_pushButton_12_clicked()
{
    int andis = count - (end_part_products-4);
    if(ui->spinBox_5->value()==0){}
    else if(add_to_cart(andis,ui->spinBox_5->value())==0)
        QMessageBox::warning(this,"توجه","سبد محصول پر شده لطفا ابتدا سبد را پرداخت کنید");
    else
        QMessageBox::information(this,"توجه","کالا با موفقیت اضافه شد");
}

void goodsList::on_pushButton_17_clicked()
{
    int andis = count - (end_part_products-5);
    if(ui->spinBox_6->value()==0){}
    else if(add_to_cart(andis,ui->spinBox_6->value())==0)
        QMessageBox::warning(this,"توجه","سبد محصول پر شده لطفا ابتدا سبد را پرداخت کنید");
    else
        QMessageBox::information(this,"توجه","کالا با موفقیت اضافه شد");
}

void goodsList::on_pushButton_18_clicked()
{
    int andis = count - (end_part_products-6);
    if(ui->spinBox_7->value()==0){}
    else if(add_to_cart(andis,ui->spinBox_7->value())==0)
        QMessageBox::warning(this,"توجه","سبد محصول پر شده لطفا ابتدا سبد را پرداخت کنید");
    else
        QMessageBox::information(this,"توجه","کالا با موفقیت اضافه شد");
}

void goodsList::on_pushButton_19_clicked()
{
    int andis = count - (end_part_products-7);
    if(ui->spinBox_8->value()==0){}
    else if(add_to_cart(andis,ui->spinBox_8->value())==0)
        QMessageBox::warning(this,"توجه","سبد محصول پر شده لطفا ابتدا سبد را پرداخت کنید");
    else
        QMessageBox::information(this,"توجه","کالا با موفقیت اضافه شد");
}

void goodsList::on_pushButton_20_clicked()
{
    int andis = count - (end_part_products-8);
    if(ui->spinBox_9->value()==0){}
    else if(add_to_cart(andis,ui->spinBox_9->value())==0)
        QMessageBox::warning(this,"توجه","سبد محصول پر شده لطفا ابتدا سبد را پرداخت کنید");
    else
        QMessageBox::information(this,"توجه","کالا با موفقیت اضافه شد");
}

void goodsList::on_pushButton_filter_4_clicked()
{
    delete_search();
    groupingGoods *goodsGroup = new groupingGoods(clie, this);
    connect(goodsGroup, SIGNAL(G_type(int)), this, SLOT(recG_type(int)));
    goodsGroup->show();
    this->hide();
}

void goodsList::on_pushButton_filter_5_clicked()
{
    if(flag_filter==1){
        delete_search();
        flag_filter=0;
        search_by_filter_in_products();
        next_to_search(9);
        show_list_products();
    }
}

void goodsList::on_pushButton_filter_6_clicked()
{
    delete_search();
    search_by_filter_in_products();
    next_to_search(9);
    show_list_products();
}
