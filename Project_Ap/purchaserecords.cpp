#include "purchaserecords.h"
#include "ui_purchaserecords.h"
#include <fstream>

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

    fstream  database_buys("database_buys.txt",ios::in | ios::out | ios::binary);
    fstream  database_factor("database_factors.txt",ios::in | ios::out | ios::binary);
    fstream  database_clients("clients.txt",ios::in | ios::out | ios::binary);
    database_clients.seekg((clie.ID-1)*sizeof(client));
    database_clients.read((char*)&clie,sizeof(client));

    ptr_next_buy=clie.ptr_start_mybuys;
    for(int i=0;i<clie.number_mybuys;i++){
        database_buys.seekg(ptr_next_buy);
        database_buys.read((char*)&ptr_factor, sizeof(int));
        database_buys.read((char*)&ptr_next_buy, sizeof(int));

        database_factor.seekg(ptr_factor);
        database_factor.read((char*)&factor, sizeof(Factor));
        buys+=to_string(i+1)+"\t"+to_string(factor.price)+"\t"+to_string(factor.number)+"\t"+to_string(factor.ID_client)+"\t"+to_string(factor.ID_customer)+"\n";
    }
}

void PurchaseRecords::show_buys(string &buys)
{
    QString content = "ردیف\tاسم کالا\tتعداد\tقیمت\n";
    content+=QString::fromStdString(buys);
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
}
