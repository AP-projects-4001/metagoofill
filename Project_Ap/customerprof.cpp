#include "customerprof.h"
#include "ui_customerprof.h"
#include <fstream>
#include <cstring>
#include "storecustomer.h"
using namespace std;

customerProf::customerProf(customer cus_info, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::customerProf)
{
    ui->setupUi(this);
    cust = cus_info;// ذخیره شی در کلاس
    string temp;
    cus_info.char_array_to_string(temp, 16, cus_info.Name);
    ui->plainTextEdit_2->setPlainText(QString::fromStdString(temp));

    cus_info.char_array_to_string(temp, 12, cus_info.PhoneNumber);
    ui->plainTextEdit->setPlainText(QString::fromStdString(temp));

    cus_info.char_array_to_string(temp, 31, cus_info.city);//در فیلد آدرس وارد می شود
    ui->plainTextEdit_6->setPlainText(QString::fromStdString(temp));

//    std::string tmp(1, cus_info.ProductType);
    ui->plainTextEdit_7->setPlainText(QString::number(cus_info.ProductType));

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
    customer cus_changes;
    customer tmp;
    cus_changes.string_to_char_array(cus_changes.Name, ui->plainTextEdit_2->toPlainText().toStdString().size()+1, ui->plainTextEdit_2->toPlainText().toStdString());
    cus_changes.string_to_char_array(cus_changes.PhoneNumber, ui->plainTextEdit->toPlainText().toStdString().size()+1, ui->plainTextEdit->toPlainText().toStdString());
    cus_changes.string_to_char_array(cus_changes.city, ui->plainTextEdit_6->toPlainText().toStdString().size()+1, ui->plainTextEdit_6->toPlainText().toStdString());
    cus_changes.ProductType = cust.ProductType;
    cus_changes.string_to_char_array(cus_changes.User, ui->plainTextEdit_5->toPlainText().toStdString().size()+1, ui->plainTextEdit_5->toPlainText().toStdString());
    strcpy(cus_changes.Password, cust.Password);

    ifstream oldFile("customers.txt", ios::in | ios::binary);
    ofstream newChanges("tmpFile.txt", ios::app | ios::binary);
    int flag;

    while(!oldFile.eof())
        {
            oldFile.read((char*)&tmp, 118);
            if(oldFile)
            {
                if(strcmp(cust.User, tmp.User))
                {
                    newChanges.write((char*)&tmp, 118);
                }
            }
        }
    newChanges.write((char *)&cus_changes, 118);

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
    //صفحه سوایق فروش
}

void customerProf::on_pushButton_3_clicked()
{
    //طرح های تبلیغاتی
}
