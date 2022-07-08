#include "groupinggoods.h"
#include "ui_groupinggoods.h"
#include "clientprof.h"
#include "cart.h"


groupingGoods::groupingGoods(client _clie, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::groupingGoods)
{
    ui->setupUi(this);
    clie = _clie;
}

groupingGoods::~groupingGoods()
{
    delete ui;
}

void groupingGoods::on_technology_clicked()
{
    //استخراج و ارسال اطلاعات کالاهای تکنولوژی
    // یا ارسال کد هر دسته بندی
    this->hide();
    emit G_type(0);
}

void groupingGoods::on_homeApp_clicked()
{
    //استخراج و ارسال اطلاعات کالاهای خانه و آشپزخانه
    // یا ارسال کد هر دسته بندی
    this->hide();
    emit G_type(1);
}


void groupingGoods::on_clothes_clicked()
{
    //استخراج و ارسال اطلاعات کالای پوشاک
    //یا ارسال کد هر دسته بندی
    this->hide();
    emit G_type(2);
}

void groupingGoods::on_fruit_clicked()
{
    //استخراج و ارسال اطلاعات کالای میوه
    // یا ارسال کد هر دسته بندی
    this->hide();
    emit G_type(3);
}

void groupingGoods::on_supermarket_clicked()
{
    //استخراج و ارسال اطلاعات کالاهای سوپر مارکت
    // یا ارسال کد هر دسته بندی
    this->hide();
    emit G_type(4);
}

void groupingGoods::on_nuts_clicked()
{
    //استخراج و ارسال اطلاعات کالاهای خشکبار
    // یا ارسال کد هر دسته بندی
    this->hide();
    emit G_type(5);
}

void groupingGoods::on_popular_clicked()
{
    //استخراج و ارسال اطلاعات کالاهای پرفروش
    // یا ارسال کد هر دسته بندی
    this->hide();
    emit G_type(6);
}


void groupingGoods::on_profile_clicked()
{
    this->close();
    clientProf *reprof = new clientProf(clie);
    reprof->show();
}


void groupingGoods::on_cart_clicked()
{
    cart *newcart = new cart(clie);
    this->close();
    newcart->show();
}

