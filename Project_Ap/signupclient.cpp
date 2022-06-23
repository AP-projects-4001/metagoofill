#include "signupclient.h"
#include "ui_signupclient.h"
#include "signup.h"
#include <QMessageBox>
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
bool CheckUserNameClient()
{
    return true;
}
void SetStringToChar(int  len,char *x,string  y)
{
    int i;
    for(i=0;i<len-1;i++)
    {
        if(y.length()==i)
        {
            return;
        }
        x[i]=y[i];
    }
    x[i]='\0';
}
void SignUpClient::on_pushButton_clicked()
{
    if(ui->textEdit_12->toPlainText().toStdString()==""||ui->textEdit_13->toPlainText().toStdString()==""
         ||ui->textEdit_14->toPlainText().toStdString()==""||ui->textEdit_15->toPlainText().toStdString()==""||
         ui->textEdit_16->toPlainText().toStdString()==""||ui->textEdit_17->toPlainText().toStdString()=="")

    {
         QMessageBox::about(this,"توجه","یکی از فیلدها خالیست");
         return;
    }

         struct Client NewClient[1];
         string Name= ui->textEdit_12->toPlainText(). toStdString();//
         SetStringToChar(16,NewClient[0].Name,Name);
         string UserName = ui->textEdit_14->toPlainText().toStdString();//
         if(CheckUserNameClient())
         {
             SetStringToChar(16,NewClient[0].User,UserName);
         }
         else
         {
             QMessageBox::about(this,"توجه","یکی از فیلدها خالیست");
             return;
         }
         SetStringToChar(16,NewClient[0].User,UserName);
         string CellPhoneNumber = ui->textEdit_15->toPlainText().toStdString();//
         SetStringToChar(16,NewClient[0].CellPhoneNumber,CellPhoneNumber);
         string Address = ui->textEdit_16->toPlainText().toStdString();//
         SetStringToChar(16,NewClient[0].Address,Address);
         string password = ui->textEdit_13->toPlainText().toStdString();//
         SetStringToChar(16,NewClient[0].Password,password);
         string City = ui->textEdit_17->toPlainText().toStdString();//
         SetStringToChar(16,NewClient[0].city,City);
         client.push_back(NewClient[0]);

}

void SignUpClient::on_pushButton_3_clicked()//بازگشت به صصفحه قبل
{
    SignUp *p =new SignUp(this);
    p->show();
    this->hide();
}
