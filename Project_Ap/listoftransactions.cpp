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
    string fac;
    search_in_factors(fac);
    show_factors(fac);
}

listoftransactions::~listoftransactions()
{
    delete ui;
}

void listoftransactions::search_in_factors(string &fac)
{
    int number_factors;
    ifstream factors("database_factors.txt", ios::in | ios::binary);
    ifstream clients("clients.txt", ios::in | ios::binary);
    ifstream customers("customers.txt", ios::in | ios::binary);
    ifstream products("database_products.txt", ios::in | ios::binary);

    ifstream numbers("numbers.txt", ios::in | ios::binary);
    numbers.seekg((4-1)*sizeof(int));
    numbers.read((char*)&number_factors, sizeof(int));

    string shop_name;
    string customer_user;
    string client_user;
    string product_name;
    string _price;
    string _number;

    factors.seekg(0);
    for(int i=0;i<number_factors;i++)
    {
        factors.read((char*)&factor, sizeof(Factor));
        _price = to_string(factor.get_price());
        _number = to_string(factor.get_number());

        clients.seekg((factor.get_ID_client()-1)*sizeof(client));
        clients.read((char*)&clie, sizeof(client));
        clie.char_array_to_string(client_user, 16, clie.get_User());

        customers.seekg((factor.get_ID_customer()-1)*sizeof(customer));
        customers.read((char*)&cust, sizeof(customer));
        cust.char_array_to_string(shop_name, 16, cust.get_Name());
        cust.char_array_to_string(customer_user, 16, cust.get_User());

        products.seekg(factor.get_ptr_product());
        products.read((char*)&product, sizeof(Product));
        product.char_array_to_string(product_name,16,product.get_type());

        fac += to_string(i+1)+"\t"+shop_name+"\t"+ customer_user+"\t"+ client_user+"\t" + product_name+"\t" + _price+"\t"+_number+ "\n";
    }
    factors.close();
    clients.close();
    customers.close();
    products.close();
    numbers.close();
}

void listoftransactions::show_factors(string &fac)
{
    QString content = "\tshop\tcus       client\tproduct\tprice\tnumber\n";
    content+=QString::fromStdString(fac);
    QListWidgetItem *m_textEdit = new QListWidgetItem(content);
    ui->listWidget->addItem(m_textEdit);
}

void listoftransactions::on_pushButton_clicked()
{
    this->close();
    AdminPage *p = new AdminPage();
    p->show();
}
