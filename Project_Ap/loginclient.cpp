#include "loginclient.h"
#include "ui_loginclient.h"
#include "mainlogin.h"
#include "forgetpasclient.h"
#include<QMessageBox>
using namespace std;
LoginClient::LoginClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginClient)
{
    ui->setupUi(this);
}
bool MatchingUserAndPasClient(string User,string Pas)
{
    return true;
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
    string Pas = ui->textEdit->toPlainText().toStdString();
    if(MatchingUserAndPasClient(User, Pas)&&User!=""&&Pas!="")
    {
        //New Page
        //Complete by Ali Yaghini
    }
    else
    {
        QMessageBox::about(this,"توجه","یوزر یا شماره تلفن تطابقت نداردیا دو جایگاه خالیست");
        return;
    }

}

void LoginClient::on_pushButton_3_clicked()
{
    ForgetPasClient *p = new ForgetPasClient(this);
    p->show();
    this->hide();

}
