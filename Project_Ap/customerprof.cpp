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
    string temp;
    cust.char_array_to_string(temp, 16, cust.get_Name());
    ui->plainTextEdit_2->setPlainText(QString::fromStdString(temp));

    cust.char_array_to_string(temp, 12, cust.get_phoneNumber());
    ui->plainTextEdit->setPlainText(QString::fromStdString(temp));

    cust.char_array_to_string(temp, 31, cust.get_city());//در فیلد آدرس وارد می شود
    ui->plainTextEdit_6->setPlainText(QString::fromStdString(temp));

//    std::string tmp(1, cus_info.ProductType);
    ui->plainTextEdit_7->setPlainText(QString::number(cust.get_ProductType()));

//    cus_info.char_array_to_string(temp, 11, cus_info.Password);
    temp = "*********";//ستاره به جای نمایش پسورد که بعدا باید تعدادش برابر با تعداد استرینگ پسورد باشد
    ui->label_2->setText(QString::fromStdString(temp));

    cust.char_array_to_string(temp, 16, cust.get_User());
    ui->plainTextEdit_5->setPlainText(QString::fromStdString(temp));
}

customerProf::~customerProf()
{
    delete ui;
}

void customerProf::on_pushButton_4_clicked()
{
    //تغییر اطلاعات و ذخیره در فایل
    customer cus_changes;
    customer tmp;
    cus_changes.string_to_char_array(cus_changes.get_Name(), 16, ui->plainTextEdit_2->toPlainText().toStdString());
    cus_changes.string_to_char_array(cus_changes.get_phoneNumber(), 12, ui->plainTextEdit->toPlainText().toStdString());
    cus_changes.string_to_char_array(cus_changes.get_city(), 11, ui->plainTextEdit_6->toPlainText().toStdString());
    cus_changes.set_ProductType(cust.get_ProductType());
    cus_changes.string_to_char_array(cus_changes.get_User(), 16, ui->plainTextEdit_5->toPlainText().toStdString());
    strcpy(cus_changes.get_Password(), cust.get_Password());
    cus_changes.set_access( '1');

    ifstream oldFile("customers.txt", ios::in | ios::binary);
    ofstream newChanges("tmpFile.txt", ios::app | ios::binary);
    int flag;

    while(!oldFile.eof())
        {
            oldFile.read((char*)&tmp, sizeof(customer));
            if(oldFile)
            {
                if(strcmp(cust.get_User(), tmp.get_User()))
                {
                    newChanges.write((char*)&tmp, sizeof(customer));
                }
            }
        }
    newChanges.write((char *)&cus_changes,sizeof(customer));

    newChanges.close();
    oldFile.close();

    remove("customers.txt");
    rename("tmpFile.txt", "customers.txt");

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

void customerProf::on_pushButton_3_clicked()
{
    //طرح های تبلیغاتی
}

void customerProf::on_pushButton_5_clicked()
{
    this->close();
    LoginPage *relogin = new LoginPage();
    relogin->show();
}

