#include "listoftransactions.h"
#include "ui_listoftransactions.h"
#include "adminpage.h"
#include "factor.h"
#include <fstream>
using namespace std;

listoftransactions::listoftransactions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listoftransactions)
{
    ui->setupUi(this);
    this->setWindowTitle("لیست تراکنش ها");
    QString content = "shop\tclient\tproduct\tprice\tnumber";
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);

    ifstream factors("database_factors.txt", ios::in | ios::binary);
    ifstream clients("clients.txt", ios::in | ios::binary);
    ifstream customers("customers.txt", ios::in | ios::binary);

    string shop_name;
    string client_name;
    string product_name;
    string _price;
    string _number;

    Factor fac;
    client cli;
    customer cus;

    while(factors.read((char*)&fac, sizeof(Factor)))
    {
        _price = to_string(fac.price);
        _number = to_string(fac.number);

        clients.seekg((fac.ID_client-1)*sizeof(client));
        cli.char_array_to_string(client_name, 16, cli.get_Name());


        customers.seekg((fac.ID_customer-1)*sizeof(customer));
        cus.char_array_to_string(shop_name, 16, cus.get_Name());

//        while(clients.read((char*)&cli, sizeof(client)))
//        {
//            if(cli.ID == fac.ID_client)
//            {
//                cli.char_array_to_string(client_name, 16, cli.get_Name());
//                clients.seekg(0);
//                break;
//            }
//        }

//        while(customers.read((char*)&cus, sizeof(customer)))
//        {
//            if(cus.ID == fac.ID_customer)
//            {
//                cus.char_array_to_string(shop_name, 16, cus.get_Name());
//                customers.seekg(0);
//                break;
//            }
//        }

        string x = shop_name+"\t" + client_name+"\t" + product_name+"\t" + _price+"\t"+_number+ "\n";
        QListWidgetItem *m_textEdit = new QListWidgetItem();
        m_textEdit->setText(QString::fromStdString(x));
        ui->listWidget->addItem(m_textEdit);
    }
    factors.close();
    clients.close();
    customers.close();
}

listoftransactions::~listoftransactions()
{
    delete ui;
}

void listoftransactions::search_in_transactions()
{

}

void listoftransactions::on_pushButton_clicked()
{
    close();
    AdminPage *p = new AdminPage(this);
    p->show();
}
