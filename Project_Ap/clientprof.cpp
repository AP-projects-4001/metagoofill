#include "clientprof.h"
#include "ui_clientprof.h"


using namespace std;
clientProf::clientProf(client cli_info, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clientProf)
{
    ui->setupUi(this);
    clie = cli_info;// ذخیره شی در کلاس
    string temp;

    //set name.
    cli_info.char_array_to_string(temp, 16, cli_info.Name);
    ui->plainTextEdit_13->setPlainText(QString::fromStdString(temp));

    //set phonenumber.
    cli_info.char_array_to_string(temp, 12, cli_info.CellPhoneNumber);
    ui->plainTextEdit_5->setPlainText(QString::fromStdString(temp));

    //set city.
    cli_info.char_array_to_string(temp, 11, cli_info.city);
    ui->plainTextEdit_15->setPlainText(QString::fromStdString(temp));

    //set address.
    cli_info.char_array_to_string(temp, 31, cli_info.Address);
    ui->plainTextEdit_14->setPlainText(QString::fromStdString(temp));

    //set hidden password.
    temp = "*********";//ستاره به جای نمایش پسورد که بعدا باید تعدادش برابر با تعداد استرینگ پسورد باشد
    ui->plainTextEdit_17->setPlainText(QString::fromStdString(temp));

    //set username.
    cli_info.char_array_to_string(temp, 16, cli_info.User);
    ui->plainTextEdit_16->setPlainText(QString::fromStdString(temp));

}

clientProf::~clientProf()
{
    delete ui;
}

void clientProf::on_pushButton_8_clicked()
{
    //تغییر اطلاعات و ذخیره در فایل
}


void clientProf::on_pushButton_7_clicked()
{
    //رفتن به فروشگاه
    goodslist = new goodsList(this);
    this->hide();
    goodslist->hide();
    goodsGroup = new groupingGoods(goodslist);
    connect(goodsGroup, SIGNAL(close_page()), this, SLOT(showw()));
    connect(goodsGroup, SIGNAL(G_type(int)), goodslist, SLOT(recG_type(int)));
    goodsGroup->show();
}


void clientProf::on_pushButton_6_clicked()
{
    //مشاهده سوابق خرید
}


void clientProf::on_pushButton_4_clicked()
{
    //بازگشت به صفحه قبل
}

void clientProf::showw()
{
    this->show();
}

