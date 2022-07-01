#include "signupclient.h"
#include "ui_signupclient.h"
#include "signup.h"
#include <QMessageBox>
#include <fstream>

using namespace std;

SignUpClient::SignUpClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpClient)
{
    ui->setupUi(this);
}

SignUpClient::~SignUpClient()
{
    delete ui;
}

bool CheckUserNameClient(string username)//یوزر تکراری
{
    class client oldClient;
    ifstream oldClients("clients.txt", ios::in | ios::binary);
    string temp_user;
    while(oldClients.read((char*)&oldClient, 137))
    {
        oldClient.char_array_to_string(temp_user, 16, oldClient.User);
        if(username == temp_user)
        {
            oldClients.close();
            return false;
        }
    }
    oldClients.close();
    return true;
}

void SignUpClient::on_pushButton_clicked()
{
    if(ui->textEdit_12->toPlainText().toStdString()=="" || ui->textEdit_13->toPlainText().toStdString()==""
          || ui->textEdit_14->toPlainText().toStdString()=="" || ui->textEdit_15->toPlainText().toStdString()=="" ||
         ui->textEdit_16->toPlainText().toStdString()=="" || ui->textEdit_17->toPlainText().toStdString()=="")
    {
         QMessageBox::about(this,"توجه","یکی از فیلدها خالیست");
         return;
    }

    class client NewClient;
    ofstream clientFile("clients.txt", ios::app | ios::binary);
    NewClient.string_to_char_array(NewClient.Name, ui->textEdit_12->toPlainText().size()+1, ui->textEdit_12->toPlainText().toStdString());
    NewClient.string_to_char_array(NewClient.User, ui->textEdit_14->toPlainText().size()+1, ui->textEdit_14->toPlainText().toStdString());
    NewClient.string_to_char_array(NewClient.Password, ui->textEdit_13->toPlainText().size()+1, ui->textEdit_13->toPlainText().toStdString());
    NewClient.string_to_char_array(NewClient.Address, ui->textEdit_16->toPlainText().size()+1, ui->textEdit_16->toPlainText().toStdString());
    NewClient.string_to_char_array(NewClient.city, ui->textEdit_17->toPlainText().size()+1, ui->textEdit_17->toPlainText().toStdString());
    NewClient.string_to_char_array(NewClient.CellPhoneNumber, ui->textEdit_15->toPlainText().size()+1, ui->textEdit_15->toPlainText().toStdString());

    fstream test_file("infos.txt",  ios::in | ios::binary);
    if(!test_file)
    {
        test_file.close();
        test_file.open("infos.txt",  ios::out | ios::binary);
        int a=0;
        for(int i=0; i<2; i++)
        {
            test_file.write((char*)&a, 4);
        }
    }
    test_file.close();

    int tmp_id;
    fstream spec_info("infos.txt", ios::in | ios::out | ios::binary);
    spec_info.seekg(0);
    spec_info.read((char*)&tmp_id, 4);
    tmp_id++;
    NewClient.string_to_char_array(NewClient.ID, to_string(tmp_id).size(), to_string(tmp_id));
    spec_info.seekp(0);
    spec_info.write((char*)&tmp_id, 4);
    spec_info.close();

    string newUser = ui->textEdit_14->toPlainText().toStdString();
    if(CheckUserNameClient(newUser) == false)
    {
        QMessageBox::warning(this, "اخطار","نام کاربری تکراری است");
        return;
    }

    QMessageBox::about(this, "توجه", "ثبت نام موفقیت آمیز");

    clientFile.write((char*)&NewClient, 137);//change block size
    clientFile.close();
}

void SignUpClient::on_pushButton_3_clicked()//بازگشت به صصفحه قبل
{
    SignUp *p =new SignUp(this);
    p->show();
    this->hide();
}
