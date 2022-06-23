#include "loginpage.h"
#include "ui_loginpage.h"
#include "signup.h"
#include "mainlogin.h"
LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage()
{
    delete ui;
}


void LoginPage::on_pushButton_7_clicked()
{
    this->close();
}

void LoginPage::on_pushButton_9_clicked()
{
    SignUp *p = new SignUp(this);
    p->show();
    this->hide();
}

void LoginPage::on_pushButton_8_clicked()
{
    MainLogin *p = new MainLogin(this);
    p->show();
    this->hide();
}
