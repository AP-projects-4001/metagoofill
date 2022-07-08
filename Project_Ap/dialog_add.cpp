#include "dialog_add.h"
#include "ui_dialog_add.h"
#include <QMessageBox>

Dialog_add::Dialog_add(bool _flag_berand,bool _flag_color,bool _flag_weight,bool _flag_numerical,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_add)
{
    ui->setupUi(this);

    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(999999999);
    ui->spinBox_2->setMinimum(0);
    ui->spinBox_2->setMaximum(999999999);

    flag_berand=_flag_berand;
    flag_color=_flag_color;
    flag_weight=_flag_weight;
    flag_numerical=_flag_numerical;
    if(flag_numerical==1){
        ui->label_price_->setText("قیمت هر عدد:");
    }
    else{
        ui->label_price_->setText("قیمت هر کیلو:");
    }

    if(flag_berand==1){
        ui->lineEdit_berand->show();
        ui->label_berand_->show();
    }
    else{
        ui->lineEdit_berand->hide();
        ui->label_berand_->hide();
    }

    if(flag_color==1){
        ui->lineEdit_color->show();
        ui->label_color_->show();
    }
    else{
        ui->lineEdit_color->hide();
        ui->label_color_->hide();
    }

    if(flag_weight==1){
        ui->lineEdit_weight->show();
        ui->label_weight_->show();
    }
    else{
        ui->lineEdit_weight->hide();
        ui->label_weight_->hide();
    }

}

Dialog_add::~Dialog_add()
{
    delete ui;
}

void Dialog_add::on_pushButton_cancel_clicked()
{
    this->close();
}

void Dialog_add::on_pushButton_confirm_clicked()
{
    //بررسی مشخصات وارد شده
    if(1){
        emit item_added2(ui->lineEdit_type->text(),ui->spinBox->value(),ui->lineEdit_berand->text(),ui->lineEdit_color->text(),(ui->lineEdit_weight->text()).toInt(),ui->spinBox_2->value(),ui->plainTextEdit_descript->toPlainText(),flag_berand,flag_color,flag_weight,flag_numerical);
    }
    this->close();
}
