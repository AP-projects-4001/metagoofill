#include "loginpage.h"
#include "ui_loginpage.h"
#include "signup.h"
#include "mainlogin.h"
#include <fstream>

using namespace std;
LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);

    fstream database_clients("clients.txt",  ios::app | ios::binary);
    database_clients.close();

    fstream database_customers("customers.txt",  ios::app | ios::binary);
    database_customers.close();

    fstream database_product("database_products.txt",  ios::app | ios::binary);
    database_product.close();

    fstream database_product_type("database_product_type.txt",  ios::in | ios::binary);
    if(!database_product_type){
        database_product_type.close();
        database_product_type.open("database_product_type.txt",  ios::out | ios::binary);
        int a=0;
        for(int i=0;i<18;i++){
            database_product_type.write((char*)&a, sizeof(int));
        }
    }
    database_product_type.close();

    fstream database_search("database_search.txt",ios::app | ios::binary);
    database_search.close();

    fstream  database_cart("database_cart.txt",ios::app | ios::binary);
    database_cart.close();

    fstream  database_factor("database_factors.txt", ios::app | ios::binary);
    database_factor.close();

    fstream  database_buys("database_buys.txt",ios::app | ios::binary);
    database_buys.close();

    fstream  database_sells("database_sells.txt",ios::app | ios::binary);
    database_sells.close();

    fstream numbers("numbers.txt",  ios::in | ios::binary);
    if(!numbers)
    {
        numbers.close();
        numbers.open("numbers.txt",  ios::out | ios::binary);
        int a=0;
        for(int i=0; i<6; i++)
        {
            numbers.write((char*)&a, 4);
        }
    }
    numbers.close();

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
