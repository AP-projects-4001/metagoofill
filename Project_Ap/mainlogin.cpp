#include "mainlogin.h"
#include "ui_mainlogin.h"
#include "customerlogin.h"
#include "loginpage.h"
#include "loginclient.h"
#include "loginadmin.h"
MainLogin::MainLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainLogin)
{
    ui->setupUi(this);
}

MainLogin::~MainLogin()
{
    delete ui;
}

void MainLogin::on_pushButton_clicked()
{
    CustomerLogin *p = new CustomerLogin(this);
    p->show();
    this->hide();
}

void MainLogin::on_pushButton_2_clicked()
{
    LoginPage *p = new LoginPage(this);
    p->show();
    this->hide();
}

void MainLogin::on_pushButton_3_clicked()
{
    LoginClient *p = new LoginClient(this);
    p->show();
    this->hide();
}

void MainLogin::on_pushButton_4_clicked()
{
    Loginadmin *p = new Loginadmin(this);
    p->show();
    this->hide();

}
