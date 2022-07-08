#include "fruitandveg_filter.h"
#include "ui_fruitandveg_filter.h"

fruitandveg_filter::fruitandveg_filter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fruitandveg_filter)
{
    ui->setupUi(this);
}

fruitandveg_filter::~fruitandveg_filter()
{
    delete ui;
}

void fruitandveg_filter::on_pushButton_2_clicked()
{
    fruit_info.set_name_prod(ui->lineEdit->text().toStdString());
    fruit_info.set_price_from(ui->lineEdit_2->text().toStdString());
    fruit_info.set_price_to(ui->lineEdit_5->text().toStdString());
    fruit_info.set_customer_name(ui->lineEdit_3->text().toStdString());
    fruit_info.set_color(ui->lineEdit_4->text().toStdString());

    emit send_fruits_info(fruit_info);
    this->close();
}

