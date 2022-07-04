#include "clientprof.h"
#include "ui_clientprof.h"
#include <cstring>
#include "goodslist.h"
#include "purchaserecords.h"
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
    client cli_changes;
    client tmp;
    cli_changes.string_to_char_array(cli_changes.Name, ui->plainTextEdit_13->toPlainText().toStdString().size()+1, ui->plainTextEdit_13->toPlainText().toStdString());
    cli_changes.string_to_char_array(cli_changes.CellPhoneNumber, ui->plainTextEdit_5->toPlainText().toStdString().size()+1, ui->plainTextEdit_5->toPlainText().toStdString());
    cli_changes.string_to_char_array(cli_changes.city, ui->plainTextEdit_15->toPlainText().toStdString().size()+1, ui->plainTextEdit_15->toPlainText().toStdString());
    cli_changes.string_to_char_array(cli_changes.Address, ui->plainTextEdit_14->toPlainText().toStdString().size()+1, ui->plainTextEdit_14->toPlainText().toStdString());
    cli_changes.string_to_char_array(cli_changes.User, ui->plainTextEdit_16->toPlainText().toStdString().size()+1, ui->plainTextEdit_16->toPlainText().toStdString());
    strcpy(cli_changes.Password, clie.Password);

    ifstream oldFile("clients.txt", ios::in | ios::binary);
    ofstream newChanges("tmpFile.txt", ios::app | ios::binary);
    int flag;

    while(!oldFile.eof())
        {
            oldFile.read((char*)&tmp, 138);
            if(oldFile)
            {
                if(strcmp(clie.User, tmp.User))
                {
                    newChanges.write((char*)&tmp, sizeof(client));
                }
            }
        }
    newChanges.write((char *)&cli_changes, sizeof(client));

        newChanges.close();
        oldFile.close();

        remove("clients.txt");
        rename("tmpFile.txt", "clients.txt");
}


void clientProf::on_pushButton_7_clicked()
{
    //رفتن به فروشگاه
    goodsList *goodslist= new goodsList(clie,this);
    this->hide();
}


void clientProf::on_pushButton_6_clicked()
{
    PurchaseRecords *purchaserecords= new PurchaseRecords(clie,this);
    purchaserecords->show();
    this->hide();
}


void clientProf::on_pushButton_4_clicked()
{
    //بازگشت به صفحه قبل
}


