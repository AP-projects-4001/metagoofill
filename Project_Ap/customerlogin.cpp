#include "customerlogin.h"
#include "ui_customerlogin.h"
#include "forgetpascustomer.h"
#include "mainlogin.h"
#include <QMessageBox>
#include <fstream>

using namespace std;
CustomerLogin::CustomerLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomerLogin)
{
    ui->setupUi(this);
}

CustomerLogin::~CustomerLogin()
{
    delete ui;
}

void charArrayToString(string &str, int len, char *array_char)
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

bool checking_UserAndPass(string username,string password)
{
    struct Customer customerr;
    ifstream CustomerFile("customers.txt", ios::in | ios::binary);
    string user;
    string pass;

    while(CustomerFile.read((char*)&customerr, 118))
    {
        charArrayToString(user, 16, customerr.User);
        charArrayToString(pass, 31, customerr.Password);
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

void CustomerLogin::on_pushButton_clicked()//we must add next page
{
    string User = ui->textEdit->toPlainText().toStdString();
    string Passwd = ui->textEdit_2->toPlainText().toStdString();
    if(checking_UserAndPass(User,Passwd))
    {
        QMessageBox::about(this, "توجه", "ورود موفقیت آمیز");
        //New Page
        //Complete by Ali yaghini
    }
    else
    {
        QMessageBox::about(this, "توجه","یوزر یا پسورد اشتباه است یا فیلدهاخالی هستند");
        return;
    }
}

void CustomerLogin::on_pushButton_2_clicked()
{
    ForgetPasCustomer *p = new ForgetPasCustomer(this);
    p->show();
    this->hide();
}

void CustomerLogin::on_pushButton_3_clicked()//بازگشت به صفحه قبل
{
    MainLogin *p = new MainLogin(this);
    p->show();
    this->hide();
}
