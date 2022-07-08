#include "storecustomer.h"
#include "ui_storecustomer.h"
#include "dialog_options.h"
#include "dialog_add.h"
#include <fstream>
#include <string>
#include "customerprof.h"
#include "salesrecords.h"
#define data_product "database_products.txt"

using namespace std;

storecustomer::storecustomer(customer _cust,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::storecustomer)
{
    ui->setupUi(this);

    cust=_cust;
    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(999999999);
    ui->spinBox_2->setMinimum(0);
    ui->spinBox_2->setMaximum(999999999);


    if(cust.get_number_myproducts()>0){
        count_myproduct=1;
        ptr_file_this_myproduct=go_to_product(count_myproduct);
        show_product();
    }
    else{
        count_myproduct=0;
        show_without_product();
    }
}

storecustomer::~storecustomer()
{
    delete ui;
}

void storecustomer::on_pushButten_add_clicked()
{
    Dialog_options *d=new Dialog_options(this);
    connect(d,SIGNAL(item_added(bool,bool,bool,bool)),this,SLOT(item_added(bool,bool,bool,bool)));
    d->show();
}

void storecustomer::on_pushButten_delete_clicked()
{
    if(count_myproduct>1){
        delete_product();
        count_myproduct--;
        ptr_file_this_myproduct=go_to_product(count_myproduct);
        show_product();
    }
    else if(cust.get_number_myproducts()==1){
        delete_product();
        count_myproduct=0;
        show_without_product();
    }
    else if(count_myproduct==1){
        delete_product();
        ptr_file_this_myproduct=go_to_product(count_myproduct);
        show_product();
    }
}

void storecustomer::on_pushButton_save_clicked()
{
    if(count_myproduct!=0){
        product.set_price(ui->spinBox->value());
        product.set_available(ui->spinBox_2->value());
        product.string_to_char_array((ui->plainTextEdit_descript->toPlainText()).toStdString(),49,product.get_descript());
        save_product();
        show_product();
    }
}

void storecustomer::on_pushButton_next_clicked()
{
    fstream database_product(data_product, ios::in | ios::out | ios::binary);
    if(count_myproduct<cust.get_number_myproducts()){
        database_product.seekg(product.get_ptr_file_myproduct_next());
        ptr_file_this_myproduct=product.get_ptr_file_myproduct_next();
        database_product.read((char*)&product,sizeof(Product));
        count_myproduct++;
        show_product();
    }
    database_product.close();
}

void storecustomer::on_pushButton_before_clicked()
{
    fstream database_product(data_product,  ios::in | ios::out | ios::binary);
    if(count_myproduct>1){
        database_product.seekg(product.get_ptr_file_myproduct_preview());
        ptr_file_this_myproduct=product.get_ptr_file_myproduct_preview();
        database_product.read((char*)&product, sizeof(Product));
        count_myproduct--;
        show_product();
    }
    database_product.close();
}

void storecustomer::item_added(bool flag_berand,bool flag_color,bool flag_weight,bool flag_numerical)
{
    Dialog_add *d2=new Dialog_add(flag_berand,flag_color,flag_weight,flag_numerical,this);
    connect(d2,SIGNAL(item_added2(QString,int,QString,QString,int,int,QString,bool,bool,bool,bool)),this,SLOT(item_added2(QString,int,QString,QString,int,int,QString,bool,bool,bool,bool)));
    d2->show();
}

void storecustomer::item_added2(QString type,int price,QString berand,QString color,int weight,int available,QString descript,bool flag_berand,bool flag_color,bool flag_weight,bool flag_numerical)
{

    product.string_to_char_array(type.toStdString(),16,product.get_type());
    product.string_to_char_array(berand.toStdString(),16,product.get_berand());
    product.string_to_char_array(color.toStdString(),16,product.get_color());
    product.string_to_char_array(descript.toStdString(),49,product.get_descript());


    product.set_price(price);
    product.set_weight(weight);
    product.set_available(available);

    product.set_flag_berand(flag_berand);
    product.set_flag_color(flag_color);
    product.set_flag_weight( flag_weight);
    product.set_flag_numerical( flag_numerical);
    product.set_flag_delete_product( 0);
    product.set_ID_customer( cust.get_ID());

    add_product();
    add_product_to_type();
    count_myproduct=cust.get_number_myproducts();
    ptr_file_this_myproduct=go_to_product(count_myproduct);
    show_product();
}

