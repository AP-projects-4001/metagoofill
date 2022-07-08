#include "infofclie.h"
#include "ui_infofclie.h"
#include "listofclientforadmin.h"

#include <fstream>

using namespace std;
infofclie::infofclie(client clie, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infofclie)
{
    ui->setupUi(this);

    clie_inf = clie;// ذخیره شی در کلاس
    string temp;

    //set name.
    clie_inf.char_array_to_string(temp, 16, clie_inf.get_Name());
    ui->plainTextEdit_2->setPlainText(QString::fromStdString(temp));

    //set phonenumber.
    clie_inf.char_array_to_string(temp, 12, clie_inf.get_phoneNumber());
    ui->plainTextEdit->setPlainText(QString::fromStdString(temp));

    //set city.
    clie_inf.char_array_to_string(temp, 11, clie_inf.get_city());
    ui->plainTextEdit_7->setPlainText(QString::fromStdString(temp));

    //set address.
    clie_inf.char_array_to_string(temp, 31, clie_inf.get_Address());
    ui->plainTextEdit_6->setPlainText(QString::fromStdString(temp));

    //access.
    if(clie_inf.get_access() == '1')
    {
        ui->plainTextEdit_8->setPlainText(QString::fromStdString("active"));
    }
    else if(clie_inf.get_access() == '0')
    {
        ui->plainTextEdit_8->setPlainText(QString::fromStdString("not active"));
    }

    //set username.
    clie_inf.char_array_to_string(temp, 16, clie_inf.get_User());
    ui->plainTextEdit_5->setPlainText(QString::fromStdString(temp));

}

infofclie::~infofclie()
{
    delete ui;
}

void infofclie::on_pushButton_4_clicked()
{
    client cli_changes;
    client tmp;
    cli_changes.string_to_char_array(cli_changes.get_Name(), 16, ui->plainTextEdit_2->toPlainText().toStdString());
    cli_changes.string_to_char_array(cli_changes.get_phoneNumber(), 12, ui->plainTextEdit->toPlainText().toStdString());
    cli_changes.string_to_char_array(cli_changes.get_city(), 11, ui->plainTextEdit_7->toPlainText().toStdString());
    cli_changes.string_to_char_array(cli_changes.get_Address(), 31, ui->plainTextEdit_6->toPlainText().toStdString());
    cli_changes.string_to_char_array(cli_changes.get_User(), 16, ui->plainTextEdit_5->toPlainText().toStdString());
    strcpy(cli_changes.get_Password(), clie_inf.get_Password());
    cli_changes.set_access( ui->plainTextEdit_8->toPlainText().toStdString()[0]);

    ifstream oldFile("clients.txt", ios::in | ios::binary);
    ofstream newChanges("tmpFile.txt", ios::app | ios::binary);
    while(!oldFile.eof())
        {
            oldFile.read((char*)&tmp, sizeof(client));
            if(oldFile)
            {
                if(strcmp(clie_inf.get_User(), tmp.get_User()))
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


void infofclie::on_pushButton_5_clicked()
{
    ListOFClientForAdmin *readmin = new ListOFClientForAdmin();
    this->close();
    readmin->show();
}

