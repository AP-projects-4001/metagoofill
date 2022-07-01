#include "customerlogin.h"
#include "ui_customerlogin.h"
#include "forgetpascustomer.h"
#include "mainlogin.h"
#include <QMessageBox>
#include <fstream>
#include <cstring>
#include "customerprof.h"

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

bool checking_UserAndPass(string username,string password)
{
    class customer customerr;
    ifstream CustomerFile("customers.txt", ios::in | ios::binary);
    string user;
    string pass;

    while(CustomerFile.read((char*)&customerr, 138))
    {
        customerr.char_array_to_string(user, 16, customerr.User);
        customerr.char_array_to_string(pass, 31, customerr.Password);
        if(username == user)
        {
            if(password == pass)
            {
                CustomerFile.close();
                return true;
            }
        }
    }
    CustomerFile.close();
    return false;
}

void CustomerLogin::on_pushButton_clicked()
{
    string User = ui->textEdit->toPlainText().toStdString();
    string Passwd = ui->textEdit_2->toPlainText().toStdString();
    string username_tmp = "";
    if(checking_UserAndPass(User,Passwd))
    {
        QMessageBox::about(this, "توجه", "ورود موفقیت آمیز");
        class customer cus_tmp;
        ifstream cus_tmps("customers.txt", ios::in | ios::binary);
        while(cus_tmps.read((char*)&cus_tmp, 138))
        {
            cus_tmp.char_array_to_string(username_tmp, 16, cus_tmp.User);
            if(username_tmp == User)
            {
                //cus_tmps.close();
                dia2 = new customerProf(cus_tmp, this);
                this->hide();
                dia2->show();
            }
        }
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
