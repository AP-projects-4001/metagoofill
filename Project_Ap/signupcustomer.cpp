#include "signupcustomer.h"
#include "ui_signupcustomer.h"
#include <QMessageBox>
#include <fstream>
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

void charArray_to_string(string &str, int len, char *array_char)
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

bool CheckUserNameCustomer(string username)//تکراری بودن یوزر
{
    struct Customer oldCustomer;
    ifstream oldCustomers("customers.txt", ios::in | ios::binary);
    string temp_user;
    while(oldCustomers.read((char*)&oldCustomer, 118))
    {
        charArray_to_string(temp_user, 16, oldCustomer.User);
        if(username == temp_user)
        {
            oldCustomers.close();
            return false;
        }
    }
    oldCustomers.close();
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

void stringToCharArray(char *array_char, int len, string str)
{
    int i=0;
    for(i=0;i<len-1;i++){
        if(str[i]=='\0'){
            break;
        }
        array_char[i]=str[i];
    }
    array_char[i]='\0';
}

void SignUpCUSTOMER::on_pushButton_clicked()
{
    if(ui->textEdit_9->toPlainText().toStdString()==""||ui->textEdit_10->toPlainText().toStdString()==""||
         ui->textEdit_8->toPlainText().toStdString()==""||ui->textEdit_7->toPlainText().toStdString()==""||
         ui->textEdit_11->toPlainText().toStdString()==""||
            CheckRadio())
    {
        QMessageBox::about(this,"توجه","یکی از فیلدها خالیست");
        return;
    }

         struct Customer NewCustomer;
         stringToCharArray(NewCustomer.Name, ui->textEdit_7->toPlainText().size()+1, ui->textEdit_7->toPlainText().toStdString());
         stringToCharArray(NewCustomer.User, ui->textEdit_8->toPlainText().size()+1, ui->textEdit_8->toPlainText().toStdString());
         stringToCharArray(NewCustomer.Password, ui->textEdit_9->toPlainText().size(), ui->textEdit_9->toPlainText().toStdString());
         stringToCharArray(NewCustomer.PhoneNumber, ui->textEdit_10->toPlainText().size(), ui->textEdit_10->toPlainText().toStdString());
         stringToCharArray(NewCustomer.city, ui->textEdit_11->toPlainText().size(), ui->textEdit_11->toPlainText().toStdString());

         if(ui->radioButton_3)
         {
             NewCustomer.ProductType='6';//پوشاک
         }
         else if(ui->radioButton_4)
         {
             NewCustomer.ProductType='1';//میوه و تره بار
         }
         else if(ui->radioButton_5)
         {
             NewCustomer.ProductType='2';//لبنیات
         }
         else if(ui->radioButton_6)
         {
             NewCustomer.ProductType='4';//تکنولوژی
         }
         else if(ui->radioButton_7)
         {
             NewCustomer.ProductType='3';//آجیل
         }
         else
         {
             NewCustomer.ProductType='5';//لوازم خانگی
         }

         ofstream CustomerFile("customers.txt", ios::app | ios::binary);
         if(CheckUserNameCustomer(ui->textEdit_8->toPlainText().toStdString()) == false)
         {
             QMessageBox::about(this,"توجه","یوزرنیم تکراری است");
             return;
         }

         QMessageBox::about(this, "توجه", "ثبت نام موفقیت آمیز");

         CustomerFile.write((char*)&NewCustomer, 118);
         CustomerFile.close();
}

void SignUpCUSTOMER::on_pushButton_2_clicked()//بازگشت به صفحه قبل
{
    SignUp *p = new SignUp(this);
    p->show();
    this->hide();
}
