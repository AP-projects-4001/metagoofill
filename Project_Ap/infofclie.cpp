#include "infofclie.h"
#include "ui_infofclie.h"
#include "listofclientforadmin.h"

#include <fstream>

using namespace std;
infofclie::infofclie(client _clie, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infofclie)
{
    ui->setupUi(this);

    clie = _clie;// ذخیره شی در کلاس

    show_infofclie();
}

infofclie::~infofclie()
{
    delete ui;
}

void infofclie::show_infofclie()
{
    string temp;

    //set name.
    clie.char_array_to_string(temp, 16, clie.get_Name());
    ui->plainTextEdit_2->setPlainText(QString::fromStdString(temp));

    //set phonenumber.
    clie.char_array_to_string(temp, 12, clie.get_phoneNumber());
    ui->plainTextEdit->setPlainText(QString::fromStdString(temp));

    //set city.
    clie.char_array_to_string(temp, 11, clie.get_city());
    ui->plainTextEdit_7->setPlainText(QString::fromStdString(temp));

    //set address.
    clie.char_array_to_string(temp, 31, clie.get_Address());
    ui->plainTextEdit_6->setPlainText(QString::fromStdString(temp));

    //access.
    if(clie.get_access()=='1'){ui->radioButton->click();}
    else{ui->radioButton_2->click();}

    //set username.
    clie.char_array_to_string(temp, 16, clie.get_User());
    ui->plainTextEdit_5->setPlainText(QString::fromStdString(temp));
}

void infofclie::on_pushButton_4_clicked()
{
    fstream database_clients("clients.txt", ios::in | ios::out | ios::binary);
    database_clients.seekg((clie.get_ID()-1)*sizeof(client));
    database_clients.read((char*)&clie,sizeof(client));

    clie.string_to_char_array(clie.get_Name(), 16, ui->plainTextEdit_2->toPlainText().toStdString());
    clie.string_to_char_array(clie.get_phoneNumber(), 12, ui->plainTextEdit->toPlainText().toStdString());
    clie.string_to_char_array(clie.get_city(), 11, ui->plainTextEdit_7->toPlainText().toStdString());
    clie.string_to_char_array(clie.get_Address(), 31, ui->plainTextEdit_6->toPlainText().toStdString());
    clie.string_to_char_array(clie.get_User(), 16, ui->plainTextEdit_5->toPlainText().toStdString());

    if(ui->radioButton->isChecked()){clie.set_access('1');}
    else{clie.set_access('0');}

    database_clients.seekp((clie.get_ID()-1)*sizeof(client));
    database_clients.write((char*)&clie,sizeof(client));
    database_clients.close();

    show_infofclie();

}


void infofclie::on_pushButton_5_clicked()
{
    ListOFClientForAdmin *readmin = new ListOFClientForAdmin();
    this->close();
    readmin->show();
}

