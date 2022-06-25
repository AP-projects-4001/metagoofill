#include "loginclient.h"
#include "ui_loginclient.h"
#include "mainlogin.h"
#include "forgetpasclient.h"
#include<QMessageBox>
#include <fstream>
#include <string>
using namespace std;
LoginClient::LoginClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginClient)
{
    ui->setupUi(this);
}

void char_array_to_string(string &str, int len, char *array_char)
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

bool MatchingUserAndPasClient(string username,string password)
{
    struct client Client;
    ifstream clientFile("clients.txt", ios::in | ios::binary);
    string user;
    string pass;
    int flag = 0;
    while(clientFile.read((char*)&Client, 117))
    {
        char_array_to_string(user, 16, Client.User);
        char_array_to_string(pass, 31, Client.Password);
        if(username == user)
        {
            if(password == pass)
            {
                return true;
            }
        }     
    }
    return false;
}

LoginClient::~LoginClient()
{
    delete ui;
}

void LoginClient::on_pushButton_2_clicked()
{
    MainLogin *p = new MainLogin(this);
    p->show();
    this->hide();
}

void LoginClient::on_pushButton_clicked()
{
    string User = ui->textEdit->toPlainText().toStdString();
    string Pass = ui->textEdit_2->toPlainText().toStdString();
    if(MatchingUserAndPasClient(User, Pass) && User != "" && Pass != "")
    {
        QMessageBox::about(this, "توجه", "ورود موفقیت آمیز");
        //New Page
        //Complete by Ali Yaghini
    }
    else
    {
        QMessageBox::about(this,"توجه","یوزرنیم یا رمزعبور نادرست است یا جایگاه خالیست");
        return;
    }

}

void LoginClient::on_pushButton_3_clicked()
{
    ForgetPasClient *p = new ForgetPasClient(this);
    p->show();
    this->hide();

}
