#include "goodslist.h"
#include "ui_goodslist.h"
#include "tech_filter.h"
#include "homeapps_filter.h"
#include "clothes_filter.h"
#include "fruitandveg_filter.h"
#include "super_filter.h"

goodsList::goodsList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::goodsList)
{
    ui->setupUi(this);
}

goodsList::~goodsList()
{
    delete ui;
}

void goodsList::recG_type(int G_type)
{
    type = G_type;
    this->show();
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


//void goodsList::on_pushButton_next_clicked()
//{

//}


//void goodsList::on_pushButton_prev_clicked()
//{

//}

