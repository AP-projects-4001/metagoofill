#include "infofcus.h"
#include "ui_infofcus.h"
#include "listofcustomersforadmin.h"
#include <fstream>

using namespace std;
infofcus::infofcus(customer cus, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infofcus)
{
    ui->setupUi(this);
    cus_info = cus;

    string temp;
    cus_info.char_array_to_string(temp, 16, cus_info.get_Name());
    ui->plainTextEdit_2->setPlainText(QString::fromStdString(temp));

    cus_info.char_array_to_string(temp, 12, cus_info.get_phoneNumber());
    ui->plainTextEdit->setPlainText(QString::fromStdString(temp));

    cus_info.char_array_to_string(temp, 31, cus_info.get_city());//در فیلد آدرس وارد می شود
    ui->plainTextEdit_6->setPlainText(QString::fromStdString(temp));

//    std::string tmp(1, cus_info.ProductType);
    ui->plainTextEdit_7->setPlainText(QString::number(cus_info.get_ProductType()));

//    ui->plainTextEdit_8->setPlainText(QString::number(cus_info.access));
    if(cus_info.get_access() == '1')
    {
        ui->plainTextEdit_8->setPlainText(QString::fromStdString("active"));
    }
    else if(cus_info.get_access() == '0')
    {
        ui->plainTextEdit_8->setPlainText(QString::fromStdString("not active"));
    }

    cus_info.char_array_to_string(temp, 16, cus_info.get_User());
    ui->plainTextEdit_5->setPlainText(QString::fromStdString(temp));

}

infofcus::~infofcus()
{
    delete ui;
}


void infofcus::on_pushButton_4_clicked()
{
    //تغییر اطلاعات و ذخیره در فایل
    customer cus_changes;
    customer tmp;
    cus_changes.string_to_char_array(cus_changes.get_Name(),16, ui->plainTextEdit_2->toPlainText().toStdString());
    cus_changes.string_to_char_array(cus_changes.get_phoneNumber(), 12, ui->plainTextEdit->toPlainText().toStdString());
    cus_changes.string_to_char_array(cus_changes.get_city(), 11, ui->plainTextEdit_6->toPlainText().toStdString());
    cus_changes.set_ProductType( cus_info.get_ProductType());
    cus_changes.string_to_char_array(cus_changes.get_User(), 16, ui->plainTextEdit_5->toPlainText().toStdString());
    strcpy(cus_changes.get_Password(), cus_info.get_Password());
    cus_changes.set_access(ui->plainTextEdit_8->toPlainText().toStdString()[0]);

    ifstream oldFile("customers.txt", ios::in | ios::binary);
    ofstream newChanges("tmpFile.txt", ios::app | ios::binary);
    int flag;

    while(!oldFile.eof())
        {
            oldFile.read((char*)&tmp,sizeof(customer));
            if(oldFile)
            {
                if(strcmp(cus_info.get_User(), tmp.get_User()))
                {
                    newChanges.write((char*)&tmp, 139);
                }
            }
        }
    newChanges.write((char *)&cus_changes, sizeof(customer));

    newChanges.close();
    oldFile.close();

    remove("customers.txt");
    rename("tmpFile.txt", "customers.txt");
}


void infofcus::on_pushButton_5_clicked()
{
    this->close();
    ListOfCustomersForAdmin *readmin = new ListOfCustomersForAdmin();
    readmin->show();
}

