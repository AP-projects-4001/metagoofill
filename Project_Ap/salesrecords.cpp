#include "salesrecords.h"
#include "ui_salesrecords.h"
#include <fstream>
#include "customerprof.h"
using namespace std;
SalesRecords::SalesRecords(customer _cust,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalesRecords)
{
    ui->setupUi(this);
    cust=_cust;
    string sells;
    search_in_sells(sells);
    show_sells(sells);
}

SalesRecords::~SalesRecords()
{
    delete ui;
}

void SalesRecords::search_in_sells(string &sells)
{
    sells="";
    int ptr_factor;
    int ptr_next_sell;
    string product_name;
    string client_user;

    fstream  database_sells("database_sells.txt",ios::in | ios::out | ios::binary);
    fstream  database_factor("database_factors.txt",ios::in | ios::out | ios::binary);
    fstream  database_clients("clients.txt",ios::in | ios::out | ios::binary);
    fstream database_customers("customers.txt", ios::in | ios::out | ios::binary);
    fstream database_product("database_products.txt",  ios::in | ios::out | ios::binary);

    database_customers.seekg((cust.get_ID()-1)*sizeof(customer));
    database_customers.read((char*)&cust,sizeof(customer));

    ptr_next_sell=cust.get_ptr_start_mysells();
    for(int i=0;i<cust.get_number_mysells();i++){
        database_sells.seekg(ptr_next_sell);
        database_sells.read((char*)&ptr_factor, sizeof(int));
        database_sells.read((char*)&ptr_next_sell, sizeof(int));

        database_factor.seekg(ptr_factor);
        database_factor.read((char*)&factor, sizeof(Factor));

        database_clients.seekg((factor.get_ID_client()-1)*sizeof(client));
        database_clients.read((char*)&clie,sizeof(client));
        clie.char_array_to_string(client_user,16,clie.get_User());

        database_product.seekg(factor.get_ptr_product());
        database_product.read((char*)&product, sizeof(Product));
        product.char_array_to_string(product_name,16,product.get_type());

        sells+=to_string(i+1)+"\t"+product_name+"\t"+to_string(factor.get_price())+"\t"+to_string(factor.get_number())+"\t"+client_user+"\n";
    }

    database_sells.close();
    database_factor.close();
    database_clients.close();
    database_customers.close();
    database_product.close();
}

void SalesRecords::show_sells(string &sells)
{
    QString content = "ردیف\tاسم کالا\tتعداد\tقیمت\n";
    content+=QString::fromStdString(sells);
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
}

void SalesRecords::on_pushButton_2_clicked()
{
    this->close();
    customerProf *reprof = new customerProf(cust);
    reprof->show();
}
