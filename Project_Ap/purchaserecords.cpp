#include "purchaserecords.h"
#include "ui_purchaserecords.h"
#include <fstream>

using namespace std;
PurchaseRecords::PurchaseRecords(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PurchaseRecords)
{
    ui->setupUi(this);
    QString content = "ردیف\tاسم کالا\tتعداد\tقیمت";
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
}

PurchaseRecords::~PurchaseRecords()
{
    delete ui;
}

void PurchaseRecords::search_in_buys()
{
    int ptr_factor;
    int ptr_next_buy;

    fstream  database_clients("clients.txt",ios::in | ios::out | ios::binary);
    database_clients.seekg((clie.ID-1)*sizeof(client));
    database_clients.read((char*)&clie,sizeof(client));


    fstream database_buys("database_buys.txt",ios::in | ios::out | ios::binary);
    fstream database_search("database_search.txt",ios::in | ios::out | ios::binary);

    database_search.seekp(0);
    ptr_next_buy=ptr_start_mybuys;
    for(int i=0;i<number_mybuys;i++){
        database_buys.seekg(ptr_next_buy);
        database_buys.read((char*)&ptr_factor, sizeof(int));
        database_buys.read((char*)&ptr_next_buy, sizeof(int));

        database_search.write((char *)&ptr_factor, sizeof(int));

    }
    len_search=number_mybuys;
}

void PurchaseRecords::next_to_search(int part)
{
    int ptr_file;
    if(count!=len_search){
        fstream database_factors("database_factors",ios::in | ios::out | ios::binary);
        fstream database_search("database_search.txt",ios::in | ios::out | ios::binary);

        database_search.seekg((count)*sizeof(int));
        end_part_buys=len_search-count;
        if(end_part_buys>=part-1){end_part_buys=part;}
        for(int i=0;i<end_part_buys;i++){
            database_search.read((char *)&ptr_file, sizeof(int));
            database_factors.seekg(ptr_file);
            database_factors.read((char*)&factors[i], sizeof(Factor));
        }
        count+=end_part_buys;
    }
}

void PurchaseRecords::preview_to_search(int part)
{
    int ptr_file;

    if(count>=(end_part_buys+part)){
        count-=end_part_buys;
        count-=part;
        end_part_buys=part;
        fstream database_factors("database_factors",ios::in | ios::out | ios::binary);
        fstream database_search("database_search.txt",ios::in | ios::out | ios::binary);

        database_search.seekg((count)*sizeof(int));

        for(int i=0;i<end_part_buys;i++){
            database_search.read((char *)&ptr_file, sizeof(int));
            database_factors.seekg(ptr_file);
            database_factors.read((char*)&factors[i], sizeof(Factor));
        }
        count+=end_part_buys;
    }
}
