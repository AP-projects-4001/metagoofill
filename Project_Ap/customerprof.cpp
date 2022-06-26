#include "customerprof.h"
#include "ui_customerprof.h"
#include <fstream>
#include <cstring>
using namespace std;

customerProf::customerProf(customer cus_info, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::customerProf)
{
    ui->setupUi(this);
    string temp;
    cus_info.char_array_to_string(temp, 16, cus_info.Name);
    ui->plainTextEdit_2->setPlainText(QString::fromStdString(temp));

    cus_info.char_array_to_string(temp, 12, cus_info.PhoneNumber);
    ui->plainTextEdit->setPlainText(QString::fromStdString(temp));

    cus_info.char_array_to_string(temp, 31, cus_info.city);//در فیلد آدرس وارد می شود
    ui->plainTextEdit_6->setPlainText(QString::fromStdString(temp));

    std::string tmp(1, cus_info.ProductType);
    ui->plainTextEdit_7->setPlainText(QString::fromStdString(tmp));

//    cus_info.char_array_to_string(temp, 11, cus_info.Password);
    temp = "*********";//ستاره به جای نمایش پسورد که بعدا باید تعدادش برابر با تعداد استرینگ پسورد باشد
    ui->plainTextEdit_3->setPlainText(QString::fromStdString(temp));

    cus_info.char_array_to_string(temp, 16, cus_info.User);
    ui->plainTextEdit_5->setPlainText(QString::fromStdString(temp));
}

customerProf::~customerProf()
{
    delete ui;
}

void customerProf::on_pushButton_4_clicked()
{
    //تغییر اطلاعات و ذخیره در فایل
}

