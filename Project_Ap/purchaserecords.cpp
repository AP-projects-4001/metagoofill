#include "purchaserecords.h"
#include "ui_purchaserecords.h"
#include "clientprof.h"
#include <fstream>
#include "gooddetails.h"
using namespace std;
PurchaseRecords::PurchaseRecords(client _clie,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PurchaseRecords)
{
    ui->setupUi(this);
    clie=_clie;
    string buys;
    search_in_buys(buys);
    show_buys(buys);
}

PurchaseRecords::~PurchaseRecords()
{
    delete ui;
}

void PurchaseRecords::search_in_buys(string &buys)
{
    buys="";
    int ptr_factor;
    int ptr_next_buy;
    string product_name;
    string shop_name;

    fstream  database_buys("database_buys.txt",ios::in | ios::out | ios::binary);
    fstream  database_factor("database_factors.txt",ios::in | ios::out | ios::binary);
    fstream  database_clients("clients.txt",ios::in | ios::out | ios::binary);
    fstream database_customers("customers.txt", ios::in | ios::out | ios::binary);
    fstream database_product("database_products.txt",  ios::in | ios::out | ios::binary);

    database_clients.seekg((clie.get_ID()-1)*sizeof(client));
    database_clients.read((char*)&clie,sizeof(client));

    ptr_next_buy=clie.get_ptr_start_mybuys();
    for(int i=0;i<clie.get_number_mybuys();i++){
        database_buys.seekg(ptr_next_buy);
        database_buys.read((char*)&ptr_factor, sizeof(int));
        database_buys.read((char*)&ptr_next_buy, sizeof(int));

        database_factor.seekg(ptr_factor);
        database_factor.read((char*)&factor, sizeof(Factor));

        database_customers.seekg((factor.ID_customer-1)*sizeof(customer));
        database_customers.read((char*)&cust,sizeof(customer));
        cust.char_array_to_string(shop_name,16,cust.get_Name());

        database_product.seekg(factor.ptr_product);
        database_product.read((char*)&product, sizeof(Product));
        product.char_array_to_string(product_name,16,product.get_type());

        buys+=to_string(i+1)+"\t"+product_name+"\t"+to_string(factor.number*factor.price)+"\t"+to_string(factor.number)+"\t"+shop_name+"\n";
    }
    database_buys.close();
    database_factor.close();
    database_clients.close();
    database_customers.close();
    database_product.close();
}

void PurchaseRecords::show_buys(string &buys)
{
    QString content = "ردیف\tاسم کالا\tتعداد\tقیمت\n";
    content+=QString::fromStdString(buys);
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
}

void PurchaseRecords::go_to_factor(int radif)
{
    int ptr_factor;
    int ptr_next_buy;

    fstream  database_buys("database_buys.txt",ios::in | ios::out | ios::binary);
    fstream  database_factor("database_factors.txt",ios::in | ios::out | ios::binary);
    fstream  database_clients("clients.txt",ios::in | ios::out | ios::binary);
    fstream database_product("database_products.txt",  ios::in | ios::out | ios::binary);

    database_clients.seekg((clie.get_ID()-1)*sizeof(client));
    database_clients.read((char*)&clie,sizeof(client));
    if(radif<=clie.get_number_mybuys()){
        ptr_next_buy=clie.get_ptr_start_mybuys();
        for(int i=0;i<radif;i++){
            database_buys.seekg(ptr_next_buy);
            database_buys.read((char*)&ptr_factor, sizeof(int));
            database_buys.read((char*)&ptr_next_buy, sizeof(int));
        }
        database_factor.seekg(ptr_factor);
        database_factor.read((char*)&factor, sizeof(Factor));

        database_product.seekg(factor.ptr_product);
        database_product.read((char*)&product, sizeof(Product));

        goodDetails *details = new goodDetails(product, this);
        details->show();
    }
    database_buys.close();
    database_factor.close();
    database_clients.close();
    database_product.close();
}

void PurchaseRecords::on_pushButton_2_clicked()
{
    this->close();
    clientProf *reprof = new clientProf(clie);
    reprof->show();
}


void PurchaseRecords::on_pushButton_clicked()
{
    go_to_factor((ui->textEdit->toPlainText()).toInt());
}
