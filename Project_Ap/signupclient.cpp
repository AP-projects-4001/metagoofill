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

void char_arrayToString(string &str, int len, char *array_char)
{
    str="";
    int i=0;
    for(i=0;i<len-1;i++){
        if(array_char[i]=='\0'){
            break;
        }
        str += array_char[i];
    }
}

bool CheckUserNameClient(string username)//یوزر تکراری
{
    struct Client oldClient;
    ifstream oldClients("clients.txt", ios::in | ios::binary);
    string temp_user;
    while(oldClients.read((char*)&oldClient, 117))
    {
        char_arrayToString(temp_user, 16, oldClient.User);
        if(username == temp_user)
        {
            oldClients.close();
            return false;
        }
    }
    oldClients.close();
    return true;
}

void string_to_char_array(char *array_char, int len, string str)
{
    int i=0;
    for(i=0;i<len-1;i++){
        if(str[i]=='\0'){
            break;
        }
        array_char[i]=str[i];
    }
    array_char[i]='\0';
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

//    string newUser = ui->textEdit_14->toPlainText().toStdString();
//    if(CheckUserNameClient(newUser) == false)
//    {
//        QMessageBox::warning(this, "اخطار","نام کاربری تکراری است");
//        return;
//    }

    struct Client NewClient;
    ofstream clientFile("clients.txt", ios::app | ios::binary);
    string_to_char_array(NewClient.Name, ui->textEdit_12->toPlainText().size()+1, ui->textEdit_12->toPlainText().toStdString());
    string_to_char_array(NewClient.User, ui->textEdit_14->toPlainText().size()+1, ui->textEdit_14->toPlainText().toStdString());
    string_to_char_array(NewClient.Password, ui->textEdit_13->toPlainText().size()+1, ui->textEdit_13->toPlainText().toStdString());
    string_to_char_array(NewClient.Address, ui->textEdit_16->toPlainText().size()+1, ui->textEdit_16->toPlainText().toStdString());
    string_to_char_array(NewClient.city, ui->textEdit_17->toPlainText().size()+1, ui->textEdit_17->toPlainText().toStdString());
    string_to_char_array(NewClient.CellPhoneNumber, ui->textEdit_15->toPlainText().size()+1, ui->textEdit_15->toPlainText().toStdString());

    string newUser = ui->textEdit_14->toPlainText().toStdString();
    if(CheckUserNameClient(newUser) == false)
    {
        QMessageBox::warning(this, "اخطار","نام کاربری تکراری است");
        return;
    }

    QMessageBox::about(this, "توجه", "ثبت نام موفقیت آمیز");

    clientFile.write((char*)&NewClient, 117);//change block size
    clientFile.close();
}

void SignUpClient::on_pushButton_3_clicked()//بازگشت به صصفحه قبل
{
    SignUp *p =new SignUp(this);
    p->show();
    this->hide();
}
