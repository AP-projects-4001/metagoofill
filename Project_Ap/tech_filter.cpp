#include "tech_filter.h"
#include "ui_tech_filter.h"

tech_filter::tech_filter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tech_filter)
{
    ui->setupUi(this);
}

tech_filter::~tech_filter()
{
    delete ui;
}

void tech_filter::on_pushButton_2_clicked()
{
    tech_info.set_name_prod(ui->lineEdit->text().toStdString());
    tech_info.set_price_from(ui->lineEdit_2->text().toStdString());
    tech_info.set_price_to(ui->lineEdit_5->text().toStdString());
    tech_info.set_customer_name(ui->lineEdit_3->text().toStdString());
    tech_info.set_grouping(ui->comboBox->currentText().toStdString());
    tech_info.set_color(ui->lineEdit_6->text().toStdString());

    emit send_tech_info(tech_info);
    this->close();
}

