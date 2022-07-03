#include "salesrecords.h"
#include "ui_salesrecords.h"
#include <fstream>
using namespace std;
SalesRecords::SalesRecords(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalesRecords)
{
    ui->setupUi(this);
    QString content = "اسم کالا\tتعداد\tقیمت";
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
}

SalesRecords::~SalesRecords()
{
    delete ui;
}

void SalesRecords::search_in_sells()
{
    int ptr_factor;
    int ptr_next_sell;

    fstream  database_customers("customers.txt",ios::in | ios::out | ios::binary);
    database_customers.seekg((cust.ID-1)*sizeof(customer));
    database_customers.read((char*)&cust,sizeof(customer));


    fstream database_sells("database_sells.txt",ios::in | ios::out | ios::binary);
    fstream database_search("database_search.txt",ios::in | ios::out | ios::binary);

    database_search.seekp(0);
    ptr_next_sell=ptr_start_mysells;
    for(int i=0;i<number_mysells;i++){
        database_sells.seekg(ptr_next_sell);
        database_sells.read((char*)&ptr_factor, sizeof(int));
        database_sells.read((char*)&ptr_next_sell, sizeof(int));

        database_search.write((char *)&ptr_factor, sizeof(int));

    }
    len_search=number_mysells;
}
