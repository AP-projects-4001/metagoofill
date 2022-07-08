#include "clothes_filter.h"
#include "ui_clothes_filter.h"

clothes_filter::clothes_filter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clothes_filter)
{
    ui->setupUi(this);
}

clothes_filter::~clothes_filter()
{
    delete ui;
}

void clothes_filter::on_pushButton_2_clicked()
{
    clothes_info.set_name_prod(ui->lineEdit->text().toStdString());
    clothes_info.set_price_from(ui->lineEdit_2->text().toStdString());
    clothes_info.set_price_to (ui->lineEdit_5->text().toStdString());
    clothes_info.set_customer_name( ui->lineEdit_3->text().toStdString());
    clothes_info.set_size(ui->comboBox_4->currentText().toStdString());
    clothes_info.set_age( ui->comboBox_3->currentText().toStdString());
    clothes_info.set_sex(ui->comboBox_2->currentText().toStdString());
    clothes_info.set_grouping(ui->comboBox->currentText().toStdString());
    clothes_info.set_color(ui->lineEdit_6->text().toStdString());

    emit send_clothes_info(clothes_info);
    this->close(); //or hide??
}

