#include "loginadmin.h"
#include "ui_loginadmin.h"
#include "mainlogin.h"
#include <QMessageBox>
using namespace  std;
Loginadmin::Loginadmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loginadmin)
{
    ui->setupUi(this);
}

Loginadmin::~Loginadmin()
{
    delete ui;
}

void Loginadmin::on_pushButton_2_clicked()
{
    MainLogin *p = new MainLogin(this);
    this->hide();
    p->show();
}

void Loginadmin::on_pushButton_clicked()
{
    string User = ui->textEdit->toPlainText().toStdString();
    string pas = ui->textEdit_2->toPlainText().toStdString();
    if(User=="Admin"&&pas=="Admin")
    {
        //New Page
        close();
        AdminPage *p =  new AdminPage(this);
        p->show();
    }
    else
    {
        QMessageBox::about(this,"توجه","رمز و یوزر را از برنامه نویس سوال کنید");
        return;
    }
}
