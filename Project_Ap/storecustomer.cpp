#include "storecustomer.h"
#include "ui_storecustomer.h"
#include "dialog_options.h"
#include "dialog_add.h"
#include <fstream>
#include <string>
#include "customerprof.h"
#define data_product "database_products.txt"

using namespace std;

storecustomer::storecustomer(customer _cust,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::storecustomer)
{
    ui->setupUi(this);

    cust=_cust;

    number_products=0;//موقتی

    if(cust.number_myproducts>0){
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
    else if(cust.number_myproducts==1){
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
        product.price=(ui->lineEdit_price->text()).toInt();
        product.available=(ui->lineEdit_available->text()).toInt();
        product.string_to_char_array((ui->plainTextEdit_descript->toPlainText()).toStdString(),49,product.descript);
        save_product();
        show_product();
    }
}

void storecustomer::on_pushButton_next_clicked()
{
    fstream database_product(data_product, ios::in | ios::out | ios::binary);
    if(count_myproduct<cust.number_myproducts){
        database_product.seekg(product.ptr_file_myproduct_next);
        ptr_file_this_myproduct=product.ptr_file_myproduct_next;
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
        database_product.seekg(product.ptr_file_myproduct_preview);
        ptr_file_this_myproduct=product.ptr_file_myproduct_preview;
        database_product.read((char*)&product, sizeof(Product));
        count_myproduct--;
        show_product();
    }
    database_product.close();
}

void storecustomer::item_added(bool flag_berand,bool flag_color,bool flag_weight,bool flag_numerical)
{
    Dialog_add *d2=new Dialog_add(flag_berand,flag_color,flag_weight,flag_numerical,this);
    connect(d2,SIGNAL(item_added2(QString,QString,QString,QString,QString,QString,QString,bool,bool,bool,bool)),this,SLOT(item_added2(QString,QString,QString,QString,QString,QString,QString,bool,bool,bool,bool)));
    d2->show();
}

void storecustomer::item_added2(QString type,QString price,QString berand,QString color,QString weight,QString available,QString descript,bool flag_berand,bool flag_color,bool flag_weight,bool flag_numerical)
{

    product.string_to_char_array(type.toStdString(),16,product.type);
    product.string_to_char_array(berand.toStdString(),16,product.berand);
    product.string_to_char_array(color.toStdString(),16,product.color);
    product.string_to_char_array(descript.toStdString(),49,product.descript);


    product.price=price.toInt();
    product.weight=weight.toInt();
    product.available=available.toInt();

    product.flag_berand=flag_berand;
    product.flag_color=flag_color;
    product.flag_weight=flag_weight;
    product.flag_numerical=flag_numerical;
    product.flag_delete_product=0;
    product.ID=number_products+1;
    product.ID_customer=cust.ID;

    add_product();
    add_product_to_type();
    count_myproduct=cust.number_myproducts;
    ptr_file_this_myproduct=go_to_product(count_myproduct);
    show_product();
}

void storecustomer::show_product()
{
    string str;
    product.char_array_to_string(str,16,product.type);
    ui->label_type->setText(QString::fromStdString(str));

    if(product.flag_numerical==1){
        ui->label_price_->setText("قیمت هر عدد:");
    }
    else{
        ui->label_price_->setText("قیمت هر کیلو:");
    }

    ui->lineEdit_price->setText(QString::number(product.price));

    if(product.flag_berand==1){
        ui->label_berand_->show();
        ui->label_berand->show();
        product.char_array_to_string(str,16,product.berand);
        ui->label_berand->setText(QString::fromStdString(str));
    }
    else{
        ui->label_berand_->hide();
        ui->label_berand->hide();
    }

    if(product.flag_color==1){
        ui->label_color_->show();
        ui->label_color->show();
        product.char_array_to_string(str,16,product.color);
        ui->label_color->setText(QString::fromStdString(str));
    }
    else{
        ui->label_color_->hide();
        ui->label_color->hide();
    }

    if(product.flag_weight==1){
        ui->label_weight_->show();
        ui->label_weight->show();
        ui->label_weight->setText(QString::number(product.weight));
    }
    else{
        ui->label_weight_->hide();
        ui->label_weight->hide();
    }

    ui->lineEdit_available->setText(QString::number(product.available));

    product.char_array_to_string(str,49,product.descript);
    ui->plainTextEdit_descript->setPlainText(QString::fromStdString(str));

    ui->label_count->setText(QString::number(count_myproduct));

    ui->label_number->setText(QString::number(cust.number_myproducts));

    ui->label_id->setText(QString::number(product.ID));
}

int storecustomer::go_to_product(int count)
{
    int ptr_file;

    fstream database_product(data_product,  ios::in | ios::out | ios::binary);

    product.ptr_file_myproduct_next=ptr_file_myproduct;
    for(int i=0;i<count;i++){
        ptr_file=product.ptr_file_myproduct_next;
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
    fstream database_product(data_product,  ios::in | ios::out | ios::binary);


    product2.ptr_file_myproduct_next=ptr_file_myproduct;
    for(int i=0;i<cust.number_myproducts;i++){
        ptr_file=product2.ptr_file_myproduct_next;
        database_product.seekg(ptr_file);
        database_product.read((char*)&product2, sizeof(Product));
    }

    if(cust.number_myproducts!=0){
        product2.ptr_file_myproduct_next=number_products*sizeof(Product);
        database_product.seekp(ptr_file);
        database_product.write((char *)&product2, sizeof(Product));

        product.ptr_file_myproduct_preview=ptr_file;
    }
    else{
        ptr_file_myproduct=number_products*sizeof(Product);
    }

    database_product.seekp(number_products*sizeof(Product));
    database_product.write((char *)&product, sizeof(Product));

    number_products++;
    cust.number_myproducts++;

    database_product.close();
}

void storecustomer::delete_product()
{
    int temp_ptr_file;
    int temp_ptr_file2;
    fstream database_product(data_product,  ios::in | ios::out | ios::binary);

    product.flag_delete_product=1;
    database_product.seekp(ptr_file_this_myproduct);
    database_product.write((char *)&product, sizeof(Product));

    temp_ptr_file=product.ptr_file_myproduct_next;
    temp_ptr_file2=product.ptr_file_myproduct_preview;

    if(count_myproduct>1){
        database_product.seekg(temp_ptr_file2);
        database_product.read((char*)&product, sizeof(Product));
        product.ptr_file_myproduct_next=temp_ptr_file;
        database_product.seekp(temp_ptr_file2);
        database_product.write((char *)&product, sizeof(Product));
    }
    else{
        ptr_file_myproduct=temp_ptr_file;
    }

    if(count_myproduct<cust.number_myproducts){
        database_product.seekg(temp_ptr_file);
        database_product.read((char*)&product, sizeof(Product));
        product.ptr_file_myproduct_preview=temp_ptr_file2;
        database_product.seekp(temp_ptr_file);
        database_product.write((char *)&product, sizeof(Product));
    }

    cust.number_myproducts--;

    //database_cust.seekp((cust.ID-1)*sizeof(customer));
   // database_product_type.write((char*)&ptr_start_file_product_type, sizeof(int));
    //database_product_type.write((char*)&ptr_end_file_product_type, sizeof(int));
    //database_product_type.write((char*)&number_product_type, sizeof(int));

    database_product.close();
}

void storecustomer::show_without_product()
{
    ui->label_type_->show();
    ui->label_type->setText("");
    ui->label_price_->setText("قیمت هر عدد:");
    ui->lineEdit_price->setText("");
    ui->label_berand_->show();
    ui->label_berand->setText("");
    ui->label_color_->show();
    ui->label_color->setText("");
    ui->label_weight_->show();
    ui->label_weight->setText("");
    ui->label_id->setText("");
    ui->plainTextEdit_descript->setPlainText("");
    ui->lineEdit_available->setText("");

    ui->label_number->setText(QString::number(cust.number_myproducts));
    ui->label_count->setText(QString::number(count_myproduct));
}

void storecustomer::add_product_to_type()
{
    fstream database_product_type("database_product_type.txt",  ios::in | ios::out | ios::binary);
    database_product_type.seekg(cust.ProductType*3*sizeof(int));
    database_product_type.read((char*)&ptr_start_file_product_type, sizeof(int));
    database_product_type.read((char*)&ptr_end_file_product_type, sizeof(int));
    database_product_type.read((char*)&number_product_type, sizeof(int));

    fstream database_product(data_product,  ios::in | ios::out | ios::binary);


    if(number_product_type!=0){

        database_product.seekg(ptr_end_file_product_type);
        database_product.read((char*)&product2, sizeof(Product));
        product2.ptr_file_product_type_next=(number_products-1)*sizeof(Product);
        database_product.seekp(ptr_end_file_product_type);
        database_product.write((char *)&product2, sizeof(Product));
        product.ptr_file_product_type_preview=ptr_end_file_product_type;
        ptr_end_file_product_type=(number_products-1)*sizeof(Product);
    }
    else{
        ptr_start_file_product_type=(number_products-1)*sizeof(Product);
        ptr_end_file_product_type=(number_products-1)*sizeof(Product);
    }

    database_product.seekp((number_products-1)*sizeof(Product));
    database_product.write((char *)&product, sizeof(Product));

    number_product_type++;

    database_product_type.seekp(cust.ProductType*3*sizeof(int));
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

void storecustomer::on_pushButton_clicked()
{
    //صفحه سوایق فروش
}

void storecustomer::on_pushButton_3_clicked()
{
    //طرح های تبلیغاتی
}
