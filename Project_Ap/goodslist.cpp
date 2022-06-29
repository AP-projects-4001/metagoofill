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
#define data_product "database_products.txt"
using namespace std;
goodsList::goodsList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::goodsList)
{
    ui->setupUi(this);

    fstream database_search("database_search.txt",ios::app | ios::binary);
    database_search.close();
}

goodsList::~goodsList()
{
    delete ui;
}

void goodsList::recG_type(int G_type)
{
    type = G_type;
    this->show();
    search_by_filter();
    next_to_search(9);
    show_list_products();

}

void goodsList::on_pushButton_filter_clicked()
{

   if(type == 0)
   {
       tech_filter *filter_0 = new tech_filter(this);//add product class array to constructor.
       filter_0->show();
       this->hide();
       connect(filter_0, SIGNAL(send_tech_info(other_filter_info)), this, SLOT(rec_tech_info(other_filter_info)));
   }

   else if(type == 1)
   {
        homeApps_filter *filter_1 = new homeApps_filter(this);
        filter_1->show();
        this->hide();
        connect(filter_1, SIGNAL(send_homeapp_info(other_filter_info)), this, SLOT(rec_tech_info(other_filter_info)));


   }

   else if(type == 2)
   {
       clothes_filter *filter_2 = new clothes_filter(this);
       filter_2->show();
       this->hide();
       connect(filter_2, SIGNAL(send_clothes_info(clothes_filter_info)), this, SLOT(rec_clothes_info(clothes_filter_info)));
   }

   else if(type == 3)
   {
       fruitandveg_filter *filter_3 = new fruitandveg_filter(this);
       filter_3->show();
       this->hide();
       connect(filter_3, SIGNAL(send_fruit_info(fruits_filter_info)), this, SLOT(rec_fruits_info(fruits_filter_info)));
   }

   else if(type == 4)
   {
       super_filter *filter_4 = new super_filter(this);
       filter_4->show();
       this->hide();
       connect(filter_4, SIGNAL(send_super_info(other_filter_info)), this, SLOT(rec_tech_info(other_filter_info)));

   }

   else if(type == 5)
   {
       fruitandveg_filter *filter_5 = new fruitandveg_filter(this);
       filter_5->show();
       this->hide();
       connect(filter_5, SIGNAL(send_fruit_info(fruits_filter_info)), this, SLOT(rec_fruits_info(fruits_filter_info)));

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

       //کار با فایل
}

void goodsList::rec_fruit_info(fruitandveg_filter_info fruit_info)
{
    fruit_info_2 = fruit_info;
    this->show();

    //کار با فایل
}

void goodsList::rec_other_info(others_filter_info other_info)
{
    other_info_2 = other_info;
    this->show();

    //کار با فایل
}

void goodsList::search_by_filter()//
{
    int ptr_start_file_product_type;
    int ptr_end_file_product_type;
    int number_product_type;
    int ptr_file;


    fstream  database_product_type("database_product_type.txt",ios::in | ios::out | ios::binary);
    database_product_type.seekg(type*3*sizeof(int));
    database_product_type.read((char*)&ptr_start_file_product_type,sizeof(int));
    database_product_type.read((char*)&ptr_end_file_product_type, sizeof(int));
    database_product_type.read((char*)&number_product_type, sizeof(int));


    fstream database_product(data_product,ios::in | ios::out | ios::binary);
    fstream database_search("database_search.txt",ios::in | ios::out | ios::binary);

    len_search=0;
    database_search.seekp(0);
    ptr_file=ptr_start_file_product_type;
    for(int i=0;i<number_product_type;i++){
        database_product.seekg(ptr_file);
        database_product.read((char*)&product, sizeof(Product));
        if(filter()==1){
            database_search.write((char *)&ptr_file, sizeof(int));
            len_search++;
        }
        ptr_file=product.ptr_file_product_type_next;
    }

}

void goodsList::next_to_search(int part)
{
    int ptr_file;
    int count=0;
    if(count!=len_search){
        fstream database_product(data_product,ios::in | ios::out | ios::binary);
        fstream database_search("database_search.txt",ios::in | ios::out | ios::binary);

        database_search.seekg((count)*sizeof(int));
        end_part_products=len_search-count;
        if(end_part_products>=part-1){end_part_products=part;}
        for(int i=0;i<end_part_products;i++){
            database_search.read((char *)&ptr_file, sizeof(int));
            database_product.seekg(ptr_file);
            database_product.read((char*)&products[i], sizeof(Product));
        }
        count+=end_part_products;
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

        database_search.seekg((count)*sizeof(int));

        for(int i=0;i<part;i++){
            database_search.read((char *)&ptr_file, sizeof(int));
            database_product.seekg(ptr_file);
            database_product.read((char*)&products[i], sizeof(Product));
        }
        count+=part;
    }
}

bool goodsList::filter()
{

    if(type==0){

    }
    else if(type==1){

    }
    else if(type==2){

    }
    else if(type==3){

    }
    else if(type==4){

    }
    else if(type==5){

    }
    return 1;
}

void goodsList::show_list_products()
{
    string str;
    product.char_array_to_string(str,16,products[0].type);
    ui->label_type_0->setText(QString::fromStdString(str));
    ui->label_price_10->setText(QString::number(products[0].price));

    product.char_array_to_string(str,16,products[1].type);
    ui->label_type_1->setText(QString::fromStdString(str));
    ui->label_price_11->setText(QString::number(products[1].price));

    product.char_array_to_string(str,16,products[2].type);
    ui->label_type_2->setText(QString::fromStdString(str));
    ui->label_price_12->setText(QString::number(products[2].price));

    product.char_array_to_string(str,16,products[3].type);
    ui->label_type_3->setText(QString::fromStdString(str));
    ui->label_price_13->setText(QString::number(products[3].price));

    product.char_array_to_string(str,16,products[4].type);
    ui->label_type_4->setText(QString::fromStdString(str));
    ui->label_price_14->setText(QString::number(products[4].price));

    product.char_array_to_string(str,16,products[5].type);
    ui->label_type_5->setText(QString::fromStdString(str));
    ui->label_price_15->setText(QString::number(products[5].price));

    product.char_array_to_string(str,16,products[6].type);
    ui->label_type_6->setText(QString::fromStdString(str));
    ui->label_price_16->setText(QString::number(products[6].price));

    product.char_array_to_string(str,16,products[7].type);
    ui->label_type_7->setText(QString::fromStdString(str));
    ui->label_price_17->setText(QString::number(products[7].price));

    product.char_array_to_string(str,16,products[8].type);
    ui->label_type_8->setText(QString::fromStdString(str));
    ui->label_price_18->setText(QString::number(products[8].price));

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



void goodsList::on_pushButton_filter_3_clicked()//for return from goodslist to groupinggoods
{
//    this->hide();
//    groupingGoods *groups = new groupingGoods(this);
//    groups->show();
}


void goodsList::on_pushButton_filter_2_clicked()
{
    //go to cart(sabad kharid)
    this->hide();
    cart *_cart = new cart(this);
    _cart->show();
    //باید بعد از ایجاد ساختار سبد خرید تغییر کند. زیرا با این روش فقط پتانسیل خرید یک دسته بندی از کالا وجود دارد

}

