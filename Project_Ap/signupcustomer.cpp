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

bool CheckUserNameCustomer(string username)//تکراری بودن یوزر
{
    class customer oldCustomer;
    ifstream oldCustomers("customers.txt", ios::in | ios::binary);
    string temp_user;
    while(oldCustomers.read((char*)&oldCustomer, sizeof(customer)))
    {
        oldCustomer.char_array_to_string(temp_user, 16, oldCustomer.User);
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

         class customer NewCustomer;
         NewCustomer.string_to_char_array(NewCustomer.Name, ui->textEdit_7->toPlainText().size()+1, ui->textEdit_7->toPlainText().toStdString());
         NewCustomer.string_to_char_array(NewCustomer.User, ui->textEdit_8->toPlainText().size()+1, ui->textEdit_8->toPlainText().toStdString());
         NewCustomer.string_to_char_array(NewCustomer.Password, ui->textEdit_9->toPlainText().size()+1, ui->textEdit_9->toPlainText().toStdString());
         NewCustomer.string_to_char_array(NewCustomer.PhoneNumber, ui->textEdit_10->toPlainText().size()+1, ui->textEdit_10->toPlainText().toStdString());
         NewCustomer.string_to_char_array(NewCustomer.city, ui->textEdit_11->toPlainText().size()+1, ui->textEdit_11->toPlainText().toStdString());
         NewCustomer.access = '1';
         NewCustomer.ptr_end_mysells = 0;
         NewCustomer.ptr_start_mysells = 0;
         NewCustomer.number_mysells = 0;
         NewCustomer.ptr_file_myproduct = 0;
         NewCustomer.number_myproducts = 0;


         if(ui->radioButton_3)
         {
             NewCustomer.ProductType=2;//پوشاک
         }
         else if(ui->radioButton_4)
         {
             NewCustomer.ProductType=3;//میوه و تره بار
         }
         else if(ui->radioButton_5)
         {
             NewCustomer.ProductType=4;//لبنیات
         }
         else if(ui->radioButton_6)
         {
             NewCustomer.ProductType=0;//تکنولوژی
         }
         else if(ui->radioButton_7)
         {
             NewCustomer.ProductType=5;//آجیل
         }
         else
         {
             NewCustomer.ProductType=1;//لوازم خانگی
         }

         int tmp_id;
         fstream spec_info("infos.txt", ios::in | ios::out | ios::binary);
         spec_info.seekg(4);
         spec_info.read((char*)&tmp_id, 4);
         tmp_id++;
         spec_info.seekp(4);
         spec_info.write((char*)&tmp_id, 4);
         spec_info.close();
         NewCustomer.ID = tmp_id;

         ofstream CustomerFile("customers.txt", ios::app | ios::binary);
         if(CheckUserNameCustomer(ui->textEdit_8->toPlainText().toStdString()) == false)
         {
             QMessageBox::about(this,"توجه","یوزرنیم تکراری است");
             return;
         }

         QMessageBox::about(this, "توجه", "ثبت نام موفقیت آمیز");

         CustomerFile.write((char*)&NewCustomer, sizeof(customer));
         CustomerFile.close();
}

void SignUpCUSTOMER::on_pushButton_2_clicked()//بازگشت به صفحه قبل
{
    SignUp *p = new SignUp(this);
    p->show();
    this->hide();
}