void storecustomer::show_product()
{
    string str;

    product.char_array_to_string(str,16,cust.get_Name());
    ui->label_store->setText(QString::fromStdString(str));

    product.char_array_to_string(str,16,product.get_type());
    ui->label_type->setText(QString::fromStdString(str));

    if(product.get_flag_numerical()==1){
        ui->label_price_->setText("قیمت هر عدد:");
    }
    else{
        ui->label_price_->setText("قیمت هر کیلو:");
    }

    ui->spinBox->setValue(product.get_price());

    if(product.get_flag_berand()==1){
        ui->label_berand_->show();
        ui->label_berand->show();
        product.char_array_to_string(str,16,product.get_berand());
        ui->label_berand->setText(QString::fromStdString(str));
    }
    else{
        ui->label_berand_->hide();
        ui->label_berand->hide();
    }

    if(product.get_flag_color()==1){
        ui->label_color_->show();
        ui->label_color->show();
        product.char_array_to_string(str,16,product.get_color());
        ui->label_color->setText(QString::fromStdString(str));
    }
    else{
        ui->label_color_->hide();
        ui->label_color->hide();
    }

    if(product.get_flag_weight()==1){
        ui->label_weight_->show();
        ui->label_weight->show();
        ui->label_weight->setText(QString::number(product.get_weight()));
    }
    else{
        ui->label_weight_->hide();
        ui->label_weight->hide();
    }

    ui->spinBox_2->setValue(product.get_available());

    product.char_array_to_string(str,49,product.get_descript());
    ui->plainTextEdit_descript->setPlainText(QString::fromStdString(str));

    ui->label_count->setText(QString::number(count_myproduct));

    ui->label_number->setText(QString::number(cust.get_number_myproducts()));

    ui->label_id->setText(QString::number(product.get_ID()));
}

int storecustomer::go_to_product(int count)
{
    int ptr_file;

    fstream database_product(data_product,  ios::in | ios::out | ios::binary);

    product.set_ptr_file_myproduct_next(cust.get_ptr_start_myproducts());
    for(int i=0;i<count;i++){
        ptr_file=product.get_ptr_file_myproduct_next();
        database_product.seekg(ptr_file);
        database_product.read((char*)&product,sizeof(Product));
    }
    database_product.close();
    return ptr_file;
}

void storecustomer::save_product()
{
    fstream database_product(data_product,  ios::in | ios::out | ios::binary);
    database_product.seekp(ptr_file_this_myproduct);
    database_product.write((char *)&product, sizeof(Product));
    database_product.close();
}

void storecustomer::add_product()
{
    int ptr_file;

    fstream database_numbers("numbers.txt", ios::in | ios::out | ios::binary);
    database_numbers.seekg((3-1)*sizeof(int));
    database_numbers.read((char*)&number_products, sizeof(int));

    fstream database_product(data_product,  ios::in | ios::out | ios::binary);

    product2.set_ptr_file_myproduct_next(cust.get_ptr_start_myproducts());
    for(int i=0;i<cust.get_number_myproducts();i++){
        ptr_file=product2.get_ptr_file_myproduct_next();
        database_product.seekg(ptr_file);
        database_product.read((char*)&product2, sizeof(Product));
    }

    if(cust.get_number_myproducts()!=0){
        product2.set_ptr_file_myproduct_next(number_products*sizeof(Product));
        database_product.seekp(ptr_file);
        database_product.write((char *)&product2, sizeof(Product));

        product.set_ptr_file_myproduct_preview(ptr_file);
    }
    else{
        cust.set_ptr_start_myproducts(number_products*sizeof(Product));
    }
    product.set_ID(number_products+1);
    database_product.seekp(number_products*sizeof(Product));
    database_product.write((char *)&product, sizeof(Product));

    number_products++;
    cust.set_number_myproducts(cust.get_number_myproducts()+1);

    fstream database_cust("customers.txt",  ios::in | ios::out | ios::binary);
    database_cust.seekp((cust.get_ID()-1)*sizeof(customer));
    database_cust.write((char *)&cust, sizeof(customer));
    database_cust.close();

    database_numbers.seekp((3-1)*sizeof(int));
    database_numbers.write((char*)&number_products, sizeof(int));

    database_product.close();
    database_numbers.close();
}

