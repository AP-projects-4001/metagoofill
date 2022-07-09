#include "infofcus.h"
#include "ui_infofcus.h"
#include "listofcustomersforadmin.h"
#include <fstream>

using namespace std;
infofcus::infofcus(customer _cust, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infofcus)
{
    ui->setupUi(this);
    cust = _cust;

    show_infofcus();
}

infofcus::~infofcus()
{
    delete ui;
}

void infofcus::show_infofcus()
{
    string temp;
    cust.char_array_to_string(temp, 16, cust.get_Name());
    ui->plainTextEdit_2->setPlainText(QString::fromStdString(temp));

    cust.char_array_to_string(temp, 12, cust.get_phoneNumber());
    ui->plainTextEdit->setPlainText(QString::fromStdString(temp));

    cust.char_array_to_string(temp, 31, cust.get_city());//در فیلد آدرس وارد می شود
    ui->plainTextEdit_6->setPlainText(QString::fromStdString(temp));

    ui->plainTextEdit_7->setPlainText(QString::number(cust.get_ProductType()));

    if(cust.get_access()=='1'){ui->radioButton->click();}
    else{ui->radioButton_2->click();}

    cust.char_array_to_string(temp, 16, cust.get_User());
    ui->plainTextEdit_5->setPlainText(QString::fromStdString(temp));
}


void infofcus::on_pushButton_4_clicked()
{
    //تغییر اطلاعات و ذخیره در فایل
    fstream database_customers("customers.txt", ios::in | ios::out | ios::binary);
    database_customers.seekg((cust.get_ID()-1)*sizeof(customer));
    database_customers.read((char*)&cust,sizeof(customer));

    cust.string_to_char_array(cust.get_Name(),16, ui->plainTextEdit_2->toPlainText().toStdString());
    cust.string_to_char_array(cust.get_phoneNumber(), 12, ui->plainTextEdit->toPlainText().toStdString());
    cust.string_to_char_array(cust.get_city(), 11, ui->plainTextEdit_6->toPlainText().toStdString());
    cust.set_ProductType( cust.get_ProductType());
    cust.string_to_char_array(cust.get_User(), 16, ui->plainTextEdit_5->toPlainText().toStdString());

    if(ui->radioButton->isChecked()){cust.set_access('1');}
    else{cust.set_access('0');}

    database_customers.seekp((cust.get_ID()-1)*sizeof(customer));
    database_customers.write((char*)&cust,sizeof(customer));
    database_customers.close();

    show_infofcus();
}


void infofcus::on_pushButton_5_clicked()
{
    this->close();
    ListOfCustomersForAdmin *readmin = new ListOfCustomersForAdmin();
    readmin->show();
}

