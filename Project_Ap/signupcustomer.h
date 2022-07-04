#ifndef SIGNUPCUSTOMER_H
#define SIGNUPCUSTOMER_H
#include <QDialog>
#include <QVector>
#include "customer.h"



namespace Ui {
class SignUpCUSTOMER;
}

struct Customer
{
    char Name[16];
    char User[16];
    char PhoneNumber[12];
    char Address[31];
    char Password[31];
    char city[11];
    char ProductType;
};

class SignUpCUSTOMER : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpCUSTOMER(QWidget *parent = nullptr);
    ~SignUpCUSTOMER();

private slots:
    void on_pushButton_clicked();

    bool CheckRadio();

    void on_pushButton_2_clicked();

private:
    Ui::SignUpCUSTOMER *ui;
    //QVector<Customer>customer;
};

#endif // SIGNUPCUSTOMER_H
