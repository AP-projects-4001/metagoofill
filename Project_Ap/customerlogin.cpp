#include "customerlogin.h"
#include "ui_customerlogin.h"
#include "forgetpascustomer.h"
#include "mainlogin.h"
#include <QMessageBox>
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
bool CheckFileCus(string a , string b)
{
    return true;//It must Change by Ali Yaghini
}
void CustomerLogin::on_pushButton_clicked()
{
    string User = ui->textEdit->toPlainText().toStdString();
    string Pas = ui->textEdit_2->toPlainText().toStdString();
    if(CheckFileCus(User,Pas))//It must Change by Ali Yaghini
    {
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

void CustomerLogin::on_pushButton_3_clicked()
{
    MainLogin *p = new MainLogin(this);
    p->show();
    this->hide();
}
