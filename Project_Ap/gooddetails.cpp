#include "gooddetails.h"
#include "ui_gooddetails.h"

goodDetails::goodDetails(Product _product, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::goodDetails)
{
    ui->setupUi(this);
    Prdct = _product;
//add product info;
    string tmp;

    Prdct.char_array_to_string(tmp, 16, Prdct.get_type());
    ui->label_name->setText(QString::fromStdString(tmp));

    Prdct.char_array_to_string(tmp, 16, Prdct.get_type());

    Prdct.char_array_to_string(tmp, 16, Prdct.get_color());
    ui->label_model->setText(QString::fromStdString(tmp));

    Prdct.char_array_to_string(tmp, 49, Prdct.get_descript());
    ui->label_info->setText(QString::fromStdString(tmp));

    ui->label_id->setText(QString::number(Prdct.get_ID()));

    ui->label_price->setText(QString::number(Prdct.get_price()));

    ui->label_avail->setText(QString::number(Prdct.get_available()));

    ui->label_weight->setText(QString::number(Prdct.get_weight()));
}

goodDetails::~goodDetails()
{
    delete ui;
}

void goodDetails::on_pushButton_clicked()
{
    this->close();
}

