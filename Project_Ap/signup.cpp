#include "signup.h"
#include "ui_signup.h"
#include "signupcustomer.h"
#include "signupclient.h"
#include "loginpage.h"
SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_clicked()//صفحه ثبت نام فروشنده
{
    SignUpCUSTOMER *p = new SignUpCUSTOMER(this);
    p->show();
    this->hide();
}

void SignUp::on_pushButton_2_clicked()
{
    SignUpClient *p = new SignUpClient(this);
    p->show();
    this->hide();
}

void SignUp::on_pushButton_3_clicked()//برگشت به قبل
{
    LoginPage *p = new LoginPage(this);
    p->show();
    this->hide();
}
