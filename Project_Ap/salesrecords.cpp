#include "salesrecords.h"
#include "ui_salesrecords.h"
#include <fstream>
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

    fstream  database_sells("database_sells.txt",ios::in | ios::out | ios::binary);
    fstream  database_factor("database_factors.txt",ios::in | ios::out | ios::binary);
    fstream  database_customers("customers.txt",ios::in | ios::out | ios::binary);
    database_customers.seekg((cust.ID-1)*sizeof(customer));
    database_customers.read((char*)&cust,sizeof(customer));

    ptr_next_sell=cust.ptr_start_mysells;
    for(int i=0;i<cust.number_mysells;i++){
        database_sells.seekg(ptr_next_sell);
        database_sells.read((char*)&ptr_factor, sizeof(int));
        database_sells.read((char*)&ptr_next_sell, sizeof(int));

        database_factor.seekg(ptr_factor);
        database_factor.read((char*)&factor, sizeof(Factor));
        sells+=to_string(i+1)+"\t"+to_string(factor.price)+"\t"+to_string(factor.number)+"\t"+to_string(factor.ID_client)+"\t"+to_string(factor.ID_customer)+"\n";
    }
}

void SalesRecords::show_sells(string &sells)
{
    QString content = "ردیف\tاسم کالا\tتعداد\tقیمت\n";
    content+=QString::fromStdString(sells);
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
}
