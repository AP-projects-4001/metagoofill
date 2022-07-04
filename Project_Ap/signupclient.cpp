#include "signupclient.h"
#include "ui_signupclient.h"
#include "signup.h"
#include <QMessageBox>
#include <fstream>

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

bool CheckUserNameClient(string username)//یوزر تکراری
{
    client oldClient;
    ifstream oldClients("clients.txt", ios::in | ios::binary);
    string temp_user;
    while(oldClients.read((char*)&oldClient, sizeof(client)))
    {
        oldClient.char_array_to_string(temp_user, 16, oldClient.User);
        if(username == temp_user)
        {
            oldClients.close();
            return false;
        }
    }
    oldClients.close();
    return true;
}

void SignUpClient::on_pushButton_clicked()
{

    if(ui->textEdit_12->toPlainText().toStdString()=="" || ui->textEdit_13->toPlainText().toStdString()==""
          || ui->textEdit_14->toPlainText().toStdString()=="" || ui->textEdit_15->toPlainText().toStdString()=="" ||
         ui->textEdit_16->toPlainText().toStdString()=="" || ui->textEdit_17->toPlainText().toStdString()=="")
    {
         QMessageBox::about(this,"توجه","یکی از فیلدها خالیست");
         return;
    }

    client NewClient;
    ofstream clientFile("clients.txt", ios::app | ios::binary);
    NewClient.string_to_char_array(NewClient.Name, ui->textEdit_12->toPlainText().size()+1, ui->textEdit_12->toPlainText().toStdString());
    NewClient.string_to_char_array(NewClient.User, ui->textEdit_14->toPlainText().size()+1, ui->textEdit_14->toPlainText().toStdString());
    NewClient.string_to_char_array(NewClient.Password, ui->textEdit_13->toPlainText().size()+1, ui->textEdit_13->toPlainText().toStdString());
    NewClient.string_to_char_array(NewClient.Address, ui->textEdit_16->toPlainText().size()+1, ui->textEdit_16->toPlainText().toStdString());
    NewClient.string_to_char_array(NewClient.city, ui->textEdit_17->toPlainText().size()+1, ui->textEdit_17->toPlainText().toStdString());
    NewClient.string_to_char_array(NewClient.CellPhoneNumber, ui->textEdit_15->toPlainText().size()+1, ui->textEdit_15->toPlainText().toStdString());
    NewClient.access = '1';
    NewClient.ptr_start_mybuys = 0;
    NewClient.ptr_end_mybuys = 0;
    NewClient.number_mybuys = 0;

    int tmp_id;
    fstream spec_info("numbers.txt", ios::in | ios::out | ios::binary);
    spec_info.seekg(0);
    spec_info.read((char*)&tmp_id, 4);
    tmp_id++;
    NewClient.ID = tmp_id;
    //NewClient.string_to_char_array(NewClient.ID, to_string(tmp_id).size(), to_string(tmp_id));
    spec_info.seekp(0);
    spec_info.write((char*)&tmp_id, 4);
    spec_info.close();

    string newUser = ui->textEdit_14->toPlainText().toStdString();
    if(CheckUserNameClient(newUser) == false)
    {
        QMessageBox::warning(this, "اخطار","نام کاربری تکراری است");
        return;
    }

    QMessageBox::about(this, "توجه", "ثبت نام موفقیت آمیز");


    fstream database_cart("database_cart.txt",ios::in | ios::out | ios::binary);
    database_cart.seekp((NewClient.ID-1)*(3*20+1)*sizeof(int));
    int len_cart=0;
    database_cart.write((char*)&len_cart, sizeof(int));
    database_cart.close();


    clientFile.write((char*)&NewClient, sizeof(client));//change block size
    clientFile.close();
}

void SignUpClient::on_pushButton_3_clicked()//بازگشت به صصفحه قبل
{
    SignUp *p =new SignUp(this);
    p->show();
    this->hide();
}
