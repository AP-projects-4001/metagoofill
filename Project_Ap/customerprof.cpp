#include "customerprof.h"
#include "ui_customerprof.h"
#include <fstream>
#include <cstring>
#include "storecustomer.h"
#include "salesrecords.h"
#include "loginpage.h"

using namespace std;

customerProf::customerProf(customer _cust, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::customerProf)
{
    ui->setupUi(this);
    cust = _cust;// ذخیره شی در کلاس
    show_prof();
}

customerProf::~customerProf()
{
    delete ui;
}

void customerProf::show_prof()
{
    string temp;
    cust.char_array_to_string(temp, 16, cust.get_Name());
    ui->plainTextEdit_2->setPlainText(QString::fromStdString(temp));

    cust.char_array_to_string(temp, 12, cust.get_phoneNumber());
    ui->plainTextEdit->setPlainText(QString::fromStdString(temp));

    cust.char_array_to_string(temp, 31, cust.get_city());//در فیلد آدرس وارد می شود
    ui->plainTextEdit_6->setPlainText(QString::fromStdString(temp));

    ui->plainTextEdit_7->setPlainText(QString::number(cust.get_ProductType()));

    temp = "*********";//ستاره به جای نمایش پسورد که بعدا باید تعدادش برابر با تعداد استرینگ پسورد باشد
    ui->label_2->setText(QString::fromStdString(temp));

    cust.char_array_to_string(temp, 16, cust.get_User());
    ui->plainTextEdit_5->setPlainText(QString::fromStdString(temp));
}

void customerProf::on_pushButton_4_clicked()
{
    //تغییر اطلاعات و ذخیره در فایل

    fstream database_customers("customers.txt", ios::in | ios::out | ios::binary);
    database_customers.seekg((cust.get_ID()-1)*sizeof(customer));
    database_customers.read((char*)&cust,sizeof(customer));

    cust.string_to_char_array(cust.get_Name(), 16, ui->plainTextEdit_2->toPlainText().toStdString());
    cust.string_to_char_array(cust.get_phoneNumber(), 12, ui->plainTextEdit->toPlainText().toStdString());
    cust.string_to_char_array(cust.get_city(), 11, ui->plainTextEdit_6->toPlainText().toStdString());
    cust.set_ProductType(cust.get_ProductType());
    cust.string_to_char_array(cust.get_User(), 16, ui->plainTextEdit_5->toPlainText().toStdString());
    cust.set_access( '1');

    database_customers.seekp((cust.get_ID()-1)*sizeof(customer));
    database_customers.write((char*)&cust,sizeof(customer));
    database_customers.close();

    show_prof();
}


void customerProf::on_pushButton_2_clicked()
{
    storecustomer *d=new storecustomer(cust);
    d->show();
    this->close();
}

void customerProf::on_pushButton_clicked()
{
    SalesRecords *salesrecords=new SalesRecords(cust,this);
    salesrecords->show();
    this->hide();
}

void customerProf::on_pushButton_5_clicked()
{
    this->close();
    LoginPage *relogin = new LoginPage(1);
    relogin->show();
}

