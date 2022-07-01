#include "listofclientforadmin.h"
#include "ui_listofclientforadmin.h"
#include "adminpage.h"
#include "client.h"
#include <fstream>
using namespace std;
ListOFClientForAdmin::ListOFClientForAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListOFClientForAdmin)
{
    ui->setupUi(this);
    QString content = "Name\tUser\tCity\tPhoneNumber";
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
    fstream cli_tmps("clients.txt", ios::in | ios::out | ios::binary);
    class client cli_tmp;
    int Count_Client = 0;
    while(cli_tmps.read((char*)&cli_tmp,137))
        Count_Client++;
    cli_tmps.close();
    fstream cli_tmps2("clients.txt", ios::in | ios::out | ios::binary);
    class customer Cli_Show[Count_Client];
    int i=0;
    while(cli_tmps2.read((char*)&Cli_Show[i],137))
        i++;
    cli_tmps2.close();
    for(i=0;i<Count_Client;i++)
    {
        string Name = Cli_Show[i].get_Name();
        string User = Cli_Show[i].get_User();
        string City = Cli_Show[i].get_city();//اسم ها بعدا باید تغییر کند و به شهر تبدیل شود به سیتی
        string phoneNumber;
        Cli_Show[i].char_array_to_string(City,11,Cli_Show[i].get_city());
        Cli_Show[i].char_array_to_string(phoneNumber,12,Cli_Show[i].get_phoneNumber());
        string x = Name+"\t" + User+"\t" + City+"\t" + phoneNumber+"\n";
        QListWidgetItem *m_textEdit = new QListWidgetItem();
        m_textEdit->setText(QString::fromStdString(x));
        ui->listWidget->addItem(m_textEdit);
    }
}

ListOFClientForAdmin::~ListOFClientForAdmin()
{
    delete ui;
}

void ListOFClientForAdmin::on_pushButton_2_clicked()
{
    AdminPage *p = new AdminPage(this);
    p->show();
    this->hide();
}