void storecustomer::delete_product()
{
    int temp_ptr_file;
    int temp_ptr_file2;
    fstream database_product(data_product,  ios::in | ios::out | ios::binary);

    product.set_flag_delete_product(1);
    database_product.seekp(ptr_file_this_myproduct);
    database_product.write((char *)&product, sizeof(Product));

    temp_ptr_file=product.get_ptr_file_myproduct_next();
    temp_ptr_file2=product.get_ptr_file_myproduct_preview();

    if(count_myproduct>1){
        database_product.seekg(temp_ptr_file2);
        database_product.read((char*)&product, sizeof(Product));
        product.set_ptr_file_myproduct_next(temp_ptr_file);
        database_product.seekp(temp_ptr_file2);
        database_product.write((char *)&product, sizeof(Product));
    }
    else{
        cust.set_ptr_start_myproducts(temp_ptr_file);
    }

    if(count_myproduct<cust.get_number_myproducts()){
        database_product.seekg(temp_ptr_file);
        database_product.read((char*)&product, sizeof(Product));
        product.set_ptr_file_myproduct_preview(temp_ptr_file2);
        database_product.seekp(temp_ptr_file);
        database_product.write((char *)&product, sizeof(Product));
    }

    cust.set_number_myproducts(cust.get_number_myproducts()-1);

    fstream database_cust("customers.txt",  ios::in | ios::out | ios::binary);
    database_cust.seekp((cust.get_ID()-1)*sizeof(customer));
    database_cust.write((char *)&cust, sizeof(customer));
    database_cust.close();

    database_product.close();
}

void storecustomer::show_without_product()
{
    string str;

    product.char_array_to_string(str,16,cust.get_Name());
    ui->label_store->setText(QString::fromStdString(str));

    ui->label_type_->show();
    ui->label_type->setText("");
    ui->label_price_->setText("قیمت هر عدد:");
    ui->spinBox->setValue(0);
    ui->label_berand_->show();
    ui->label_berand->setText("");
    ui->label_color_->show();
    ui->label_color->setText("");
    ui->label_weight_->show();
    ui->label_weight->setText("");
    ui->label_id->setText("");
    ui->plainTextEdit_descript->setPlainText("");
    ui->spinBox_2->setValue(0);

    ui->label_number->setText(QString::number(cust.get_number_myproducts()));
    ui->label_count->setText(QString::number(count_myproduct));
}

void storecustomer::add_product_to_type()
{
    fstream database_product_type("database_product_type.txt",  ios::in | ios::out | ios::binary);
    database_product_type.seekg(cust.get_ProductType()*3*sizeof(int));
    database_product_type.read((char*)&ptr_start_file_product_type, sizeof(int));
    database_product_type.read((char*)&ptr_end_file_product_type, sizeof(int));
    database_product_type.read((char*)&number_product_type, sizeof(int));

    fstream database_product(data_product,  ios::in | ios::out | ios::binary);


    if(number_product_type!=0){

        database_product.seekg(ptr_end_file_product_type);
        database_product.read((char*)&product2, sizeof(Product));
        product2.set_ptr_file_product_type_next((number_products-1)*sizeof(Product));
        database_product.seekp(ptr_end_file_product_type);
        database_product.write((char *)&product2, sizeof(Product));
        product.set_ptr_file_product_type_preview(ptr_end_file_product_type);
        ptr_end_file_product_type=(number_products-1)*sizeof(Product);
    }
    else{
        ptr_start_file_product_type=(number_products-1)*sizeof(Product);
        ptr_end_file_product_type=(number_products-1)*sizeof(Product);
    }

    database_product.seekp((number_products-1)*sizeof(Product));
    database_product.write((char *)&product, sizeof(Product));

    number_product_type++;

    database_product_type.seekp(cust.get_ProductType()*3*sizeof(int));
    database_product_type.write((char*)&ptr_start_file_product_type, sizeof(int));
    database_product_type.write((char*)&ptr_end_file_product_type, sizeof(int));
    database_product_type.write((char*)&number_product_type, sizeof(int));

    database_product.close();
    database_product_type.close();
}


void storecustomer::on_pushButton_2_clicked()
{
    customerProf *d=new customerProf(cust);
    d->show();
    this->close();
}
