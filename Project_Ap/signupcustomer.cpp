#include "signupcustomer.h"
#include "ui_signupcustomer.h"
#include <QMessageBox>
#include "signup.h"
using namespace std;
SignUpCUSTOMER::SignUpCUSTOMER(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpCUSTOMER)
{
    ui->setupUi(this);
}

SignUpCUSTOMER::~SignUpCUSTOMER()
{
    delete ui;
}
bool CheckUserNameCustomer()//تکراری بودن یوزر
{
    return true;
}
bool SignUpCUSTOMER::CheckRadio()//چک کردن  رادیو باتون که زده شده یا زده نشده
{
    if((((ui->radioButton_3->isChecked())||(ui->radioButton_4->isChecked())||
                                        (ui->radioButton_5->isChecked())||
                                        (ui->radioButton_6->isChecked())||
                                        (ui->radioButton_7->isChecked())||
                                        (ui->radioButton_8->isChecked()))))
    {
        return false;
    }
    return true;

}
void AddStringToCharCustomer(int  len,char *x,string  y)
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
void SignUpCUSTOMER::on_pushButton_clicked()
{
    if(ui->textEdit_9->toPlainText().toStdString()==""||ui->textEdit_10->toPlainText().toStdString()==""||
         ui->textEdit_8->toPlainText().toStdString()==""||ui->textEdit_7->toPlainText().toStdString()==""||
         ui->textEdit_6->toPlainText().toStdString()==""||ui->textEdit_11->toPlainText().toStdString()==""||
            CheckRadio())

    {
        QMessageBox::about(this,"توجه","یکی از فیلدها خالیست");
        return;
    }

         struct Customer NewCustomer[1];
         int ProductType;
         if(ui->radioButton_3)
         {
             NewCustomer[0].ProductType=6;//پوشاک
         }
         else if(ui->radioButton_4)
         {
             NewCustomer[0].ProductType=1;//میوه و تره بار
         }
         else if(ui->radioButton_5)
         {
             NewCustomer[0].ProductType=2;//لبنیات
         }
         else if(ui->radioButton_6)
         {
             NewCustomer[0].ProductType=4;//تکنولوژی
         }
         else if(ui->radioButton_7)
         {
             NewCustomer[0].ProductType=3;//آجیل
         }
         else
         {
             NewCustomer[0].ProductType=5;//لوازم خانگی
         }

         string Name= ui->textEdit_7->toPlainText(). toStdString();//
         AddStringToCharCustomer(16,NewCustomer[0].Name,Name);
         string UserName = ui->textEdit_8->toPlainText().toStdString();//
         if(CheckUserNameCustomer())
         {
             AddStringToCharCustomer(16,NewCustomer[0].User,UserName);
         }
         else
         {
             QMessageBox::about(this,"توجه","یوزرنیم تکراری است");
             return;
         }
         AddStringToCharCustomer(16,NewCustomer[0].User,UserName);
         string CellPhoneNumber = ui->textEdit_11->toPlainText().toStdString();//
         AddStringToCharCustomer(16,NewCustomer[0].CellPhoneNumber,CellPhoneNumber);
         string password = ui->textEdit_9->toPlainText().toStdString();//
         AddStringToCharCustomer(16,NewCustomer[0].Password,password);
         string City = ui->textEdit_6->toPlainText().toStdString();//
         AddStringToCharCustomer(16,NewCustomer[0].city,City);
         customer.push_back(NewCustomer[0]);
}

void SignUpCUSTOMER::on_pushButton_2_clicked()//بازگشت به صفحه قبل
{
    SignUp *p = new SignUp(this);
    p->show();
    this->hide();
}
