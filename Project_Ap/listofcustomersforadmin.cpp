#include "listofcustomersforadmin.h"
#include "ui_listofcustomersforadmin.h"
#include "adminpage.h"
#include <iostream>
#include <fstream>
using namespace std;
ListOfCustomersForAdmin::ListOfCustomersForAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListOfCustomersForAdmin)
{
    ui->setupUi(this);
    this->setWindowTitle("لیست فروشندگان");
    QString content = "Name\tUser\tAddress\tPhoneNumber";
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
    fstream cus_tmps("customers.txt", ios::in | ios::out | ios::binary);
    class customer cus_tmp;
    int Count_Customer = 0;
    while(cus_tmps.read((char*)&cus_tmp,138))
        Count_Customer++;
    cus_tmps.close();
    fstream cus_tmps2("customers.txt", ios::in | ios::out | ios::binary);
    class customer Cus_Show[Count_Customer];
    int i=0;
    while(cus_tmps2.read((char*)&Cus_Show[i],138))
        i++;
    cus_tmps2.close();
    for(i=0;i<Count_Customer;i++)
    {
        string Name = Cus_Show[i].get_Name();
        string User = Cus_Show[i].get_User();
        string Address = Cus_Show[i].get_city();//اسم ها بعدا باید تغییر کند و به شهر تبدیل شود به سیتی
        string phoneNumber;
        Cus_Show[i].char_array_to_string(Address,11,Cus_Show[i].get_city());
        Cus_Show[i].char_array_to_string(phoneNumber,12,Cus_Show[i].get_phoneNumber());
        string x = Name+"\t" + User+"\t" + Address+"\t" + phoneNumber+"\n";
        QListWidgetItem *m_textEdit = new QListWidgetItem();
        m_textEdit->setText(QString::fromStdString(x));
        ui->listWidget->addItem(m_textEdit);
    }
}

ListOfCustomersForAdmin::~ListOfCustomersForAdmin()
{
    delete ui;
}

void ListOfCustomersForAdmin::on_pushButton_2_clicked()
{
    close();
    AdminPage *p = new AdminPage(this);
    p->show();
}
